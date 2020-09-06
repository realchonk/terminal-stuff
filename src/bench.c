#include <pthread.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

typedef struct {
  float x, y, z, w;
} vec4f;

vec4f vec4f_add(vec4f a, vec4f b) {
  const vec4f r = {
    a.x + b.x,
    a.y + b.y,
    a.w + b.z,
    a.z + b.w
  };
  return r;
}
float frand(void) {
  return (float)rand() / (float)RAND_MAX;
}
vec4f vec4f_rand(void) {
  const vec4f r = {
    frand(),
    frand(),
    frand(),
    frand()
  };
  return r;
}

char* format_str(double x) {
  const char* prefix = "";
  if ((x / 1000000000) > 1) {
    prefix = "G";
    x /= 1000000000;
  }
  else if ((x / 1000000) > 1) {
    prefix = "M";
    x /= 1000000;
  }
  else if ((x / 1000) > 1) {
    prefix = "K";
    x /= 1000;
  }
  char* buf = (char*)malloc(100);
  snprintf(buf, 100, "%.2f%s", x, prefix);
  return buf;
}

#ifdef MULTICORE
inline unsigned nproc(void) {
  unsigned eax=11, ebx=0, ecx=1, edx=0;
  asm volatile("cpuid"
    : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
    : "0"(eax), "2"(ecx)
    :
  );
  return eax;
}

struct test {
  volatile uintmax_t counter;
  volatile int status;
  FILE* file;
  const int* nsec;
  pthread_t thread;
};

static clock_t cur_clock;
void* bench(void* data) {
  struct test* const t = (struct test*)data;
  printf("starting task with %d secs\n", *t->nsec);
  while (!t->status);
  const clock_t end = clock() + (*t->nsec * CLOCKS_PER_SEC);
  while (cur_clock < end) {
    const vec4f a = vec4f_rand();
    const vec4f b = vec4f_rand();
    const vec4f r = vec4f_add(a, b);
    fprintf(t->file, "%.3f + %.3f = %.3f\n", a, b, r);
    ++t->counter;
  }
  t->status = 2;
  return NULL;
}
#endif

int main(const int argc, const char* argv[]) {
  int nsec = 60;
  if (argc == 2) {
    nsec = atoi(argv[1]);
  }
  FILE* file = fopen("/dev/null", "w");
  if (!file) {
    puts("Failed to open /dev/null!");
    return 1;
  }
  srand(time(NULL));
  uintmax_t counter = 0;
#ifdef MULTICORE
  const unsigned num_threads = nproc();
  printf("This machine has %u threads\n", num_threads);

  struct test* tests = (struct test*)malloc(sizeof(struct test) * num_threads);
  for (size_t i = 0; i < num_threads; ++i) {
    tests[i].file = file;
    tests[i].counter = 0;
    tests[i].nsec = &nsec;
    if (pthread_create(&tests[i].thread, NULL, bench, &tests[i])) {
      printf("Failed to create thread #%zu!\n", i);
      return 2;
    }
  }

  for (size_t i = 0; i < num_threads; ++i) {
    tests[i].status = 1;
  }

  while (1) {
    int x = 0;
    cur_clock = clock();
    for (size_t i = 0; i < num_threads; ++i) {
      x += tests[i].status;
    }
    if (x == (num_threads * 2)) break;
  }
//  nsec = nsec * num_threads;
  for (size_t i = 0; i < num_threads; ++i) {
    counter += tests[i].counter;
  }
#else
  const clock_t end = clock() + (nsec * CLOCKS_PER_SEC);
  while (clock() < end) {
    const vec4f a = vec4f_rand();
    const vec4f b = vec4f_rand();
    const vec4f r = vec4f_add(a, b);
    fprintf(file, "%.3f + %.3f = %.3f\n", a, b, r);
    ++counter;
  }
#endif

  char* fmt = format_str((double)counter / (double)nsec);
  printf("%ju vec4f addtions in %d seconds. (%sops/sec)\n",
         counter, nsec, fmt
  );
  free(fmt);
  fclose(file);
  return 0;
}

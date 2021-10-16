#define _XOPEN_SOURCE 700

#if __linux__
#define _GNU_SOURCE 1
#include <linux/fs.h>
#endif

#include <sys/ioctl.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

// default size of the internal buffer (1 MiB)
#define DEF_BUF_SIZE (1<<20)

#ifndef O_DIRECT
#define O_DIRECT 0
#endif

static void eprintf(const char* msg, ...) {
   va_list ap;
   va_start(ap, msg);

   const int saved_errno = errno;
   fputs("flash: ", stderr);
   vfprintf(stderr, msg, ap);
   fprintf(stderr, ": %s\n", strerror(saved_errno));

   va_end(ap);
}

struct size_unit {
   const char* suffix;
   unsigned long long base;
};

static const struct size_unit units[] = {
   { "PiB", 1ull << 50 },
   { "TiB", 1ull << 40 },
   { "GiB", 1ull << 30 },
   { "MiB", 1ull << 20 },
   { "KiB", 1ull << 10 },
   { NULL, 0 },
};

static void print_size(size_t sz) {
   long double num;
   const char* suffix = NULL;
   for (size_t i = 0; units[i].suffix; ++i) {
      const struct size_unit* u = &units[i];
      if (sz >= u->base) {
         suffix = u->suffix;
         num = (long double)sz / (long double)u->base;
         break;
      }
   }
   if (suffix) {
      if (num >= 100) {
         printf("%.0Lf%s", num, suffix);
      } else if (num >= 10) {
         printf("%.1Lf%s", num, suffix);
      } else {
         printf("%.2Lf%s", num, suffix);
      }
   } else {
      printf("%zuB", sz);
   }
}

static void sz_print(const char* msg, size_t cur, size_t count) {
   printf("\r%s: ", msg);
   print_size(cur);
   putchar('/');
   print_size(count);
   fflush(stdout);
}

#if __linux__
static int get_blk_size(const char* filename) {
   int fd = open(filename, O_NONBLOCK);
   if (fd < 0)
      return -2;

   int blk_size;
   if (ioctl(fd, BLKSSZGET, &blk_size) < 0) {
      eprintf("failed to get block size of '%s'", filename);
   }
   
   close(fd);
   
   return blk_size;
}
#endif

int main(int argc, char* argv[]) {
   int option;
   size_t buf_size = DEF_BUF_SIZE;
   bool verbose = false;
   while ((option = getopt(argc, argv, ":b:v")) != -1) {
      char* endp;
      switch (option) {
      case 'v':
         verbose = true;
         break;
      case 'b':
         buf_size = (size_t)strtoull(optarg, &endp, 10);
         if (*endp) {
            fprintf(stderr, "flash: '%s' is not a valid number\n", optarg);
            return 1;
         }
         break;
      default:
      print_usage:
         fputs("Usage: flash [-b size] src dest\n", stderr);
         return 1;
      }
   }

   if ((argc - optind) != 2)
      goto print_usage;
   const char* src = argv[optind + 0];
   const char* dest = argv[optind + 1];

#if __linux__
   // get the block size of the device
   int blk_size = get_blk_size(dest);
   if (verbose) {
      fprintf(stderr, "%s: block size: %d\n", dest, blk_size);
   }
#endif

   char* buffer;
#ifdef __linux__
   if (blk_size > 0) {
      buffer = aligned_alloc(blk_size, buf_size);
   } else {
      buffer = malloc(buf_size);
   }
#else
   buffer = malloc(buf_size);
#endif

   if (!buffer) {
      eprintf("failed to allocate '%zu' bytes for internal buffer", buf_size);
      return 1;
   }

   const int fd_src = open(src, O_RDONLY | O_DIRECT);
   if (fd_src < 0) {
      eprintf("failed to open '%s'", src);
      return 1;
   }
   struct stat st_src;
   if (fstat(fd_src, &st_src) != 0) {
      eprintf("fstat failed for '%s'", src);
      close(fd_src);
      return 1;
   }

   int oflags = O_WRONLY | O_SYNC;
#if __linux__
   if (blk_size > 0) {
      if (verbose) {
         fprintf(stderr, "%s: adding O_DIRECT\n", dest);
      }
      oflags |= O_DIRECT;
   }
#endif

   const int fd_dest = open(dest, oflags);
   if (fd_dest < 0) {
      eprintf("failed to open '%s'", dest);
      close(fd_src);
      return 1;
   }

   const size_t sz = st_src.st_size;
   size_t copied = 0;
   sz_print(dest, copied, sz);
   int ec = 0;
   while (copied < sz) {
      const ssize_t nr = read(fd_src, buffer, buf_size);
      if (nr < 0) {
         putchar('\n');
         eprintf("failed to read %zu bytes from '%s'", buf_size, src);
         ec = 1;
         break;
      } else if (nr == 0) {
         break;
      }


      ssize_t nw = 0;
      while (nw < nr) {
         const ssize_t n = write(fd_dest, buffer + nw, nr - nw);
         if (n < 0) {
            putchar('\n');
            eprintf("failed to write %zu bytes to '%s'", (nr - nw), dest);
            ec = 1;
            goto end;
         }

         nw += n;
      }
      copied += nr;
      sz_print(dest, copied, sz);
   }
end:

   close(fd_src);
   close(fd_dest);
   if (ec == 0)
      putchar('\n');
   return ec;
}

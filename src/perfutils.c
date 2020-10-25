#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))

#define FILE_CPU_FREQ "/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq"
#define FILE_GOVERNOR "/sys/devices/system/cpu/cpufreq/policy0/scaling_governor"
#define FILE_GOVERNORS "/sys/devices/system/cpu/cpufreq/policy0/scaling_available_governors"

// options:
// read CPU frequency
// read/write CPU governor

static char* read_file(const char* filename, char* buf, size_t num) {
	FILE* file = fopen(filename, "r");
	if (!file) {
		printf("failed to open file %s!\n", filename);
		exit(1);
	}
	fgets(buf, num, file);
	fclose(file);
	return buf;
}
static void write_file(const char* filename, const char* str) {
	FILE* file = fopen(filename, "w");
	if (!file) {
		printf("failed to open file %s!\n", filename);
		exit(1);
	}
	fputs(str, file);
	fclose(file);
}

int read_cpu_freq(unsigned core) {
	char path[256] = FILE_CPU_FREQ;
	char buf[32];
	if (core > 9) {
		puts("perfutils currently supports at most 10 cores.");
		exit(1);
	}
	*strchr(path, '0') = core + '0';
	read_file(path, buf, sizeof buf);
	return atoi(buf);
}
static unsigned nproc(void) {
	return (unsigned)sysconf(_SC_NPROCESSORS_ONLN);
}


int main(int argc, const char** argv) {
	if (argc == 2) {
		write_file(FILE_GOVERNOR, argv[1]);
	}

	const unsigned ncpu = min(nproc(), 10);
	char governor[32], governors[128];
	read_file(FILE_GOVERNOR, governor, sizeof governor);
	read_file(FILE_GOVERNORS, governors, sizeof governors);
	printf("number of cores: %u\n", ncpu);
	printf("available governors: %s", governors);
	printf("current governor: %s", governor);
	for (unsigned i = 0; i < ncpu; ++i) {
		printf("cpu%d speed: %.1fMHz\n", i, (float)read_cpu_freq(i) / 1000.f);
	}
	return 0;
}

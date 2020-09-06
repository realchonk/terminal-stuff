#include <stdint.h>
#include <stdio.h>
#include <time.h>

#define SEC		(1)
#define MIN		(60*SEC)
#define HOUR	(60*MIN)
#define DAY		(24*HOUR)

static void print_time(uint64_t time, FILE* file) {
	if (time / DAY) {
		fprintf(file, "%ud", time / DAY);
		time %= DAY;
	}
	if (time / HOUR) {
		fprintf(file, "%uh", time / HOUR);
		time %= HOUR;
	}
	if (time / MIN) {
		fprintf(file, "%umin", time / MIN);
		time %= MIN;
	}
	if (time / SEC) {
		fprintf(file, "%us", time / SEC);
		time %= SEC;
	}
}

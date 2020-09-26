#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

#define arraylen(a) (sizeof(a) / sizeof(*(a)))

typedef struct {
	const char* name;
	char suffix;
	unsigned mult;
} time_scale_t;

static time_scale_t time_scales[] = {
	{ "second",	's',	1 						},
	{ "minute",	'm',	60 						},
	{ "hour",		'h',	60*60 				},
	{ "day",		'd',	24*60*60 			},
	{ "week",		'w',	7*24*60*60 		},
	{ "month",	'M',	30*24*60*60 	},
	{ "year",		'y',	365*24*60*60 	},
};

static time_t parse_time(const char* str) {
	size_t i = 0;
	time_t t = 0;
	while (str[i]) {
		if (!isdigit(str[i])) {
			puts("Invalid Format");
			exit(1);
		}
		unsigned n = 0;
		while (isdigit(str[i])) n = n * 10 + (str[i++] - '0');
		if (isalpha(str[i])) {
			const char ch = str[i++];
			for (size_t j = 0; j < arraylen(time_scales); ++j) {
				if (ch == time_scales[j].suffix) {
					n *= time_scales[j].mult;
					goto add;
				}
			}
			printf("Unknown time scale: '%c'\n", ch);
			exit(1);
		}
	add:
		t += n;
	}
	return t;
}
static void print_time(time_t t) {
	for (size_t i = arraylen(time_scales); i != 0; --i) {
		const time_scale_t* ts = &time_scales[i-1];
		if ((t / ts->mult) > 0) {
			printf("%u%c", t / ts->mult, ts->suffix);
			t %= ts->mult;
		}
	}
}

static void print_time_left(time_t left) {
	putchar('\r');
	for (int i = 0; i < 30; ++i) putchar(' ');
	putchar('\r');
	fputs("Time left: ", stdout);
	print_time(left);
}

int main(const int argc, const char* argv[]) {
	if (argc != 2) {
		printf("Usage: %s --help\n", *argv);
		return 1;
	}
	else if (strcmp(argv[1], "--help") == 0) {
		puts("TODO: Implement Help Page");
		return 0;
	}
	else if (strcmp(argv[1], "--version") == 0) {
		puts("Countdown v1.0");
		return 0;
	}
	const time_t end = time(NULL) + parse_time(argv[1]);
	time_t cur;
	while ((cur = time(NULL)) < end) {
		print_time_left(end - cur);
		fflush(stdout);
		sleep(1);
	}
	print_time_left(0);
	putchar('\n');
	return 0;
}

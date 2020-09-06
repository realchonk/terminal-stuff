#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, const char* argv[]) {
	if (argc != 2) {
		printf("Usage: %s <positive integer>\n", *argv);
		return -1;
	}
	const int n = atoi(argv[1]);
	bool is_prime;
	if (n == 2) {
		is_prime = true;
		goto end;
	}
	else if (n <= 1 || (n & 1) == 0) {
		is_prime = false;
		goto end;
	}
	for (int i = 3; i < (n/2); i += 2) {
		if (n % i == 0) {
			is_prime = false;
			goto end;
		}
	}
	is_prime = 1;
	end:
#if defined(PRINT_BOOL)
	puts(is_prime ? "true" : "false");
	return 0;
#elif defined(PRINT)
	puts(is_prime ? "1" : "0");
	return 0;
#elif defined(PRINT_UNIX)
	puts(is_prime ? "0" : "1");
	return 0;
#else
	return is_prime;
#endif
}

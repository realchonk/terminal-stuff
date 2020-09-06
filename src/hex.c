#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char* argv[]) {
	if (argc != 3 && argc != 4) {
		printf("Usage: %s <a> [<op>] <b>\n", *argv);
		return 1;
	}
	const int a = strtol(argv[1], NULL, 16);
	const int b = strtol(argc == 4 ? argv[3] : argv[2], NULL, 16);
	if (argc == 4) {
		if (strcmp(argv[2], "+") == 0) printf("%x + %x = %x\n", a, b, a + b);
		else if (strcmp(argv[2], "-") == 0) printf("%x - %x = %x\n", a, b, a - b);
		else if (strcmp(argv[2], "*") == 0) printf("%x * %x = %x\n", a, b, a * b);
		else if (strcmp(argv[2], "/") == 0) printf("%x / %x = %x\n", a, b, a / b);
		else if (strcmp(argv[2], "%") == 0) printf("%x % %x = %x\n", a, b, a % b);
		else if (strcmp(argv[2], "&") == 0) printf("%x & %x = %x\n", a, b, a & b);
		else if (strcmp(argv[2], "|") == 0) printf("%x | %x = %x\n", a, b, a | b);
		else if (strcmp(argv[2], "^") == 0) printf("%x ^ %x = %x\n", a, b, a ^ b);
		else if (strcmp(argv[2], "<<")== 0) printf("%x << %x = %x\n", a, b, a << b);
		else if (strcmp(argv[2], ">>")== 0) printf("%x >> %x = %x\n", a, b, a >> b);
	}
	else printf("%x + %x = %x\n", a, b, a + b);
	return 0;
}

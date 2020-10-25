#include <stdlib.h>
#include <stdio.h>

#ifndef THERMAL_FILE
#define THERMAL_FILE "/sys/class/thermal/thermal_zone0/temp"
#endif

int main(void) {
	FILE* file = fopen(THERMAL_FILE, "r");
	if (!file) {
		puts("failed to read file " THERMAL_FILE);
		return 1;
	}

	char buf[32];
	fgets(buf, sizeof buf, file);
	fclose(file);
	printf("%.1f\u00b0C\n", atof(buf) / 1000.f);
	return 0;
}

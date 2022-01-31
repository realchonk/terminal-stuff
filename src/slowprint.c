// Inspired by: https://youtu.be/fPU7Uq4TtNU?t=108
#define _XOPEN_SOURCE 500
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static void print_usage(void) {
   fputs("Usage: slowprint <baudrate>\n", stderr);
}

int main(int argc, char** argv) {
   unsigned long baudrate;
   if (argc == 1) {
      baudrate = 9600;
   } else if (argc == 2) {
      char* endp;
      baudrate = strtoul(argv[1], &endp, 0);
      if (*endp)
         return print_usage(), 1;
   } else return print_usage(), 1;

   const useconds_t delay = (useconds_t)(1000000.0f / (baudrate / 8.0f));

   int ch;
   while ((ch = fgetc(stdin)) != EOF) {
      fputc(ch, stdout);
      fflush(stdout);
      usleep(delay);
   }
   return 0;
}

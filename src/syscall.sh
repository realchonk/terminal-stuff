#!/bin/sh

EXE="$(basename "$0")"
USAGE="$EXE [-c CPP] [-o CPPFLAG] SYSCALL"
cpp=cpp
printf_opt="%d"

printed=0

while [ "$#" -gt 0 ]; do
   case "$1" in
   -h|--help)
      echo "Usage:"
      echo "  $USAGE"
      echo ""
      echo "Options:"
      echo "  -h,--help       Show this screen."
      echo "  -c CPP          Use CPP as the C preprocessor."
      echo "  -o CPPFLAGS     Add an options for the C preprocessor."
      echo "  -x              Print hexadecimal representation."
      echo ""
      echo "Bugs to <benni@stuerz.xyz>"
      exit 0
      ;;
   -c)
      [ "$#" -lt 2 ] && echo "$EXE: Expected argument for '-c'." >&2 && exit 1
      cpp="$2"
      shift 2
      ;;
   -o)
      [ "$#" -lt 2 ] && echo "$EXE: Expected argument for '-o'." >&2 && exit 1
      CPPFLAGS="$CPPFLAGS$SPACE$2"
      SPACE=' '
      shift 2
      ;;
   -x)
      printf_opt="%x"
      shift
      ;;
   -*)
      echo "$EXE: Invalid option '$1'." >&2
      exit 1
      ;;
   *)
      out="$(printf '#include <asm/unistd.h>\n__NR_%s\n' "$1" | "$cpp" $CPPFLAGS | grep -v '^\(#.*\|\s*\)$')"
      if echo "$out" | grep -Fq __NR_; then
         echo "$1: invalid"
      else
         printf "$1: $printf_opt\n" "$out"
      fi
      printed="$((printed + 1))"
      shift
      ;;
   esac
done

[ "$printed" -eq 0 ] && echo "Usage: $USAGE" >&2 && exit 1

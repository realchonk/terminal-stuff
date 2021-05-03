#!/bin/sh

filter() {
   while IFS= read -r file; do
      (file "$file" | grep ELF >/dev/null) || echo "$file"
   done
}

[ $# -lt 1 ] && echo "Usage: $(basename "$0") <directory...>" && exit 1

find "$@" -type f | filter | xargs wc -l | tail -n1 | awk '{print $1}'

#!/bin/sh

filter() {
   while IFS= read -r file; do
      (file "$file" | grep ELF >/dev/null) || echo "$file"
   done
}

[ $# -lt 1 ] && echo "Usage: $(basename "$0") <directory...>" && exit 1

find "$@" -type f | grep -v '^\./\.[^$]*$' | filter | xargs grep -v '^\s*\(//[^$]*\)\?\s*$' | wc -l | tail -n1 | awk '{print $1}'

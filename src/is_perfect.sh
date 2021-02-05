#!/bin/sh

[ $# -ne 1 ] && echo "Usage: $0 <integer>" && exit 255

[ -z "$count_divisors" ] || count_divisors="$(dirname "$0")/count_divisors.sh"

n_divs="$(count_divisors "$1")"

i=1
while [ "$i" -lt "$1" ]; do
	n="$(count_divisors "$i")"
	[ "$n" -ge "$n_divs" ] && echo 1 && exit 1
	i=$((i + 1))
done

echo 0
exit 0

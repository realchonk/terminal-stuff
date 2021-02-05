#!/bin/sh

[ $# -ne 1 ] && echo "Usage: $0 <integer>" && exit 255

[ "$1" -eq 0 ] && echo 0 && exit 0

n_divs=1

i=1
while [ $i -le "$(($1/2))" ]; do
	[ $(($1 % i)) -eq 0 ] && n_divs=$((n_divs + 1))
	i=$((i + 1))
done

echo "$n_divs"

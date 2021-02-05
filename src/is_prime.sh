#!/bin/sh

[ $# -ne 1 ] && echo "Usage: $0 <positive integer>" && exit 255

if [ "$1" -eq 2 ]; then
	echo 0
	exit 0
elif [ "$1" -le 1 ] || [ $(( $1 % 2 )) -eq 0 ]; then
	echo 1
	exit 1
fi

i=3
while [ "$i" -lt "$(($1 / 2))" ]; do
	[ $(( $1 % i )) -eq 0 ] && echo 1 && exit 1
	i=$((i + 2))
done

echo 0
exit 0

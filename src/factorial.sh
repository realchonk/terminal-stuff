#!/bin/sh

[ $# -ne 1 ] && echo "Usage: $0 <n>" && exit 1;

# 5! = 1 * 2 * 3 * 4 * 5
factorial() {
	result=1
	i=1
	while [ "$i" -le "$1" ]; do
		result=$(( result * i ))
		i=$((i + 1))
	done
	echo "$result"
}

factorial "$1"

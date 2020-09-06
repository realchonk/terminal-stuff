#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Usage: $0 <integer>"
	exit -1
fi

if [ $1 -eq 0 ]; then
	echo 0
	exit 0
fi

n_divs=1

for (( i=1; i<=($1/2); i++ )); do
	if [ $(( $1 % $i )) -eq 0 ]; then
		n_divs=$(($n_divs + 1))
	fi
done

echo $n_divs

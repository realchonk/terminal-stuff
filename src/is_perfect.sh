#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Usage: $0 <integer>"
fi

if [ -z "$count_divisors" ]; then
	count_divisors=$(dirname $0)/count_divisors.sh
fi

n_divs=$($count_divisors $1)

for (( i=1; i<$1; i++ )); do
	n=$($count_divisors $i)
	if [ $n -ge $n_divs ]; then
		echo 1
		exit 1
	fi
done

echo 0

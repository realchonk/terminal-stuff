#!/bin/sh

if [ $# -eq 0 ]; then
	start=1
	end=63
elif [ $# -eq 1 ]; then
	start=1
	end=$1
elif [ $# -eq 2 ]; then
	start=$1
	end=$2
else
	echo "Usage: $0 [<start>] <end>"
	exit -1
fi

is_prime=$(dirname $0)/is_prime.sh
n=$(( 2**$start ))

for (( i=start; i<end; i++ )); do
	tmp=$(( $n - 1 ))
	if [ $($is_prime $tmp) -eq 0 ]; then
		echo "2^$i-1 = $tmp"
	fi
	n=$(( $n*2 ))
done

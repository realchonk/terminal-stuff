#!/bin/sh

if [ $# -eq 0 ]; then
	start=1
	end=$(( 2**62-1 ))
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

if [ -z "$is_perfect" ]; then
	is_perfect="$(dirname $0)/is_perfect.sh"
fi

for (( i=$start; i<$end; i++ )); do
	if [ $($is_perfect $i) -eq 0 ]; then
		echo $i
	fi
done

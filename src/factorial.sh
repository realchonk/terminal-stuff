#!/bin/sh

if [ $# -ne 1 ]; then
	echo "Usage: $0 <n>"
	exit -1
fi

# 5! = 1 * 2 * 3 * 4 * 5
function factorial {
	result=1
	for (( i=1; i<=$1; i++ )); do
		result=$(( $result * $i ))
	done
	echo $result
}

echo $(factorial $1)

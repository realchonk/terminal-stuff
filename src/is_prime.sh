#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Usage: $0 <positive integer>"
	exit -1
fi

if [ $1 -eq 2 ]; then
	echo 0
	exit 0
elif [ $1 -le 1 ] || [ $(( $1 % 2 )) -eq 0 ]; then
	echo 1
	exit 1
fi

for (( i=3; i < ($1 / 2); i = i + 2 ))
do
	if [ $(( $1 % $i )) -eq 0 ]; then
		echo 1
		exit 1
	fi
done

echo 0
exit 0

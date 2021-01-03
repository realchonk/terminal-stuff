#!/bin/sh

# !!! Please do not move line 4, because it gets replaced when 'make install' !!!
datadir=$(dirname $0)/../share/benni
repeats=20

if [ $# -eq 2 ]; then
	delay=$1
	file=$2
elif [ $# -eq 1 ]; then
	delay=$1
	file=$datadir/timer.wav
else
	echo "Usage: $0 <time> [<file>]"
	exit 1
fi

if [ -z $sleep ]; then
	if [ -f $(dirname $0)/countdown ]; then
		sleep=$(dirname $0)/countdown
	else
		sleep=sleep
	fi
fi

$sleep $delay
for (( i=0; i < ${repeats}; i++ )); do
	aplay $file > /dev/null 2> /dev/null
	if [ $? -ne 0 ]; then break; fi
done

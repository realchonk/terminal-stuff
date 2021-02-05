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
	exit 1
fi

[ -z "$is_prime" ] && is_prime="$(dirname "$0")/is_prime.sh"
n=$(( 1 << start ))

i="$start"
while [ "$i" -lt "$end" ]; do
	tmp=$(( n - 1 ))
	[ "$($is_prime "$tmp")" -eq 0 ] && echo "2^$i-1 = $tmp"
	n=$(( n*2 ))
	i=$((i + 1))
done

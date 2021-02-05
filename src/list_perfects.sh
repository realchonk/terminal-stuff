#!/bin/sh

pow() {
	set -- "$1" "$2" 1
	while [ "$2" -gt 0 ]; do
		set -- "$1" $(($2-1)) $(($1*$3))
	done
	echo "$3"
}

if [ $# -eq 0 ]; then
	start=1
	end=$(( $(pow 2 62) - 1))
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

if [ -z "$is_perfect" ]; then
	is_perfect="$(dirname "$0")/is_perfect.sh"
fi

i="$start"
while [ "$i" -lt "$end" ]; do
	[ "$($is_perfect "$i")" -eq 0 ] && echo "$i"
	i=$((i + 1))
done

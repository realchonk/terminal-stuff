#!/bin/sh

fib() {
	if [ "$1" -eq 0 ] || [ "$1" -eq 1 ]; then
		echo "$1"
	else
		t1=$(fib $(( $1 - 1 )) )
		t2=$(fib $(( $1 - 2 )) )
		echo $(( t1 + t2 ))
	fi
}

[ $# -ne 1 ] && echo "Usage: $0 <n>" && exit 1

fib "$1"

# fib(n) = fib(n-1) + fib(n-2)

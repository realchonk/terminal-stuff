#!/bin/bash

# !!! Please do not move or change line 4 and 5, because it gets replaced with 'make install' !!!
backupdir="$(dirname "$0")/../backup"
backupfmt="%Y-%m-%d-%H-%M-%S"

if [ $# -eq 0 ]; then
	echo "Usage: $0 <directory...>"
	exit 1
fi

for arg in "$@"; do
	echo "$arg"
	mkdir -p "${backupdir}/${arg}"
	if ! tar -czf "${backupdir}/${arg}/$(date +${backupfmt}).tar.gz" "${arg}"; then
		echo "Failed to backup $arg"
		exit 1
	fi
done

exit 0

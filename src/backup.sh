#!/bin/bash

# !!! Please do not move or change line 4, because it gets replaced with 'make install' !!!
backupdir=$(dirname $0)/../backup

if [[ $# -eq 0 ]]; then
	echo "Usage: $0 <directory...>"
	exit 1
fi

for arg in "$@"; do
	echo $arg
	mkdir -p ${backupdir}/${arg}
	tar -czf ${backupdir}/${arg}/$(date +"%Y-%m-%d").tar.gz ${arg}
	if [[ $? -ne 0 ]]; then
		echo Failed to backup $arg
		exit 1
	fi
done

exit 0

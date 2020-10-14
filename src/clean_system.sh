#!/bin/sudo /bin/bash

if [ -f /bin/pacman ]; then
# Arch Linux
	pacman -Qtdq | pacman -Rns -
	rm -rf /var/cache/pacman/pkg/*
elif [ -f /bin/apt-get ]; then
# Debian
	apt-get update
	apt-get autoremove
fi

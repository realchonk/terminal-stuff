#!/bin/sudo /bin/sh

if [ $# -ne 1 ]; then
	echo "Usage: $0 <interface>"
	exit 1
fi

ip addr add 192.168.9.1/24 dev $1
dnsmasq -d -C /dev/null --port=0 --domain=localdomain --interface=$1 --dhcp-range=192.168.9.2,192.168.9.10,99h

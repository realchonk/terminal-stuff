#!/bin/sh

error() {
   echo "$(basename "$0"): $1" >&2
   exit 1
}

[ $# -ne 1 ] && echo "Usage: $(basename "$0") <kernel>" >&2 && exit 1

[ "$(id -u)" = 0 ] || error "Superuser access required."

kernel="$1"

[ -f "/boot/vmlinuz-${kernel}" ] || error "No such kernel: ${kernel}"

# delete the kernel itself
rm -v "/boot/vmlinuz-${kernel}" || error "Failed to delete kernel"

# delete the optional inird/initramfs
[ -f "/boot/initramfs-${kernel}.img" ] && rm -v "/boot/initramfs-${kernel}.img"
[ -f "/boot/initrd-${kernel}.img" ] && rm -v "/boot/initrd-${kernel}.img"

# delete the optional modules
[ -d "/lib/modules/${kernel}" ] && rm -rv "/lib/modules/${kernel}"

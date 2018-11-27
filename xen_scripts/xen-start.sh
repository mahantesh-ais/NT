#!/bin/bash
mount -t xenfs none /proc/xen
modprobe xen-gntdev
modprobe xen-evtchn
modprobe blktap
#modprobe xen-blkback
mkdir /var/run/xen
/usr/sbin/xenstored
/usr/sbin/xenconsoled
/usr/lib/xen/bin/xen-init-dom0
./network.sh


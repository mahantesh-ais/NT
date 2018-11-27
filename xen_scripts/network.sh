#!/bin/bash

killall dhclient
/etc/init.d/network-manager stop 
brctl addbr xenbr0
brctl addif xenbr0 eth0
ifconfig eth0 inet 0.0.0.0 promisc up 
dhclient xenbr0


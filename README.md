# Smart Virtual Network Interface & Packet Monitor

This project implements a Linux kernel virtual Ethernet device
using the net_device framework, designed for embedded and
OpenWrt-based systems.

## Features
- Custom virtual Ethernet interface (smart0)
- Packet TX monitoring
- Kernel statistics tracking
- OpenWrt kmod integration

## Build (OpenWrt)
make package/kernel/kmod-smart-netdev/compile V=s

## Load Module
insmod smart_netdev.ko

## Bring Interface Up
ip link set smart0 up
ip addr add 192.168.100.1/24 dev smart0

## Test
./userspace/netdev_test.sh

## Kernel Log
dmesg | grep smart_netdev

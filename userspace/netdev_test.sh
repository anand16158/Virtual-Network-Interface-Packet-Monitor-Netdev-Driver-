#!/bin/sh

echo "Bringing interface up..."
ip link set smart0 up

echo "Assigning IP..."
ip addr add 192.168.100.1/24 dev smart0

echo "Sending packets..."
ping -I smart0 -c 3 192.168.100.1

echo "Checking stats..."
ip -s link show smart0

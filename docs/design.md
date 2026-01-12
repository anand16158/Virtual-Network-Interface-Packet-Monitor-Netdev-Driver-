# Smart Virtual Netdev – Design

## Overview
This project implements a custom virtual Ethernet interface
using the Linux net_device framework.

## Kernel Components
- alloc_netdev()
- net_device_ops
- ndo_start_xmit()
- skb handling
- TX statistics

## Packet Flow
User Space → Kernel Netdev → TX Handler → skb free

## Use Cases
- Packet monitoring
- Network simulation
- Firewall / IDS foundations

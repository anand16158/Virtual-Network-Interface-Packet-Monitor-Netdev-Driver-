// SPDX-License-Identifier: GPL-2.0
/*
 * Smart Virtual Network Device
 *
 * - Custom virtual Ethernet interface
 * - Packet TX monitoring
 * - Kernel networking stack integration
 */

#include <linux/module.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/skbuff.h>

#define DRV_NAME "smart_netdev"

static struct net_device *smart_dev;

/* ================= TX PATH ================= */
static netdev_tx_t smart_xmit(struct sk_buff *skb,
                              struct net_device *dev)
{
    dev->stats.tx_packets++;
    dev->stats.tx_bytes += skb->len;

    pr_info("smart_netdev: TX packet len=%u protocol=0x%04x\n",
            skb->len, ntohs(skb->protocol));

    dev_kfree_skb(skb);
    return NETDEV_TX_OK;
}

/* ================= OPEN / CLOSE ================= */
static int smart_open(struct net_device *dev)
{
    netif_start_queue(dev);
    pr_info("smart_netdev: interface up\n");
    return 0;
}

static int smart_stop(struct net_device *dev)
{
    netif_stop_queue(dev);
    pr_info("smart_netdev: interface down\n");
    return 0;
}

/* ================= NETDEV OPS ================= */
static const struct net_device_ops smart_netdev_ops = {
    .ndo_open       = smart_open,
    .ndo_stop       = smart_stop,
    .ndo_start_xmit = smart_xmit,
};

/* ================= SETUP ================= */
static void smart_setup(struct net_device *dev)
{
    ether_setup(dev);
    dev->netdev_ops = &smart_netdev_ops;

    dev->flags |= IFF_NOARP;
    dev->features |= NETIF_F_HW_CSUM;
}

/* ================= MODULE INIT ================= */
static int __init smart_netdev_init(void)
{
    int ret;

    smart_dev = alloc_netdev(0, "smart%d",
                             NET_NAME_UNKNOWN, smart_setup);
    if (!smart_dev)
        return -ENOMEM;

    ret = register_netdev(smart_dev);
    if (ret) {
        free_netdev(smart_dev);
        return ret;
    }

    pr_info("smart_netdev: virtual interface registered\n");
    return 0;
}

/* ================= MODULE EXIT ================= */
static void __exit smart_netdev_exit(void)
{
    unregister_netdev(smart_dev);
    free_netdev(smart_dev);
    pr_info("smart_netdev: removed\n");
}

module_init(smart_netdev_init);
module_exit(smart_netdev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anand Kumar");
MODULE_DESCRIPTION("Smart Virtual Network Interface with Packet Monitor");

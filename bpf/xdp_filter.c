#include "../header/bpf_helpers.h"
#include <arpa/inet.h>
#include <linux/if_ether.h>


// XDP program //
SEC("xdp_drop")
int xdp_ipv6_filter_program(struct xdp_md *ctx)
{
    void *data_end = (void *)(long)ctx->data_end;
    void *data     = (void *)(long)ctx->data;
    struct ethhdr *eth = data;
    __u16 h_proto;

   if (data + sizeof(struct ethhdr) > data_end)
        return XDP_DROP;

    h_proto = eth->h_proto;

    // Check if the Ethernet type is IPv6
    if (h_proto == htons(ETH_P_IPV6))
        return XDP_DROP;

    return XDP_PASS;
}


char _license[] SEC("license") = "GPL";
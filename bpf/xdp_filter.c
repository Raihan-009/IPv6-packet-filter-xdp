#include "../header/bpf_helpers.h"

// Ethernet header
struct ethhdr {
  __u8 h_dest[6];
  __u8 h_source[6];
  __u16 h_proto;
} __attribute__((packed));


int parse_eth(struct ethhdr *eth, void *data_end, __u16 *eth_type)
{
    __u64 offset;

    offset = sizeof(*eth);
    if ((void *)eth + offset > data_end)
        return 0;
    *eth_type = eth->h_proto;
    return 1;
}

// XDP program //
SEC("prog")
int xdp_ipv6_filter_program(struct xdp_md *ctx)
{
    void *data_end = (void *)(long)ctx->data_end;
    void *data     = (void *)(long)ctx->data;
    struct ethhdr *eth = data;
    
    __u16 eth_type = 0;
    if (!(parse_eth(eth, data_end, &eth_type))) {
        return XDP_PASS;
    }

    // 0x86dd: IPv6 packets //
    if (eth_type == (0x86dd)) {
        return XDP_PASS;
    } else {
        return XDP_DROP;
    }
}

char _license[] SEC("license") = "GPL";
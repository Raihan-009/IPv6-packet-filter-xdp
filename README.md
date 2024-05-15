# IPv6-packet-filter-xdp


## Table of Contents

- [Introduction](#introduction)
- [Dependencies](#dependencies)
- [Installation](#installation)
- [Setting Up Pseudo Environment and Testing Connectivity](#setting-up-pseudo-environment-and-testing-connectivity)
- [Building and Loading BPF Code](#building-and-loading-bpf-code)
- [Testing Connectivity](#testing-connectivity)
- [Exploring with tcpdump](#exploring-with-tcpdump)
- [Clean Up](#clean-up)
- [References](#reference)


## Introduction

`eBPF` (extended Berkeley Packet Filter) is a revolutionary technology that allows for programmability within the Linux kernel. It enables the execution of sandboxed user-defined programs, providing efficient and flexible packet processing, tracing, and monitoring capabilities. `XDP` (eXpress Data Path) is a specific use case of eBPF tailored for high-performance packet processing at the network driver level. It operates directly on incoming packets before they reach the kernel's networking stack, allowing for ultra-fast packet filtering, forwarding, and manipulation with minimal overhead. Together, eBPF and XDP empower developers to implement complex networking functions with unprecedented speed and efficiency.

This project provides a packet filtering mechanism using XDP (eXpress Data Path) for IPv6 traffic. It aims to enhance network security and performance by filtering IPv6 packets at the kernel level.

## Dependencies

Before getting started, ensuring that the following dependencies are installed on our `Ubuntu` system:

```bash
sudo apt install clang llvm libelf-dev libpcap-dev build-essential libc6-dev-i386
sudo apt install linux-headers-$(uname -r)
sudo apt install linux-tools-common linux-tools-generic
```

## Installation
To get started with this project, follow these steps:

1. Clone this repository to local machine using `git clone git@github.com:Raihan-009/IPv6-packet-filter-xdp.git`.
2. Navigate to the project directory: `cd IPv6-packet-filter-xdp`.
3. Follow the `Makefile` for further operations or follow the Doc.


## Setting Up Pseudo Environment and Testing Connectivity

The environment setup involves creating a network namespace named "node" and configuring two virtual Ethernet interfaces (`veth-u` and `veth-k`). One end of the virtual link (`veth-u`) is moved into the "node" namespace while the other end (`veth-k`) remains in the default namespace. IP addresses are assigned to each interface, enabling communication between processes within the "node" namespace and the default namespace. XDP code will be loaded in veth-k.

Here is the demo illustration.

![pseduo env](https://github.com/Raihan-009/IPv6-packet-filter-xdp/blob/main/pseduo-env.png?raw=true)

To set up a pseudo environment and test connectivity:

```bash
make pseudo-env
```

For making pseudo network environment:
```bash
sudo ip netns add node
sudo ip link add dev veth-u type veth peer name veth-k
sudo ip link set veth-u netns node
sudo ip netns exec node ip addr add 192.168.1.1/24 dev veth-u
sudo ip netns exec node ip link set dev veth-u up
sudo ip addr add 192.168.1.2/24 dev veth-k
sudo ip link set up dev veth-k
```
- Test connectivity for IPv4
    ```bash
    make test-connectivity
    ```
- Test connectivity for IPv6:
    ```bash
    make get-ipv6
    make exec-node
    ping6 fe80::c4b5:26ff:fe32:2535
    ```

## Building and Loading BPF Code

To build and load the BPF (Berkeley Packet Filter) code:

```bash
make build-bpf
make load-bpf
```

BPF code at a glance

```c
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

    // Check if the Ethernet type is IPv6 //
    if (h_proto == htons(ETH_P_IPV6))
        return XDP_DROP;

    return XDP_PASS;
}
```
## Testing Connectivity

   - Test Connectivity for IPv4
        ```bash
        make test-connectivity
        ```

   - Test Connectivity for IPv6
        ```bash
        make get-ipv6
        make exec-node
        ping6 fe80::c4b5:26ff:fe32:2535
        ```

***Expected Output***
![test-connectivity](https://github.com/Raihan-009/IPv6-packet-filter-xdp/blob/main/test-connectivity.png?raw=true)

## Exploring with tcpdump

For exploring more `tcpdump` utility can do a great job! 
```bash
sudo tcpdump -i veth-k
```

## Clean Up

To clean up the environment:

```bash
make clean
```

## References

1. [eBPF XDP: The Basics and a Quick Tutorial](https://www.tigera.io/learn/guides/ebpf/ebpf-xdp/)
2. [A brief introduction to XDP and eBPF](https://blogs.igalia.com/dpino/2019/01/07/introduction-to-xdp-and-ebpf/)
3. [Learning-ebpf](https://github.com/lizrice/learning-ebpf)
4. [XDP Tutorial](https://github.com/xdp-project/xdp-tutorial)
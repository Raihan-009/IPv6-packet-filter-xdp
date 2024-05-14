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


## Introduction

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
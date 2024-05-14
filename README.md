# IPv6-packet-filter-xdp

## Dependencies -> Packages for Ubuntu
```bash
sudo apt install clang llvm libelf-dev libpcap-dev build-essential libc6-dev-i386
sudo apt install linux-headers-$(uname -r)
sudo apt install linux-tools-common linux-tools-generic
```

## Make pseudo environment and test connectivity

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

## Build and Load bpf code
```bash
make build-bpf
make load-bpf
```

## Test Connectivity for IPv4
```bash
make test-connectivity
```

## Test Connectivity for IPv6
```bash
make get-ipv6
make exec-node
ping6 fe80::c4b5:26ff:fe32:2535
```

For exploring more `tcpdump` utility can do a great job!

## Clean Up
```bash
make clean
```
pseudo-env:
	@ chmod +x ./netns.sh
	@ ./netns.sh

test-connectivity:
	@ sudo ip netns exec node ping -c 1 192.168.1.2

build-bpf:
	@ clang -O2 -target bpf -c bpf/xdp_filter.c -o bpf/xdp_filter.o

load-bpf:
	@ sudo ip link set dev veth-k xdpgeneric obj bpf/xdp_filter.o sec xdp_drop

get-ipv6:
	@ ip -6 addr show dev veth-k | grep -oP '(?<=inet6 )[\da-f:]+' | head -n 1

tcpdump-bpf:
	@ sudo tcpdump -i veth-k 

exec-node:
	@ sudo ip netns exec node bash

clean:
	@ sudo rm -rf bpf/xdp_filter.o
	@ sudo ip netns delete node
	@ sudo ip link delete dev veth-k

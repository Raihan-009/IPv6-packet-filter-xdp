
env:
	@ chmod +x ./netns.sh
	@ ./netns.sh

bpf-build:
	@ clang -O2 -target bpf -c bpf/xdp_filter.c -o bpf/xdp_filter.o
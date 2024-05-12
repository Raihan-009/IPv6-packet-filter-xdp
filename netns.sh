sudo ip link add dev veth-u type veth peer name veth-k
sudo ip link set up dev veth-u
sudo ip link set up dev veth-k
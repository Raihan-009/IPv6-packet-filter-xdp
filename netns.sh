sudo ip netns add node
sudo ip link add dev veth-u type veth peer name veth-k
sudo ip link set veth-u netns node
sudo ip netns exec node ip addr add 192.168.1.1/24 dev veth-u
sudo ip netns exec node ip link set dev veth-u up
sudo ip addr add 192.168.1.2/24 dev veth-k
sudo ip link set up dev veth-k
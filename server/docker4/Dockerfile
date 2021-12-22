FROM slankdev/ubuntu:20.04


# (base=slankdev/ubuntu18:04) basic package install

RUN apt -y update \
 && apt install -y iproute2 net-tools iputils-ping build-essential tcpdump iperf3 systemctl hping3 nmap ufw iptables python3-pip\
 && pip3 install scapy\
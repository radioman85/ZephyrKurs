#!/usr/bin/python

import socket
from socket import *
import datetime;
from datetime import timezone


def recv_from_client(sock, out_file):
    data = sock.recv(1024)
#    dt = datetime.datetime.now(timezone.utc)
#    utc_time = dt.replace(tzinfo=timezone.utc)
#    utc_timestamp = utc_time.timestamp()
    while data:
        out_file.write(data)
        if print(f"{data}"):
            break
        data = sock.recv(1024)
    sock.close()

out = open('gnss-data.txt', 'wb', buffering=0)
bindsocket = socket(AF_INET, SOCK_STREAM)
bindsocket.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
bindsocket.bind(('192.168.8.1', 2001))
bindsocket.listen(5)

try:
    while True:
        clientsock, fromaddr = bindsocket.accept()
        print(f"connected by {fromaddr}")
        recv_from_client(clientsock, out)
finally:
    bindsocket.shutdown(socket.SHUT_RDWR)
    bindsocket.close()
    out.close()


import socket as soc, sys

HOST = ''
PORT = 5000

s = soc.socket(soc.AF_INET, soc.SOCK_STREAM )
s.setsockopt(soc.SOL_SOCKET, soc.SO_REUSEADDR, 1)

s.bind((HOST,PORT))
s.listen(1024)

while True:
    connectedSock, address = s.accept()
    print 'Connected by:', address

    while True:
        data = connectedSock.recv(2048)
        if not data:
            break
        connectedSock.sendall(data.upper())
    connectedSock.close()

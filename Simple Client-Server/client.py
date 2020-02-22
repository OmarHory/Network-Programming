import socket, sys
HOST = 'localhost' # The remote host
PORT = 5000
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
while True:
    message = raw_input('Input: ')
    s.sendall(message.encode('utf-8'))
    data = s.recv(2048)
    print 'Received:', data.decode('utf-8')
s.close()

from builtins import input
import socket
import sys

PORT = 80
IP_VERSION = 'IPv4'
IPV4 = '192.168.43.76'
IPV6 = 'BC9F:260A:C4FF:FE23:DA24'

family_addr = socket.AF_INET
host = IPV4
    
try:
    #SOCK_STREAM denotes TCP connection
    sock = socket.socket(family_addr, socket.SOCK_STREAM)       
    
except socket.error as msg:
        print('Could not create socket: ' + str(msg[0]) + ': ' + msg[1])
        sys.exit(1)
        
try:
    #Provide the ip address and Port number of the server to create connection
    sock.connect((host, PORT))
        
except socket.error as msg:
        print('Could not open socket: ', msg)
        sock.close()
        sys.exit(1)

while True:
    msg = input('Enter message to send: ')

    #Check whether msg is a string or not
    assert isinstance(msg, str)

    #Convert string to ascii format 
    msg = msg.encode()

    #Send msg until the server recieves the message
    sock.sendall(msg)
    data = sock.recv(1024)

    if not data:
        break
    print('Reply: ' + data.decode())
sock.close()

#!/usr/bin/env python
import rospy
from std_msgs.msg import String
from sra.msg import custom_array
from builtins import input
import socket
import sys

PORT = 80
IP_VERSION = 'IPv4'
IPV4 = '192.168.43.61'

#Encode the data before sending to the server 
def encodeData(array):
	emptyArr=[]	
	emptyArr = map(str,array)                                     #Converts all the elements in an array to string
	emptyArr='a'+emptyArr[0]+'b'+emptyArr[1]+'c'+emptyArr[2]+'d' 
	print emptyArr
	return (emptyArr)

#create and connect to the required host
def checkConnection():
	global sock,sys
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

def callback(data):
	
	global sock
	
	rospy.loginfo(rospy.get_caller_id() + "I heard {},{},{}".format(data.array1[0],data.array1[1],data.array1[2]))

	msg = encodeData(data.array1)
	
	#Verifies if the msg is string or not
	assert isinstance(msg, str)                     
	msg= msg.encode()					
	
	#Send data to the server
	sock.sendall(msg)				
	
	#Recieve same data back from the server for confirmation
	recieved_data = sock.recv(1024)			

	if not recieved_data:
		print("error in recieving data")
	print('Reply: ' + recieved_data.decode())	

	
        
def listener():
	checkConnection()
	rospy.init_node('listener', anonymous=True)
	rospy.Subscriber("chatter",custom_array, callback)
	while not rospy.is_shutdown():
		rospy.spin()
	
   
if __name__ == '__main__':
	listener()
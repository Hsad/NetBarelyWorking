# Echo client program
import socket

HOST = "cpe-69-207-198-85.stny.res.rr.com"
#HOST = "69.207.198.85"
#HOST = "127.0.0.1"    # The remote host
#PORT = 51824   # when talking to the laptop
PORT = 51878   # when talking to the desktop
#PORT = 51993   # The same port as used by the server phone
#s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

#s.connect((HOST, PORT))
#s.sendall('Hello, world')
s.settimeout(1)
while 1:
	s.sendto('Hello, world', (HOST, PORT))
	print "sent"
	try:
		data = s.recv(1024)
		break
	except socket.timeout:
		pass
#print 'Received', repr(data)
print 'Received', data

#s.sendall('') #this ends the 
s.sendto('', (HOST, PORT)) #this ends the 

raw_input("hello??")
s.close()

# Echo server program
#Linux Kill Code:  fuser -k -n udp 51824
import socket

HOST = ''                 # Symbolic name meaning all available interfaces
#PORT = 51824              # when running from the laptop
PORT = 51878              # when running from the desktop

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind((HOST, PORT))
#s.listen(1)
#conn, addr = s.accept()
#print 'Connected by', addr
while 1:
		#data = conn.recv(1024)
		data, addr = s.recvfrom(1024)
		#so addr is the tuple of host and address
		if not data: break
		print 'Connected by', addr
		print 'data=', data
		#s.sendall(data)
		#conn.sendall(data)
		s.sendto('Hello, is this phone?', addr)
#conn.close()
raw_input("hello??")
s.close()

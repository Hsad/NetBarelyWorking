import threading
import socket
import time

#hostIP = "127.0.0.1"
hostIP = "cpe-69-207-198-85.stny.res.rr.com"
pyHostPort = 51878 #desktop
cppHostPort = 51824 #laptop

UDPContinue = True  #so much is wrong with this
TCPContinue = True  #but why stop there


def endTheParty():
	global TCPContinue #pretty sure this isn't nessisary but im not
	global UDPContinue #gonna check because that will mean I cant kill it
	TCPContinue = False
	UDPContinue = False

class threadedUDP(threading.Thread):
	def __init__(self):
		threading.Thread.__init__(self)
	
	def run(self):
		global UDPContinue
		#start pulling in input
		#and send it off into the void
		#am I running python 2.7 or 3.x
		#uhhhh 3?
		#ok
		soc = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		#inp = "sds"
		while UDPContinue:
			inp = input(":")
			soc.sendto(inp.encode('utf-8'),(hostIP, cppHostPort))
			if (inp == "bye"):
				endTheParty()
		#if thats not stupid simple I dont know what is
		print("UDP done")


class threadedTCPclient(threading.Thread):
	def __init__(self):
		threading.Thread.__init__(self)

	def run(self):
		#Linux Kill Code:  fuser -k -n udp 51824
		global TCPContinue
		EmptyHOST = ''   # Symbolic name meaning all available interfaces

		s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		s.bind((EmptyHOST, pyHostPort))
		print("TCP listening")
		s.listen(1)
		conn, addr = s.accept()
		print("TCP accepted")
		#print 'Connected by', addr
		conn.settimeout(1)
		while TCPContinue:
			try:
				#print("trying to pull data in TCP")
				data = conn.recv(1024)
				#data, addr = s.recvfrom(1024)
				#so addr is the tuple of host and address
				#if not data: break
				#print 'Connected by', addr
				print(data.decode("utf-8"))
				if (data.decode("utf-8") == "bye" or not data):
					endTheParty()
					print("C++ logged out, type 'bye' or ctrl-C")
				#s.sendall(data)
				#conn.sendall(data)  #only taking in data to print out, not
				#really sending anything back
				#s.sendto('Hello, is this phone?', addr)
			except socket.timeout:
				#print("TCP timed out")
				pass
		conn.close()
		#raw_input("hello??")
		s.close()



#start the udp
UDP = threadedUDP()
UDP.start()

#start up the TCP client loop
#hell it might be easy to put it into a thread
#cant hurt to try

TCP = threadedTCPclient()
TCP.start()

#time.sleep(30)
#UDPContinue = False


print("before the joins")
UDP.join()
TCP.join()
print("main thread done")










#want a thread that tracks incomming input, and broadcasts that.
#additionally that thread should send back replies for TCP.
#not sure if that reply system is very inherent to TCP or is something
#that I need to implement and can tack onto the UDP sending

#I think that I'm going to need a udp server on the python side
#and a tcp server on the c++ side
#im not sure how, or what direction a udp needs to run, it should be
#both ways, but im guessing the client initialtes it.


#ok so the udp is just slugging out messages. real simple
#the incomming tcp connection is initialized and held
#neither will be in the way of the other, as they are heading
#along different ports.  The tcp server is on the python side
#so that make my life easier

#waiting for a message through tcp will block, but if the 
#input is threaded with the sending from udp, it will be unnoticable
#conversely on the c++ side, if waiting for the udp is threaded
#then input will be free to run and send off with tcp.
#so only one thread is required per each

#how do you want the two sides to connect and disconnect?
#connecting should be automatic
#disconnnection would be based off of the tcp closing
#so either side can control the connection... or maybe just the
#python side


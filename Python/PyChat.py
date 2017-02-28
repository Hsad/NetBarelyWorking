import threading
import socket
import time

#hostIP = "127.0.0.1"
hostIP = "cpe-69-207-198-85.stny.res.rr.com"
pyHostPort = 51878 #desktop
cppHostPort = 51824 #laptop

UDPContinue = True  #so much is wrong with this

class threadedUDP(threading.Thread):
	def __init__(self):
		threading.Thread.__init__(self)
	
	def run(self):
		#start pulling in input
		#and send it off into the void
		#am I running python 2.7 or 3.x
		#uhhhh 3?
		#ok
		soc = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		inp = "sds"
		while UDPContinue:
			inp = input(":")
			soc.sendto(inp.encode('utf-8'),(hostIP, cppHostPort))
		#if thats not stupid simple I dont know what is


#start the udp
UDP = threadedUDP()
UDP.start()

time.sleep(30)
UDPContinue = False













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


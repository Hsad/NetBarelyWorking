import socket

hostIP = "127.0.0.1"
pyHostPort = 51824
cppHostPort = 51878

#want a thread that tracks incomming input, and broadcasts that.
#additionally that thread should send back replies for TCP.
#not sure if that reply system is very inherent to TCP or is something
#that I need to implement and can tack onto the UDP sending

#I think that I'm going to need a udp server on the python side
#and a tcp server on the c++ side
#im not sure how, or what direction a udp needs to run, it should be
#both ways, but im guessing the client initialtes it.





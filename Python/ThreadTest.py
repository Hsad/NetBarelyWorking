import threading
import time

class output (threading.Thread):
	def __init__(self, out):
		threading.Thread.__init__(self)
		self.outputString = out

	def run(self):
		for x in range(30):
			print(self.outputString)
			time.sleep(1)



#thread.start_new_thread( output, "hello" )

out1 = output("hello")
out1.start()

while 1:
	inp = input("What?")
	if inp == 'x':
		break
	else:
		print("yep yep yep" + inp)
		#print(inp)

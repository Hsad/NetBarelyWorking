//Real dirty copy paste of ExSer, which is 42% copy pasted from
//Beej's networking guide.  What a guy.  Also what a strange name
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string>
#include <string.h> //memset
#include <unistd.h> //close
#include <cstdio> //printf
#include <cerrno>
#include <fcntl.h> //non blocking

#include <thread>
#include <chrono>
using namespace std;

bool UDPContinue = true;
bool TCPContinue = true;

void outputUDP(){
	int status;
	struct addrinfo hints;
	struct addrinfo *servinfo;

	memset(&hints, 0, sizeof hints); //zero out the struct
	hints.ai_family = AF_UNSPEC;  //ipv4
	//hints.ai_socktype = SOCK_STREAM;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE;


	//status = getaddrinfo(NULL, "51878", &hints, &servinfo); //desk
	status = getaddrinfo(NULL, "51824", &hints, &servinfo); //laptop
	if (status != 0){
		cout << "error with get addrinfo";
		return;
	}

	int socketFD;
	socketFD =  socket(servinfo->ai_family, 
										servinfo->ai_socktype, 
										servinfo->ai_protocol);

	bind(socketFD, servinfo->ai_addr, servinfo->ai_addrlen);

	char buff[1024];
	struct sockaddr_storage clientAddress; 
	//sockaddr_storage is larger than what it is cast into
	//not exactly sure on the details of that
	socklen_t addr_len = sizeof clientAddress;
	int recvBytes;

	//I think, because this is a thread, that really just waits
	//either I should make the thread end after a timeout period 
	//of no contact from the python, or more reasonably
	//have main change a variable from true to false
	//
	//Also need to make this non blocking, so that when the signal
	//to close up shop comes in, the change in UDPContinue is 
	//detected rather than waiting for one last message that
	//will never come.  
	
	fcntl(socketFD, F_SETFL, O_NONBLOCK);
	while (UDPContinue){
		recvBytes = recvfrom(socketFD, buff, 1024, 0, 
								(struct sockaddr*) &clientAddress,
								&addr_len);
		if (recvBytes == -1){
			//this should call freqently because of the non blocking
			this_thread::sleep_for(chrono::milliseconds(100));
			//sleep(1);  //this will induce a bit of delay into the 
			//speed of the udp signal, but nothing terrible
			//should drop its delay so it checks 10 times a second,
			//should be nearly unnoticable
		}
		else {
			//cout << "data recived\n";
			printf("%s",buff);
			cout << endl;
			string killString = buff;
			if(killString == "bye"){
				UDPContinue = false;
				TCPContinue = false;
				cout << "Python logged out, type 'bye' or ctrl-C\n";
			}
			memset(&buff, 0, sizeof buff);
		}
		/*
		const char *dataToLap = "helsdflo is this lappy?";
		//string dataToLap = "hello is this lappy?";
		int sentBytes = sendto(socketFD, dataToLap, 
														strlen(dataToLap), 0,
														(struct sockaddr*) &clientAddress, 
														sizeof clientAddress);
		cout << "the number of bytes sent was: " << sentBytes << endl;
		cout << "char* test: " << dataToLap << endl;
		if (sentBytes == -1){
			cout << "error sending back, errno: ";
			close(socketFD);
			cout << errno;
			perror("what dis shit");
			return -3;
		}
		*/
	}
	
	close(socketFD);
}

void inputTCP(){
	//connect to the py tcp server
	//when the connection goes down, close up shop and exit loop
	struct addrinfo hints, *res;
	int sockfd;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	getaddrinfo("69.207.198.85", "51878", &hints, &res);
	
	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	int connRet = -1;
	while (connRet == -1){
		connRet = connect(sockfd, res->ai_addr, res->ai_addrlen);
		sleep(1);
	}
	cout << "TCP Connected\n";

	int len, bytes_sent;
	string outp;
	while (TCPContinue){
		//cin >> outp;
		getline(cin, outp);
		//cout << outp << " and: " << outp.c_str() << endl;
		len = strlen(outp.c_str());
		bytes_sent = send(sockfd, outp.c_str(), len, 0);
		if (outp == "bye" or outp == "bye "){
			TCPContinue = false;
			UDPContinue = false;
		}
	}

	//this_thread::sleep_for(chrono::seconds(30));
}


int main(){

	thread UDP (outputUDP);

	//probably want to make a function for the tcp,
	//more so that main doesnt also look aweful, 

	inputTCP();
	
	//once the tcp connection closes, because it has lost
	//connection to the python server, stop the UDP thread from 
	//listening for rogue UDPs
	//Total side note, but this is probably a super vunerable set up
	
	UDPContinue = false;
	UDP.join();
	return 0;
}

//Cpp copy of the python server
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string>
#include <string.h> //memset
#include <unistd.h> //close
#include <cstdio> //printf
#include <cerrno>
using namespace std;




int main(){
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
		return -1;
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

	while (true){
		recvBytes = recvfrom(socketFD, buff, 1024, 0, 
								(struct sockaddr*) &clientAddress,
								&addr_len);
		if (recvBytes == -1){
			cout << "error in recvfrom";
			close(socketFD);
			return -2;
		}
		else if (recvBytes == 0){
			cout << "connection closed, I think";
			break;
		}
		else {
			cout << "data recived\n";
			//cout << static_cast<string*>(buff);  // in another context where the
			//buff[1024] = '\0';
			printf("%s",buff);
			cout << "what is even going on \ncrazy stuff\n";
			//incomming data might be larger than 1024,
			//to print the buffer may require tacking on a
			//null terminator to the end of the buffer
			//should be good for now
		}
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
	}
	
	int x;
	cout << "end?: ";
	cin >> x;
	return 0;
}

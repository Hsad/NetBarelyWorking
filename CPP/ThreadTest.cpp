#include <iostream>
#include <thread>
//#include <unistd.h>
#include <string>
#include <chrono>
using namespace std;

void outThread(string str){
	for (int x=0; x < 30; x++){
		cout << str << endl;
		this_thread::sleep_for(chrono::seconds(1));
		//sleep(1);
	}
}

int main(){
	
	thread out1 (outThread, "HelloThere");

	while (true){
		string inp;
		cout << "what: ";
		getline( cin, inp);
		//cin >> inp;
		if (inp == "x"){
			break;
		} else{
			cout << "yep yep yep " << inp << endl;
		}
	}

	out1.join();

	return 0;
}

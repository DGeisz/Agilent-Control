#include "SerialCom.h"
#include <iostream>


int main(int argc, char *argv[]){
	
	SerialCom Arduino("/dev/ttyACM0", B9600);
	while (true){
		//std::string a;
		//std::cin >> a;
		//Arduino.write(a);
		std::string buf;
		int r = Arduino.read(buf);
		std::cout<< "[" << buf << "]" <<std::endl;
		sleep(.25);
	}

	return 0;
}


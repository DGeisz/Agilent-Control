#include "ArduinoCom.h"

std::string arduino_port = "/dev/ttyACM0";

int main(int argc, char *argv[]){
	ArduinoCom MyArd(arduino_port, B9600);
	while (true){
		std::string cmd;
		std::cin>> cmd;
		std::cout<<MyArd.get_value(cmd)<<std::endl;
	}
}


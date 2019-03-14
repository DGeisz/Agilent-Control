#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "AgilentPs.h"

std::string port = "/dev/ttyUSB0"; //Change this according to which port the PS is connected to
int gpib = 4;

int main(int argc, char *argv[]){
	AgilentPs PS(port, gpib);
	PS.turnOn();
	PS.setVoltage(2.0);
	sleep(1);
	std::string voltage = PS.getVoltage();
	std::cout<<"Current Voltage is:"<<voltage<<std::endl;
	PS.turnOff();
}

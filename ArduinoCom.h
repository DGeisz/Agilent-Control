#ifndef ARDUINOCOM
#define ARDUINOCOM

#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <iostream>
#include <fstream>
#include <string>
#include <termios.h>

#include "SerialCom.h"

class ArduinoCom {
	public:
		ArduinoCom(std::string name, speed_t baud);
		~ArduinoCom();
		std::string get_value(std::string value_type); 
		double get_double_value(std::string value_type);
	private:
		SerialCom *ard_serial;
};
#endif


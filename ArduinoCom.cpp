#include "ArduinoCom.h"

using namespace std;

ArduinoCom::ArduinoCom(std::string name, speed_t baud){
	ard_serial = new SerialCom(name, baud);
}

ArduinoCom::~ArduinoCom(){
	delete ard_serial;
}

std::string ArduinoCom::get_value(std::string value_type){
	ard_serial->write(value_type);
	std::string buf;
	sleep(2);
	ard_serial->read(buf);
	return buf;
}

double ArduinoCom::get_double_value(std::string value_type){
	std::string value_str = ArduinoCom::get_value(value_type);
	return stod(value_str);
}


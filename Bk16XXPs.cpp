#include "Bk16XXPs.h"

#include <algorithm>

using namespace std::chrono;

Bk16XXPs::Bk16XXPs(std::string dev) {
	m_com = new SerialCom(dev, B9600);
}

Bk16XXPs::~Bk16XXPs() {
	delete m_com;
}

void Bk16XXPs::send(std::string cmd) {
	cmd += "\r";
	m_com->write(cmd);
	std::this_thread::sleep_for(std::chrono::milliseconds(m_wait));
	std::string buf;
	m_com->read(buf);
}

std::string Bk16XXPs::receive(std::string cmd) {
	cmd += "\r";
	m_com->write(cmd);
	std::this_thread::sleep_for(std::chrono::milliseconds(m_wait));
	std::string buf;
	m_com->read(buf);
	return buf;
}

void Bk16XXPs::init() {
	this->turnOff();
}

void Bk16XXPs::setVoltage(double volt) {
	volt *= 10;
	int volt_int = (int)volt;
	if (volt_int < 100) {
		this->send("VOLT0" + std::to_string(volt_int));
	}
	else {
		this->send("VOLT" + std::to_string(volt_int));
	}
}

double Bk16XXPs::getVoltageSetting() {
	std::string volt_curr = this->receive("GETS");
	volt_curr = volt_curr.substr(0, volt_curr.find("\r"));
	//return volt_curr;}
	int volt_curr_int = stoi(volt_curr);
	double volt = floor((double)volt_curr_int / 1000);
	return volt / 10;
}

double Bk16XXPs::getVoltageReading() {
	std::string volt_curr = this->receive("GETD");
	volt_curr = volt_curr.substr(0, volt_curr.find("\r"));
	int volt_curr_int = stoi(volt_curr);
	double volt = floor((double)volt_curr_int / 100000);
	return volt / 100;
}

void Bk16XXPs::setMaxVoltage(double volt) {
	volt *= 10;
	int volt_int = (int)volt;
	if (volt_int < 100) {
		this->send("SOVP0" + std::to_string(volt_int));
	}
	else {
		this->send("SOVP" + std::to_string(volt_int));
	}
}

double Bk16XXPs::getMaxVoltage() {
	std::string max_volt = this->receive("GOVP");
	std::string voltage = max_volt.substr(0, max_volt.find("\r"));
	int volt_int = stoi(voltage);
	double volt = floor((double)volt_int / 10);
	return volt;
}

void Bk16XXPs::setCurrent(double curr){
	curr *= 10;
	int curr_int = (int)curr;
	if (curr_int < 100) {
		this->send("CURR0" + std::to_string(curr_int));
	}	
	else {
		this->send("CURR" + std::to_string(curr_int));
	}
}

double Bk16XXPs::getCurrentSetting() {
	std::string volt_curr = this->receive("GETS");
	volt_curr = volt_curr.substr(0, volt_curr.find("\r"));
	int volt_curr_int = stoi(volt_curr);
	int curr = volt_curr_int % 1000;
	return (double)curr / 10.0;
}

double Bk16XXPs::getCurrentReading() {
	std::string volt_curr = this->receive("GETD");
	volt_curr = volt_curr.substr(0, volt_curr.find("\r"));
	int volt_curr_int = stoi(volt_curr);
	double curr = floor((double)(volt_curr_int % 100000) / 10);
	return curr / 100;
}

void Bk16XXPs::setMaxCurrent(double curr) {
	curr *= 10;
	int curr_int = (int)curr;
	if (curr_int < 100) {
		this->send("SOCP0" + std::to_string(curr_int));
	}	
	else {
		this->send("SOCP" + std::to_string(curr_int));
	}
}

double Bk16XXPs::getMaxCurrent() {
	std::string max_curr = this->receive("GOCP");
	std::string current = max_curr.substr(0, max_curr.find("\r"));
	int curr_int = stoi(current);
	double curr = floor((double)curr_int / 10);
	return curr;
}

void Bk16XXPs::turnOn() {
	this->send("SOUT0");
}

void Bk16XXPs::turnOff() {
	this->send("SOUT1");
}











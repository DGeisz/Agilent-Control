#ifndef BK16XXPS_H
#define BK16XXPS_H

#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "SerialCom.h"

class Bk16XXPs {
	public:
		Bk16XXPs(std::string dev);
		~Bk16XXPs();

		void init();

		void setVoltage(double volt);
		double getVoltageSetting();
		double getVoltageReading();

		void setMaxVoltage(double volt);
		double getMaxVoltage();
		
		void setCurrent(double curr);
		double getCurrentSetting();
		double getCurrentReading();

		void setMaxCurrent(double curr);
		double getMaxCurrent();
	
		void turnOn();
		void turnOff();
		


	private:
		SerialCom *m_com;
		
		void send(std::string cmd);
		std::string receive(std::string cmd);

  		std::chrono::milliseconds m_wait{100};

};

#endif

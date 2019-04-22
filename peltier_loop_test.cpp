#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <chrono>
#include "SorensenPs.h"
#include "PID.h"
#include "SerialCom.h"

using namespace std;
using namespace std::chrono;

double voltage;
double kp = 3.;
double ki = .05;
double kd = 19.5;

double hot;
double cool;
double cold;

double set_point = -5.0;
double max_voltage = 4.91;
double magic_ratio = 12.58 / 4.91;

double go_time_temp = (max_voltage / kp); //2 
bool temp_reached = false;
bool first_read = true;

std::string arduino_port = "/dev/ttyACM0";
std::string ps_port = "/dev/ttyUSB0";
int gpib = 11;




int main(int argc, char *argv[]){
	SorensenPs PS(ps_port, gpib);

	/*std::cout<<"Enter Kp:"<<std::endl;
	std::string k_p;
	std::cin>> k_p;
	std::cout<<"Enter Ki:"<<std::endl;
	std::string k_i;
	std::cin>> k_i;
	std::cout<<"Enter Kd:"<<std::endl;
	std::string k_d;
	std::cin >> k_d;
	std::cout<<"Enter Temperature Setpoint:"<<std::endl;
	std::string set;
	std::cin >> set;
	set_point = stod(set);
	kp = stod(k_p);
	ki = stod(k_i);
	kd = stod(k_d);*/

	Pid TC(&voltage, kp, 0.0, 0.0);
	TC.set_sample_time(500);
	TC.set_output_limits(0, max_voltage);

	PS.setCh(2);
	PS.turnOn();
	PS.setVoltage(0.0);
	PS.setCh(1);
	PS.turnOn();
	PS.setVoltage(0.0);

	SerialCom Arduino(arduino_port, B9600);
	std::cout<<"Starting..."<<std::endl;
	sleep(1.5);

	Arduino.write("a");
	std::string buf;
	sleep(2.0);
	int r = Arduino.read(buf);
	std::cout<<buf<<std::endl;
	
	ofstream new_file;
	new_file.open("pid_data.txt");
	new_file.close();

	int number_loop = 0;

	auto start_time = high_resolution_clock::now();
	auto last_time = start_time;


	while (true){
		auto curr_time = high_resolution_clock::now();
		int dur = duration_cast<milliseconds>(curr_time - start_time).count();
		double total_duration = static_cast<double>(dur);
		int dur2 = duration_cast<milliseconds>(curr_time - last_time).count();
		double duration = static_cast<double>(dur2);

		Arduino.write("a");
		std::string buf; 
		sleep(2);
		int r = Arduino.read(buf);

		if (buf.length() > 14){ 
			

			std::string::size_type sz1;
			std::string::size_type sz2;

			hot = stod(buf, &sz1);
			std::string temp_holder;
			if (sz1 > 3){

				cool = stod(buf.substr(sz1), &sz2);
				temp_holder = buf.substr(sz1);

			}
			else{
				temp_holder = buf.substr(sz1);
				cool = 0;
			}
			

			if (sz2 > 3){
				std::string temp_holder2 = temp_holder.substr(sz2);
				cold = stod(buf.substr(sz1).substr(sz2));	
			}
			else{
				cold = 0;
			}
		}
		if (number_loop > 2){
			ofstream my_file;
			my_file.open("pid_data.txt", std::ios_base::app);
			double new_duration = total_duration / 1000;
			my_file <<new_duration<<" "<<hot<<" "<<cool<<" "<<cold<<" "<<set_point<<"\n";
			my_file.close();
	
			/*if (abs(set_point - cold) > go_time_temp){
				TC.set_tunings(kp, 0.0, 0.0);
			}
			else{
				TC.set_tunings(kp, ki, kd);
				temp_reached = true;
			}*/


			if (abs(set_point - cold) < go_time_temp or temp_reached){
				temp_reached = true;
				TC.set_tunings(kp, ki, kd);
				if (first_read){
					duration = 105;
					first_read = false;
				}
				if (TC.compute(cold, set_point, duration)){
					std::cout<<"Pid Calculated! "<<voltage<<std::endl;
					last_time = curr_time;
					PS.setCh(2);
					PS.setVoltage(voltage);
					PS.setCh(1);
					PS.setVoltage(voltage * magic_ratio);
				}
			}
			else{
				PS.setCh(1);
				PS.setVoltage(12.58);
				PS.setCh(2);
				PS.setVoltage(4.91);
				
			}


			/*if (TC.compute(cold, set_point, duration)){
				std::cout<<"Pid Calculated! "<<voltage<<std::endl;
				last_time = curr_time;
				PS.setVoltage(voltage);
			}*/
		}
		else{
			number_loop++;
		}
			std::cout<<"[Hot: "<<hot<<"  Cool: "<<cool<<"  Cold: "<<cold<<"]"<<" "<<std::endl;
		
		//sleep(2);
		//number_loop++;
	}
	PS.turnOff();
}


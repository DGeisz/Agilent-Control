#include "SerialCom.h"
#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[]){
	SerialCom Arduino("/dev/ttyACM0", B9600);
	std::cout<<"Wait 3 seconds then press any key"<<std::endl;
	std::string a;
	std::cin >> a;
	std::cout<<"Starting..."<<std::endl;
	Arduino.write(a);
	std::string buf;
	int r = Arduino.read(buf);
	//std::cout<< "[" << buf << "]" <<std::endl;
	auto begin_time = high_resolution_clock::now();
	ofstream data_file;
	data_file.open("temp_data.txt");
	data_file.close();
	//data_file <<duration<<" "<<hot<<" "<<cool<<" "<<cold<<"\n";
	double total_duration = 5000.00;
	bool run_loop = true;
	bool truth = false;
	int number_loop = 0;
	while (true){
		auto curr_time = high_resolution_clock::now();
		int dur = duration_cast<milliseconds>(curr_time - begin_time).count();
		double duration = static_cast<double>(dur);

		if (duration > total_duration){
			run_loop = false;
			}

		Arduino.write("a");
		std::string buf;
		int r = Arduino.read(buf);
		if (data_file.is_open()){
				truth = true;
			}
			else{
				truth = false;
			}
		if (buf.length() > 14){ 
			

			std::string::size_type sz1;
			std::string::size_type sz2;

			double hot = stod(buf, &sz1);

			double cool;
			if (sz1 > 3){

				cool = stod(buf.substr(sz1), &sz2);

			}
			else{
				cool = 0;
			}
				
			double cold;

			std::string temp_holder = buf.substr(sz1);
			if (sz2 > 3){
				std::string temp_holder2 = temp_holder.substr(sz2);
				cold = stod(buf.substr(sz1).substr(sz2));	
			}
			else{
				cold = 0;
			}
			if (number_loop > 2){
				ofstream my_file;
				my_file.open("temp_data.txt", std::ios_base::app);
				double new_duration = duration / 1000;
				my_file <<new_duration<<" "<<hot<<" "<<cool<<" "<<cold<<"\n";
				my_file.close();
				}		
			std::cout<<"[Hot: "<<hot<<"  Cool: "<<cool<<"  Cold: "<<cold<<"]"<<" "<<truth<<std::endl;
			}		
		sleep(1);
		number_loop++;
	}

	return 0;
}


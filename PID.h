#ifndef PID
#define PID
#include <iostream>
#include <chrono>


class Pid {
	public:
		Pid(double* Output, double Kp, double Ki, double Kd);
		bool compute(double input, double set_point, double duration);
		void set_output_limits(double min, double max);
		void set_tunings(double Kp, double Ki, double Kd);
		void set_sample_time(double new_time);
		double get_kp();
		double get_ki();
		double get_kd();
		
	private:
		double kp;
		double ki;
		double kd;
		double output;
		double *myOutput;
		//double *mySetpoint;
		double output_sum;
		bool first_compute;
		double last_input;
		double sample_time;
		double out_min, out_max;
};
#endif

		

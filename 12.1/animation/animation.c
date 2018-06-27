#include<iostream>
#include<fstream>
#include<cmath>
#include<ctime>
#include<cstdlib>
#define Pi 3.14159

using namespace std;

double random01(){
	return rand()/double(RAND_MAX);
}

double angle(double x, double y){
	double result = atan(y/x);
	if(x < 0) return result+Pi;
	if(y < 0) return result+2*Pi;
	return result;
}

int main(void){
	
	//parameters
	int n = 30;
	double eps = 0.2;
	double tprint = 160;
	double dt = 0.005;
	
	//random seed
	srand(time(0));
	
	//initial condition
	double phases[n];
	for(int i = 0; i < n; ++i) phases[i] = 2*Pi*random01();
	double omegas[n];
	for(int i = 0; i < n; ++i) omegas[i] = 1.0 + 0.1*random01();
	//mean field
	double x_avg = 0;
	for(int i = 0; i < n; ++i) x_avg += cos(phases[i]);
	x_avg /= n;
	double y_avg = 0;
	for(int i = 0; i < n; ++i) y_avg += sin(phases[i]);
	y_avg /= n;
	double R = sqrt(x_avg*x_avg + y_avg*y_avg);
	double theta = angle(x_avg, y_avg);
	
	int print_cnt = 0;
	//integrate and print to file
	for(double t = 0; t < tprint; t = t+dt){
		//individual
		for(int i = 0; i < n; ++i){
			phases[i] = phases[i] + (omegas[i] + eps*R*sin(theta-phases[i]))*dt;
		}
		//mean field
		x_avg = 0;
		for(int i = 0; i < n; ++i) x_avg += cos(phases[i]);
		x_avg /= n;
		y_avg = 0;
		for(int i = 0; i < n; ++i) y_avg += sin(phases[i]);
		y_avg /= n;
		R = sqrt(x_avg*x_avg + y_avg*y_avg);
		theta = angle(x_avg, y_avg);
		if(print_cnt%16 == 0){
			for(int i = 0; i < n; ++i){
				char buffer[100];
				snprintf(buffer, 100, "saves/f%d_%d.dat", i, print_cnt/16);
				ofstream fout_f(buffer);
				fout_f << cos(phases[i]) << ", " << sin(phases[i]) << endl;
			}
			char buffer[100];
			snprintf(buffer, 100, "saves/fmean_%d.dat", print_cnt/16);
			ofstream fout_f(buffer);
			fout_f << R*cos(theta) << ", " << R*sin(theta) << endl;
		}
		print_cnt++; 
	}
	
	return 0;
	
}

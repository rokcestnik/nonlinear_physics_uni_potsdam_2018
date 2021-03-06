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
	int n = 20;
	double tmax = 1000;
	double dt = 0.01;
	
	//random seed
	srand(time(0));
	
	//frequencies
	double omegas[n];
	for(int i = 0; i < n; ++i) omegas[i] = 1.0 + random01()*0.1;
	
	for(double eps = 0; eps < 0.1; eps += 0.001){
		//initial condition
		double phases[n];
		for(int i = 0; i < n; ++i) phases[i] = 0.3*i;
		//mean field
		double x_avg = 0;
		for(int i = 0; i < n; ++i) x_avg += cos(phases[i]);
		x_avg /= n;
		double y_avg = 0;
		for(int i = 0; i < n; ++i) y_avg += sin(phases[i]);
		y_avg /= n;
		double R = sqrt(x_avg*x_avg + y_avg*y_avg);
		double theta = angle(x_avg, y_avg);
		//time loop (warmup)
		for(double t = 0; t < tmax; t += dt){
			//individual oscillators
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
		}
		//reference phases (for evaluating effective frequencies)
		double ref_phases[n];
		for(int i = 0; i < n; ++i) ref_phases[i] = phases[i];
		//time loop (real run) 
		for(double t = 0; t < tmax; t += dt){
			//individual oscillators
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
		}
		for(int i = 0; i < n; ++i){
			cout << eps << ", " << (phases[i]-ref_phases[i])/tmax << endl;
		}
	}
	
	return 0;
	
}


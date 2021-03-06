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
	double tmax = 500;
	double dt = 0.01;
	
	//random seed
	srand(time(0));
	
	//files
	ofstream fout_r("R.dat");
	ofstream fout_t("theta.dat");
	
	//frequencies
	double omegas[n];
	for(int i = 0; i < n; ++i) omegas[i] = 1.0 + 0.1*random01();
		
	for(double eps = -0.1; eps < 0.14; eps += 0.002){
		//initial condition
		double phases[n];
		for(int i = 0; i < n; ++i) phases[i] = 2*Pi*random01();
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
		//average R
		double R_avg = 0;
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
			R_avg += R*dt;
		}
		cout << eps << ", " << R_avg/tmax << endl;
	}
	
	return 0;
	
}


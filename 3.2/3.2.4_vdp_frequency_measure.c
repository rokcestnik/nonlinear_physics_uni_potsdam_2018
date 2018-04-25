#include<iostream>
#include<fstream>
#define Pi 3.14159265358979

using namespace std;

double fx(double y){
	return y;
}
double fy(double x, double y, double mu){
	return mu*(1-x*x)*y-x;
}

void integrator(double *x, double *y, double mu, double dt){
	double kx1 = fx(*y);
	double ky1 = fy(*x, *y, mu);
	double kx2 = fx(*y + ky1*dt/2.0);
	double ky2 = fy(*x + kx1*dt/2.0, *y + ky1*dt/2.0, mu);
	double kx3 = fx(*y + ky2*dt/2.0);
	double ky3 = fy(*x + kx2*dt/2.0, *y + ky2*dt/2.0, mu);
	double kx4 = fx(*y + ky3*dt);
	double ky4 = fy(*x + kx3*dt, *y + ky3*dt, mu);
	*x = *x + (kx1+2*kx2+2*kx3+kx4)*dt/6.0;
	*y = *y + (ky1+2*ky2+2*ky3+ky4)*dt/6.0;
}

int main(){
	
	//parameters
	double mu = 2.5;
	double x0 = 1.0;
	double y0 = 1.0;
	double t0 = 0.0;
	double trelax = 50.0;
	double tsim = 300.0;
	double dt = 0.01;
	
	//integration
	double x = x0;
	double y = y0;
	//relaxation period - first we simulate the oscillator so it settles to its stable orbit
	for(double t = t0; t < trelax; t = t+dt){
		integrator(&x, &y, mu, dt);
	}
	//real simulation - now we measure the zero crossings in order to determine the frequency
	int period_counter = 0;
	double first_time;
	double last_time;
	for(double t = t0; t < tsim; t = t+dt){
		double previous_x = x;
		integrator(&x, &y, mu, dt);
		if(previous_x < 0 && x > 0){
			if(period_counter == 0){
				//this is the first zero crossing
				first_time = t;
			}
			else{
				//all further zero crossings
				last_time = t;
			}
			period_counter++;
		}
	}
	//determine the average period and frequency
	double period = (last_time-first_time)/(period_counter-1);
	double frequency = 2*Pi/period;
	//printout
	cout << "the frequency of the van der Pol oscillator with mu = " << mu << " is: " << frequency << endl;
	
	return 0;
	
}




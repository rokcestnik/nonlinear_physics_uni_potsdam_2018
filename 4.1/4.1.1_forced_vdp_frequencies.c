#include<iostream>
#include<cmath>
#define Pi 3.14159265358979

using namespace std;

//global variables
double mu, eps, wf;

double fx(double y){
	return y;
}
double fy(double x, double y, double t){
	return mu*(1-x*x)*y-x + eps*cos(wf*t);
}

void integrator(double *x, double *y, double t, double dt){
	double kx1 = fx(*y);
	double ky1 = fy(*x, *y, t);
	double kx2 = fx(*y + ky1*dt/2.0);
	double ky2 = fy(*x + kx1*dt/2.0, *y + ky1*dt/2.0, t+dt/2.0);
	double kx3 = fx(*y + ky2*dt/2.0);
	double ky3 = fy(*x + kx2*dt/2.0, *y + ky2*dt/2.0, t+dt/2.0);
	double kx4 = fx(*y + ky3*dt);
	double ky4 = fy(*x + kx3*dt, *y + ky3*dt, t+dt);
	*x = *x + (kx1+2*kx2+2*kx3+kx4)*dt/6.0;
	*y = *y + (ky1+2*ky2+2*ky3+ky4)*dt/6.0;
}

double frequency(void){
	double x0 = 1.0;
	double y0 = 1.0;
	double t0 = 0.0;
	double tmax = 1000.0;
	double tstabilize = 1000.0;
	double dt = 0.05;
	//integration
	double x = x0;
	double y = y0;
	//first let the system settle to stable oscillations
	for(double t = t0; t < tstabilize; t = t+dt){
		integrator(&x, &y, t, dt);
	}
	//and now measure the frequency
	int period_counter = 0;
	double first_time;
	double last_time;
	for(double t = t0; t < tstabilize; t = t+dt){
		double previous_x = x;
		integrator(&x, &y, t, dt);
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
	return 2*Pi/period;
}

int main(){
	
	//forcing parameters
	eps = 0.5;
	//oscillator parameters
	mu = 2.5;
	
	for(wf = 0.1; wf < 1.5; wf = wf+0.01){
		cout << wf << ", " << frequency() << endl;
	}
	
	return 0;
	
}




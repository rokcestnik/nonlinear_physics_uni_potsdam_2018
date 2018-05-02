#include<iostream>
#include<fstream>
#include<cmath>

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

int main(){
	
	//forcing parameters
	eps = 0.5;
	wf = 1.0;
	//oscillator parameters
	mu = 2.5;
	//other parameters
	double x0 = 1.0;
	double y0 = 1.0;
	double t0 = 0.0;
	double tmax = 50.0;
	double dt = 0.01;
	
	//output files
	ofstream fout_forcing("vdp_forcing.dat");
	ofstream fout_x("vdp_x.dat");
	ofstream fout_y("vdp_y.dat");
	ofstream fout_xy("vdp_xy.dat");
	
	//integration
	double x = x0;
	double y = y0;
	for(double t = t0; t < tmax; t = t+dt){
		integrator(&x, &y, t, dt);
		fout_forcing << t << ", " << eps*cos(wf*t) << endl;
		fout_x << t << ", " << x << endl;
		fout_y << t << ", " << y << endl;
		fout_xy << x << ", " << y << endl;
	}
	
	return 0;
	
}




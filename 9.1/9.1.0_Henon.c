#include<iostream>
#include<fstream>

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
	double mu = 1.0;
	double x0 = 1.0;
	double y0 = 1.0;
	double t0 = 0.0;
	double tmax = 1000.0;
	double dt = 0.01;
	
	//output files
	ofstream fout_x("vdp_x.dat");
	ofstream fout_y("vdp_y.dat");
	ofstream fout_xy("vdp_xy.dat");
	ofstream fout_sp("same_point.dat");
	
	//integration
	double x = x0;
	double y = y0;
	for(double t = t0; t < tmax; t = t+dt){
		integrator(&x, &y, mu, dt);
		fout_x << t << ", " << x << endl;
		fout_y << t << ", " << y << endl;
		fout_xy << x << ", " << y << endl;
	}
	
	//measure the frequency
	double xh = x;
	while((xh < 0 && x > 0) != 1){
		xh = x;
		integrator(&x,&y,mu,dt);
	}
	cout << "we're at a point where we first cross 0, xh = " << xh << " x = " << x << endl;
	//first Henon correction
	double time_correction = 1.0/fx(y)*(x-0.0);
	integrator(&x,&y, mu, -time_correction);
	cout << "x should be very very close to 0, and it is: " << x << endl;
	
	//start timing the period
	double period = 0;
	xh = 1;
	while((xh < 0 && x > 0) != 1){
		xh = x;
		integrator(&x,&y,mu,dt);
		period += dt;
	}
	//another Henon correction
	double time_correction2 = 1.0/fx(y)*(x-0.0);
	integrator(&x,&y, mu, -time_correction2);
	period -= time_correction2;
	cout << "period = " << period << endl;
	
	//first point (arbitrary)
	fout_sp << x << ", " << y << endl;
	for(int i = 0; i < 100; ++i){
		//now run for full period
		double last_t;
		for(double t = 0; t < period; t = t+dt){
			integrator(&x, &y, mu, dt);
			last_t = t+dt;
		}
		//correction
		integrator(&x,&y,mu, period-last_t);
		fout_sp << x << ", " << y << endl;
	}
	
	return 0;
	
}



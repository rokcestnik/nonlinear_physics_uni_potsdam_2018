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
	double mu = 0.1;
	double x0 = 1.0;
	double y0 = 1.0;
	double tmax = 300.0;
	double dt = 0.002;
	
	//output files
	ofstream fout_lc("vdp_lc.dat");
	ofstream fout_xy("vdp_xy.dat");
	ofstream fout_iso("vdp_iso.dat");
	
	//warmup integration
	double x = x0;
	double y = y0;
	for(double t = 0; t < tmax; t = t+dt){
		integrator(&x, &y, mu, dt);
	}
	
	//measure the period
	double xh = x;
	while((xh < 0 && x > 0) != 1){ //when this loop ends we will be at a point where x has just crossed 0 from below
		xh = x;
		integrator(&x, &y, mu, dt);
	}
	//...and now time how long it takes to cross zero from bellow another 1000 times
	double period = 0;
	for(int i = 0; i < 1000; ++i){
		xh = 1; //break the condition (xh < 0 && x > 0)
		while((xh < 0 && x > 0) != 1){
			xh = x;
			integrator(&x, &y, mu, dt);
			period += dt;
		}
	}
	period /= 1000;

	//printout the limit cycle
	for(double t = 0; t < 2*period; t = t+dt){
		integrator(&x, &y, mu, dt);
		fout_lc << x << ", " << y << endl;
	}
	
	//now get the points with the same time
	//first perturb x,y slightly
	x = x + 0.01;
	fout_iso << x << ", " << y << endl;
	for(int p = 0; p < 50; ++p){
		double last_t;
		for(double t = 0; t < period; t = t+dt){
			fout_xy << x << ", " << y << endl;
			integrator(&x, &y, mu, -dt);
			last_t = t;
		}
		//last bit of integration by hand, so we really complete the period
		integrator(&x, &y, mu, -(period-last_t));
		fout_iso << x << ", " << y << endl;
	}
	
	return 0;
	
}




#include<iostream>
#include<fstream>
#include<cmath>

using namespace std;

double fx(double x, double y){
	return 10*(y-x);
}
double fy(double x, double y, double z){
	return 28*x-y-x*z;
}
double fz(double x, double y, double z){
	return -8.0/3.0*z+x*y;
}

void integrator(double *x, double *y, double *z, double dt){
	double kx1 = fx(*x, *y);
	double ky1 = fy(*x, *y, *z);
	double kz1 = fz(*x, *y, *z);
	double kx2 = fx(*x + kx1*dt/2.0, *y + ky1*dt/2.0);
	double ky2 = fy(*x + kx1*dt/2.0, *y + ky1*dt/2.0, *z + kz1*dt/2.0);
	double kz2 = fz(*x + kx1*dt/2.0, *y + ky1*dt/2.0, *z + kz1*dt/2.0);
	double kx3 = fx(*x + kx2*dt/2.0, *y + ky2*dt/2.0);
	double ky3 = fy(*x + kx2*dt/2.0, *y + ky2*dt/2.0, *z + kz2*dt/2.0);
	double kz3 = fz(*x + kx2*dt/2.0, *y + ky2*dt/2.0, *z + kz2*dt/2.0);
	double kx4 = fx(*x + kx3*dt, *y + ky3*dt);
	double ky4 = fy(*x + kx3*dt, *y + ky3*dt, *z + kz3*dt);
	double kz4 = fz(*x + kx3*dt, *y + ky3*dt, *z + kz3*dt);
	*x = *x + (kx1+2*kx2+2*kx3+kx4)*dt/6.0;
	*y = *y + (ky1+2*ky2+2*ky3+ky4)*dt/6.0;
	*z = *z + (kz1+2*kz2+2*kz3+kz4)*dt/6.0;
}

int main(){
	
	//parameters
	double x0 = 1.0;
	double y0 = 5.0;
	double z0 = 10.0;
	double t0 = 0.0;
	double tmax = 15.0;
	double dt = 0.01;
	
	//output files
	ofstream fout_0("chaos_0.dat");
	ofstream fout_0001("chaos_0001.dat");
	ofstream fout_001("chaos_001.dat");
	ofstream fout_01("chaos_01.dat");
	
	//0 case
	double x_0 = x0 + 0;
	double y_0 = y0;
	double z_0 = z0;
	//0.001 case
	double x_0001 = x0 + 0.001;
	double y_0001 = y0;
	double z_0001 = z0;
	//0.01 case
	double x_001 = x0 + 0.01;
	double y_001 = y0;
	double z_001 = z0;
	//0.1 case
	double x_01 = x0 + 0.1;
	double y_01 = y0;
	double z_01 = z0;
	for(double t = t0; t < tmax; t = t+dt){
		integrator(&x_0, &y_0, &z_0, dt);
		integrator(&x_0001, &y_0001, &z_0001, dt);
		integrator(&x_001, &y_001, &z_001, dt);
		integrator(&x_01, &y_01, &z_01, dt);
		fout_0 << t << ", " << x_0 << endl;
		fout_0001 << t << ", " << x_0001 << endl;
		fout_001 << t << ", " << x_001 << endl;
		fout_01 << t << ", " << x_01 << endl;
	}
	
	return 0;
	
}




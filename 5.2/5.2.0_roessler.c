#include<iostream>
#include<fstream>
#include<cmath>

using namespace std;

double fx(double y, double z){
	return -y-z;
}
double fy(double x, double y){
	return x+0.15*y;
}
double fz(double x, double z){
	return 0.4+z*(x-8.5);
}

void integrator(double *x, double *y, double *z, double dt){
	double kx1 = fx(*y, *z);
	double ky1 = fy(*x, *y);
	double kz1 = fz(*x, *z);
	double kx2 = fx(*y + ky1*dt/2.0, *z + kz1*dt/2.0);
	double ky2 = fy(*x + kx1*dt/2.0, *y + ky1*dt/2.0);
	double kz2 = fz(*x + kx1*dt/2.0, *z + kz1*dt/2.0);
	double kx3 = fx(*y + ky2*dt/2.0, *z + kz2*dt/2.0);
	double ky3 = fy(*x + kx2*dt/2.0, *y + ky2*dt/2.0);
	double kz3 = fz(*x + kx2*dt/2.0, *z + kz2*dt/2.0);
	double kx4 = fx(*y + ky3*dt, *z + kz3*dt);
	double ky4 = fy(*x + kx3*dt, *y + ky3*dt);
	double kz4 = fz(*x + kx3*dt, *z + kz3*dt);
	*x = *x + (kx1+2*kx2+2*kx3+kx4)*dt/6.0;
	*y = *y + (ky1+2*ky2+2*ky3+ky4)*dt/6.0;
	*z = *z + (kz1+2*kz2+2*kz3+kz4)*dt/6.0;
}

int main(){
	
	//parameters
	double x0 = 5.0;
	double y0 = 5.0;
	double z0 = 1.0;
	double t0 = 0.0;
	double tmax = 60.0;
	double dt = 0.01;
	
	//output files
	ofstream fout_x("roessler_x.dat");
	ofstream fout_y("roessler_y.dat");
	ofstream fout_z("roessler_z.dat");
	ofstream fout_xy("roessler_xy.dat");
	ofstream fout_xyz("roessler_xyz.dat");
	
	//integration
	double x = x0;
	double y = y0;
	double z = z0;
	for(double t = t0; t < tmax; t = t+dt){
		integrator(&x, &y, &z, dt);
		fout_x << t << ", " << x << endl;
		fout_y << t << ", " << y << endl;
		fout_z << t << ", " << z << endl;
		fout_xy << x << ", " << y << endl;
		fout_xyz << x << ", " << y << ", " << z << endl;
	}
	
	return 0;
	
}




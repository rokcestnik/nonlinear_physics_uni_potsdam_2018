#include<iostream>
#include<fstream>
#include<cmath>
#include<stdlib.h>
#include"8.1.1_isochrones.h"
#define Pi 3.14159

using namespace std;

double mu; 

double fx(double y){
	return y;
}
double fy(double x, double y){
	return -x +mu*(1-x*x)*y; //van der pol
}

void integrator(double *x, double *y, double dt){
	double kx1 = fx(*y);
	double ky1 = fy(*x, *y);
	double kx2 = fx(*y + ky1*dt/2.0);
	double ky2 = fy(*x + kx1*dt/2.0, *y + ky1*dt/2.0);
	double kx3 = fx(*y + ky2*dt/2.0);
	double ky3 = fy(*x + kx2*dt/2.0, *y + ky2*dt/2.0);
	double kx4 = fx(*y + ky3*dt);
	double ky4 = fy(*x + kx3*dt, *y + ky3*dt);
	*x = *x + (kx1+2*kx2+2*kx3+kx4)*dt/6.0;
	*y = *y + (ky1+2*ky2+2*ky3+ky4)*dt/6.0;
}

double dist(double x, double y){
	return sqrt(x*x+y*y);
}

int main(){
	
	//parameters
	mu = 0.3;
	double delta = 0.0001;//0.001;
	int pp = 550;//50; //how many delta_t's I run
	double t0 = 0.0;
	double tmax = 600.0;//50;//600.0;
	double dt = 0.002;//0.0001;//0.002;
	
	//output file
	FILE *f;
	f = fopen("limit_cycle.dat", "wt");
	
	//integration
	double x = 2.2; //arbitrary initial condition
	double y = 3.3; //arbitrary initial condition
	//let the system go to the periodic orbit
	for(double t = t0; t < tmax; t = t+dt){
		integrator(&x, &y, dt);
	}
	//then measure the period (and print the orbit to file)
	double period = 0;
	int period_cnt = -1;
	double xh; //previous value of x
	double time_of_crossing;
	for(double t = t0; t < tmax; t = t+dt){
		integrator(&x, &y, dt);
		fprintf(f, "%lf, %lf\n", x, y);
		if(xh < 0 && x > 0){
			if(period_cnt == -1){ //the first time this crosses
				time_of_crossing = t;
				period_cnt = 0;
			}
			else{ //next times it crosses
				period += t-time_of_crossing;
				period_cnt++;
				time_of_crossing = t;
			}
		}
		xh = x;
	}
	fclose(f);
	period /= period_cnt;
	cout << "period duration: " << period << endl;
	//measure the average x and y
	double x_avg = 0;
	double y_avg = 0;
	int x_cnt = 0;
	int y_cnt = 0;
	for(double t = t0; t < period; t = t+dt){ //average over one period
		integrator(&x, &y, dt);
		x_avg += x;
		y_avg += y;
		x_cnt++;
		y_cnt++;
	}
	x_avg /= x_cnt;
	y_avg /= y_cnt;
	cout << "periodic orbit center: " << x_avg << ", " << y_avg << endl;
	//get points on the period orbit, perturb them and run backwards in time
	double delta_t = period/N;
	//initialize the files
	for(int p = 0; p < N; ++p){
		char buffer[100];
		snprintf(buffer, 100, "data/%d_in.dat", p);
		f = fopen(buffer, "wt");
		fclose(f);
		snprintf(buffer, 100, "data/%d_out.dat", p);
		f = fopen(buffer, "wt");
		fclose(f);
	}
	//start running
	double x_in[N];
	double y_in[N];
	double x_out[N];
	double y_out[N];
	double x_in_h[N];
	double y_in_h[N];
	double x_out_h[N];
	double y_out_h[N];
	double x0 = x;
	double y0 = y;
	for(int i = 0; i < N; ++i){
		for(double t = t0; t < delta_t; t = t+dt){
			integrator(&x0, &y0, dt);
		}
		double delta_x = x_avg-x0;
		double delta_y = y_avg-y0;
		//perturb in
		x = x0 + delta*delta_x/dist(delta_x,delta_y);
		y = y0 + delta*delta_y/dist(delta_x,delta_y);
		x_in[i] = x;
		y_in[i] = y;
		//perturb out
		x = x0 - delta*delta_x/dist(delta_x,delta_y);
		y = y0 - delta*delta_y/dist(delta_x,delta_y);
		x_out[i] = x;
		y_out[i] = y;
	}
	for(int p = 0; p < pp; ++p){
		//print
		for(int i = 0; i < N; ++i){
			int index = (10*N+i-p)%N;
			char buffer[100];
			snprintf(buffer, 100, "data/%d_in.dat", index);
			f = fopen(buffer, "at");
			if(x_in[i] == x_in[i] && y_in[i] == y_in[i]){
				fprintf(f, "%lf, %lf\n", x_in[i], y_in[i]);
			}
			fclose(f);
			snprintf(buffer, 100, "data/%d_out.dat", index);
			f = fopen(buffer, "at");
			if(x_out[i] == x_out[i] && y_out[i] == y_out[i]){
				fprintf(f, "%lf, %lf\n", x_out[i], y_out[i]);
			}
			fclose(f);
		}
		//perturb
		for(int i = 0; i < N; ++i){
			int index = (10*N+i-p)%N;
			x_in_h[index] = x_in[i];
			y_in_h[index] = y_in[i];
			x_out_h[index] = x_out[i];
			y_out_h[index] = y_out[i];
			for(double t = 0; t < delta_t; t = t+dt){
				integrator(&(x_in[i]), &(y_in[i]), -dt); //notice we're going back in time
				integrator(&(x_out[i]), &(y_out[i]), -dt); //notice we're going back in time
			}
		}
	}
	
	return 0;
	
}



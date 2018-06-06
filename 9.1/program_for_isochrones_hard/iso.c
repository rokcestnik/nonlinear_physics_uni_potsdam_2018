#include<iostream>
#include<fstream>
#include<cmath>
#include<stdlib.h>
#include"iso.h"
#define Pi 3.14159

using namespace std;

double II = 0.07; //0.07 //0.25 
double CC = 1;
double gL = 0.5;
double gCa = 1.33; //1.33 //1.1
double gK = 2;
double VL = -0.5;
double VCa = 1;
double VK = -0.7;
double V1 = -0.01;
double V2 = 0.15;
double V3 = 0.1; //0.1 //0.0
double V4 = 0.145; //0.145 //0.3
double fi = 1.0/3; //1.0/3 //0.2

double Mss(double V){
	return 0.5*(1+tanh((V-V1)/V2));
}
double Nss(double V){
	return 0.5*(1+tanh((V-V3)/V4));
}
double tauN(double V){
	return 1.0/(fi*cosh((V-V3)/(2*V4)));
}
double fx(double V, double N, double I){
	return (I-gL*(V-VL)-gCa*Mss(V)*(V-VCa)-gK*N*(V-VK))/CC;
} 
double fy(double V, double N){
	return (Nss(V)-N)/tauN(V);
}

void integrator(double *V, double *N, double dt){
	double I = II;
	double Vk1 = fx(*V, *N, I);
	double Nk1 = fy(*V, *N);
	double Vk2 = fx(*V+dt/2*Vk1, *N+dt/2*Nk1, I);
	double Nk2 = fy(*V+dt/2*Vk1, *N+dt/2*Nk1);
	double Vk3 = fx(*V+dt/2*Vk2, *N+dt/2*Nk2, I);
	double Nk3 = fy(*V+dt/2*Vk2, *N+dt/2*Nk2);
	double Vk4 = fx(*V+dt*Vk3, *N+dt*Nk3, I);
	double Nk4 = fy(*V+dt*Vk3, *N+dt*Nk3);
	*V += (Vk1+2*Vk2+2*Vk3+Vk4)/6*dt;
	*N += (Nk1+2*Nk2+2*Nk3+Nk4)/6*dt;
}

double dist(double x, double y){
	return sqrt(x*x+y*y);
}

int main(){
	
	//parameters
	double delta = 0.00001; //how much to perturb
	int pp = 1*N; //how many delta_t's I run
	double tmax = 1000.0;
	double dt = 0.005;
	double thr = 0.0;
	
	//just variables
	double last_t;
		
	//output file
	FILE *f;
	f = fopen("limit_cycle.dat", "wt");
	fclose(f);
	
	//warmup integration
	double x = -0.4; //arbitrary initial condition
	double y = 0.1; //arbitrary initial condition
	//let the system go to the periodic orbit
	for(double t = 0; t < tmax; t = t+dt){
		integrator(&x, &y, dt);
	}
	
	//measure the period
	double xh = x; //previous x
	while((xh < thr && x > thr) != 1){ //when this loop ends we will be at a point where x has just crossed 0 from below
		xh = x;
		integrator(&x, &y, dt);
	}
	//Henon trick
	double rest_t_1 = 1.0/fx(x,y,0)*(x-thr);
	integrator(&x, &y, -rest_t_1); //integrate back to zero
	//prvic na roke da je zih x > 0
	double period = 0;
	integrator(&x, &y, dt);
	period += dt;
	//...and now time how long it takes to cross zero from bellow again
	xh = 1; //break the condition (xh < thr && x > thr)
	while((xh < thr && x > thr) != 1){
		xh = x;
		integrator(&x, &y, dt);
		period += dt;
	}
	//Henon trick
	double rest_t_2 = 1.0/fx(x,y,0)*(x-thr);
	integrator(&x, &y, -rest_t_2); //integrate back to zero
	period = period-rest_t_2; 
	
	//test
	/*integrator(&x, &y, dt/2.0);
	f = fopen("test.dat", "wt");
	for(int i = 0; i < 1000; ++i){
		for(double t = 0; t < period; t = t+dt){
			integrator(&x, &y, dt);
			last_t = t+dt;
		}
		integrator(&x, &y, period-last_t);
		fprintf(f, "%lf, %lf\n", x, y);
	}
	fclose(f);*/
	
	//print the orbit to file
	double start_x = x;
	double start_y = y;
	f = fopen("limit_cycle.dat", "wt");
	for(double t = 0; t < period; t = t+dt){
		fprintf(f, "%lf, %lf\n", x, y);
		integrator(&x, &y, dt);
	}
	//twice more for good measure
	fprintf(f, "%lf, %lf\n", x, y);
	integrator(&x, &y, dt);
	fprintf(f, "%lf, %lf\n", start_x, start_y);
	fclose(f);

	//measure the average x and y
	double x_avg = 0;
	double y_avg = 0;
	int x_cnt = 0;
	int y_cnt = 0;
	for(double t = 0; t < period; t = t+dt){ //average over one period
		integrator(&x, &y, dt);
		x_avg += x;
		y_avg += y;
		x_cnt++;
		y_cnt++;
	}
	x_avg /= x_cnt;
	y_avg /= y_cnt;
	
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
		for(double t = 0; t < delta_t; t = t+dt){
			integrator(&x0, &y0, dt);
			last_t = t+dt;
		}
		//last bit by hand
		integrator(&x0, &y0, (delta_t-last_t));
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
		if(p%10 == 0) printf("p = %d/%d\n", p, pp);
		//print
		for(int i = 0; i < N; ++i){
			int index = (100*N+i-p)%N;
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
			int index = (100*N+i-p)%N;
			x_in_h[index] = x_in[i];
			y_in_h[index] = y_in[i];
			x_out_h[index] = x_out[i];
			y_out_h[index] = y_out[i];
			for(double t = 0; t < delta_t; t = t+dt){
				integrator(&(x_in[i]), &(y_in[i]), -dt); //notice we're going back in time
				integrator(&(x_out[i]), &(y_out[i]), -dt); //notice we're going back in time
				last_t = t+dt;
			}
			//last bit by hand
			integrator(&(x_in[i]), &(y_in[i]), -(delta_t-last_t)); //notice we're going back in time
			integrator(&(x_out[i]), &(y_out[i]), -(delta_t-last_t)); //notice we're going back in time
		}
	}
	
	return 0;
	
}



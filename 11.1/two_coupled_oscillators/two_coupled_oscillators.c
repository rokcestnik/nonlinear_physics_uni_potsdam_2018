#include<iostream>
#include<fstream>
#include<cmath>

using namespace std;

double coupling(double f1, double f2){
	return -sin(f1-f2);
}

double df(double f1,double f2, double w, double eps){
	return w + eps*coupling(f1,f2);
}

void integrate(double *f1, double *f2, double w1, double w2, double eps21, double eps12, double dt){
	double kf1_1 = df(*f1,*f2,w1,eps21);
	double kf2_1 = df(*f2,*f1,w2,eps12);
	double kf1_2 = df(*f1+kf1_1/2.0*dt,*f2+kf2_1/2.0*dt,w1,eps21);
	double kf2_2 = df(*f2+kf2_1/2.0*dt,*f1+kf1_1/2.0*dt,w2,eps12);
	double kf1_3 = df(*f1+kf1_2/2.0*dt,*f2+kf2_2/2.0*dt,w1,eps21);
	double kf2_3 = df(*f2+kf2_2/2.0*dt,*f1+kf1_2/2.0*dt,w2,eps12);
	double kf1_4 = df(*f1+kf1_3*dt,*f2+kf2_3*dt,w1,eps21);
	double kf2_4 = df(*f2+kf2_3*dt,*f1+kf1_3*dt,w2,eps12);
	*f1 = *f1 + (kf1_1+2*kf1_2+2*kf1_3+kf1_4)/6.0*dt;
	*f2 = *f2 + (kf2_1+2*kf2_2+2*kf2_3+kf2_4)/6.0*dt;
}

int main(void){
	
	//parameters
	double w1 = 1.0;
	double w2 = 2.5;
	double eps21 = 0.8;
	double eps12 = 0.4;
	double tprint = 4;
	double dt = 0.01;
	//parameter that controls the speed and simulation time (we keep the number of snapshots constant)
	int resolution = 3;
	
	//initial condition
	double f1 = 0;
	double f2 = 3;
	
	int counter = 0;
	//integrate
	for(double t = 0; t < resolution*tprint; t = t+dt){
		integrate(&f1, &f2, w1, w2, eps21, eps12, dt);
		//file print
		if(counter%resolution == 0){
			char buff[100];
			snprintf(buff, 100, "saved_files/f1_%d.dat", counter/resolution);
			ofstream fout_f1(buff);
			fout_f1 << cos(f1) << ", " << sin(f1) << endl;
			snprintf(buff, 100, "saved_files/f2_%d.dat", counter/resolution);
			ofstream fout_f2(buff);
			fout_f2 << cos(f2) << ", " << sin(f2) << endl;
		}
		counter++;
	}
	
	return 0;
	
}

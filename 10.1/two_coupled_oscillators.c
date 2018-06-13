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
	double eps21 = 0.5;
	double eps12 = 0.2;
	double tprint = 20;
	double tmax = 200;
	double dt = 0.01;
	
	//output files
	ofstream fout_f1("f1.dat");
	ofstream fout_f2("f2.dat");
	
	//initial condition
	double f1 = 0;
	double f2 = 0;
	
	//integrate and print to file
	for(double t = 0; t < tprint; t = t+dt){
		integrate(&f1, &f2, w1, w2, eps21, eps12, dt);
		fout_f1 << t << ", " << fmod(f1,2*3.14159) << endl;
		fout_f2 << t << ", " << fmod(f2,2*3.14159) << endl;
	}
	
	//integrate to measure effective frequency
	double f1_0 = f1;
	double f2_0 = f2;
	for(double t = 0; t < tmax; t = t+dt){
		integrate(&f1, &f2, w1, w2, eps21, eps12, dt);
	}
	printf("1: true w = %lf, effective w = %lf\n", w1, (f1-f1_0)/tmax);
	printf("2: true w = %lf, effective w = %lf\n", w2, (f2-f2_0)/tmax);
	
	return 0;
	
}


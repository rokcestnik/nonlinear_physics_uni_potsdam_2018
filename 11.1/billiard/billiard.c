#include<iostream>
#include<fstream>
#include<cmath>
#include<cstdlib>
#include<ctime>

using namespace std;

double random01(){
	return rand()/double(RAND_MAX);
}

int main(void){
	
	srand(time(0));
	
	double dt = 0.1;
	double thryup = 1;
	double thrydown = -1;
	double thrxup = 3;
	double thrxdown = -2;
	
	double x = (thrxup-thrxdown)*random01()-(thrxup-thrxdown)/2;
	double y = (thryup-thrydown)*random01()-(thryup-thrydown)/2;
	double angle = random01()*2*3.14159;
	double vx = cos(angle);
	double vy = sin(angle);
	
	for(int i = 0; i < 500; ++i){
		x = x+vx*dt;
		y = y+vy*dt;
		if(x > thrxup || x < thrxdown) vx = -vx;
		if(y > thryup || y < thrydown) vy = -vy;
		char buff[100];
		snprintf(buff, 100, "saved_files/f_%d.dat", i);
		ofstream fout_f1(buff);
		fout_f1 << x << ", " << y << endl;
	}
	
	
	return 0;
	
}


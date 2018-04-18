#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>

using namespace std;

double random01(){
	return rand()/double(RAND_MAX);
}

double fR(double zR, double zI, double cR, double cI){
	return zR*zR - zI*zI + cR;
}
double fI(double zR, double zI, double cR, double cI){
	return 2*zR*zI + cI;
}

double absval(double zR, double zI){
	return sqrt(zR*zR + zI*zI);
}

bool in_mandelbrot_boundary(double cR, double cI){
	bool goes_fast = 0;
	bool goes_slow = 0;
	double zR = 0;
	double zI = 0;
	for(int i = 0; i < 100; ++i){
		double zR_tmp = zR;
		double zI_tmp = zI;
		zR = fR(zR_tmp, zI_tmp, cR, cI);
		zI = fI(zR_tmp, zI_tmp, cR, cI);
		if(absval(zR, zI) > 2){
			goes_fast = 1;
			break;
		}
	}
	for(int i = 0; i < 100; ++i){
		double zR_tmp = zR;
		double zI_tmp = zI;
		zR = fR(zR_tmp, zI_tmp, cR, cI);
		zI = fI(zR_tmp, zI_tmp, cR, cI);
		if(absval(zR, zI) > 2){
			goes_slow = 1;
			break;
		}
	}
	if(goes_fast == 0 && goes_slow == 1) return 1;
	return 0;
}

int main(){
	
	srand(time(0));

	for(int i = 0; i < 5000000; ++i){
		double cR = random01()*4 - 2;
		double cI = random01()*4 - 2;
		if(in_mandelbrot_boundary(cR, cI)) cout << cR << ", " << cI << endl;
	}
	
	return 0;
	
}



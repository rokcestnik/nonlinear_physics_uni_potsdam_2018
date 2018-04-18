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

int main(){
	
	srand(time(0));

	double cR = random01()*4 - 2;
	double cI = random01()*4 - 2;
	
	bool in_set = 1;
	double zR = 0;
	double zI = 0;
	for(int i = 0; i < 100; ++i){
		zR = fR(zR, zI, cR, cI);
		zI = fI(zR, zI, cR, cI);
		if(absval(zR, zI) > 2){
			in_set = 0;
			break;
		}
	}
	if(in_set) cout << "the number " << cR << " + " << cI << "*i  is (probably) in the Mandelbrot set" << endl;
	else cout << "the number " << cR << " + " << cI << "*i  is not in the Mandelbrot set" << endl;
	
	return 0;
	
}



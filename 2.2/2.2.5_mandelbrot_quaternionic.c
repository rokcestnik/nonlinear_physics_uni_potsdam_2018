#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<string>

using namespace std;

double random01(){
	return rand()/double(RAND_MAX);
}

double fR(double qR, double qI, double qJ, double qK, double cR, double cI, double cJ, double cK){
	return qR*qR - qI*qI -qJ*qJ - qK*qK + cR;
}
double fI(double qR, double qI, double qJ, double qK, double cR, double cI, double cJ, double cK){
	return 2*qR*qI + cI;
}
double fJ(double qR, double qI, double qJ, double qK, double cR, double cI, double cJ, double cK){
	return 2*qR*qJ + cJ;
}
double fK(double qR, double qI, double qJ, double qK, double cR, double cI, double cJ, double cK){
	return 2*qR*qK + cK;
}

double absval(double qR, double qI, double qJ, double qK){
	return sqrt(qR*qR + qI*qI + qJ*qJ + qK*qK);
}

bool in_mandelbrot_boundary(double cR, double cI, double cJ, double cK){
	bool goes_fast = 0;
	bool goes_slow = 0;
	double qR = 0;
	double qI = 0;
	double qJ = 0;
	double qK = 0;
	for(int i = 0; i < 100; ++i){
		double qR_tmp = qR;
		double qI_tmp = qI;
		double qJ_tmp = qJ;
		double qK_tmp = qK;
		qR = fR(qR_tmp, qI_tmp, qJ_tmp, qK_tmp, cR, cI, cJ, cK);
		qI = fI(qR_tmp, qI_tmp, qJ_tmp, qK_tmp, cR, cI, cJ, cK);
		qJ = fJ(qR_tmp, qI_tmp, qJ_tmp, qK_tmp, cR, cI, cJ, cK);
		qK = fK(qR_tmp, qI_tmp, qJ_tmp, qK_tmp, cR, cI, cJ, cK);
		if(absval(qR, qI, qJ, qK) > 2){
			goes_fast = 1;
			break;
		}
	}
	for(int i = 0; i < 100; ++i){
		double qR_tmp = qR;
		double qI_tmp = qI;
		double qJ_tmp = qJ;
		double qK_tmp = qK;
		qR = fR(qR_tmp, qI_tmp, qJ_tmp, qK_tmp, cR, cI, cJ, cK);
		qI = fI(qR_tmp, qI_tmp, qJ_tmp, qK_tmp, cR, cI, cJ, cK);
		qJ = fJ(qR_tmp, qI_tmp, qJ_tmp, qK_tmp, cR, cI, cJ, cK);
		qK = fK(qR_tmp, qI_tmp, qJ_tmp, qK_tmp, cR, cI, cJ, cK);
		if(absval(qR, qI, qJ, qK) > 2){
			goes_slow = 1;
			break;
		}
	}
	if(goes_fast == 0 && goes_slow == 1) return 1;
	return 0;
}

int main(int argc, char*argv[]){
	
	srand(time(0));

	for(int i = 0; i < 5000000; ++i){
		double cR = random01()*4 - 2;
		double cI = random01()*4 - 2;
		double cJ = atof(argv[1]);
		double cK = 0;
		if(in_mandelbrot_boundary(cR, cI, cJ, cK)) cout << cR << ", " << cI << endl;
	}
	
	return 0;
	
}



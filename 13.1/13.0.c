#include<iostream>
#include<cmath>
#include<ctime>
#include<cstdlib>

using namespace std;

double random01(){
	return rand()/double(RAND_MAX);
}

int main(void){
	
	//parameters
	double min = 2;
	double range = 0.5;
	
	//random seed
	srand(time(0));
	
	//random numbers sampling
	for(int i = 0; i < 100000; ++i){
		cout << min + range*random01() << endl;
	}
	
	return 0;
	
}


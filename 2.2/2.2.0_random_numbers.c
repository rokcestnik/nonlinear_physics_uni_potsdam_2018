#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

//funtion returning a uniformly distributed random number between 0 and 1
double random01(){
	return rand()/double(RAND_MAX);
}

int main(){
	
	//random seed
	srand(time(0));
	
	//random number generation
	double r = random01();
	cout << r << endl;
	
	return 0;
	
}


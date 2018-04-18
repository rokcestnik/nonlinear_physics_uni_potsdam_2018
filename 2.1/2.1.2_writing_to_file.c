#include<iostream>
#include<fstream>

using namespace std;

int main(){
	
	ofstream fout1("name.dat");		//file
	fout1.setf(ios::scientific);	//format
	fout1.precision(12);			//precision
	
	double a = 1.0/3;
	fout1 << a << endl;

	int b = 0;
	int c = 1;
	int tmp;
	for(int i = 0; i < 20; ++i){
		tmp = b+c;
		b = c;
		c = tmp;
		fout1 << c/double(b) << endl;
	}
	
	return 0;
	
}


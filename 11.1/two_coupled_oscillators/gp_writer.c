#include<iostream>
#include<fstream>
#include<cmath>

using namespace std;

int main(void){

	ofstream fout("gp_animation");
	
	fout << "set terminal gif animate delay 2" << endl;
	fout << "set output \"anim.gif\"" << endl;
	fout << "set xrange [-1.1:1.1]" << endl;
	fout << "set yrange [-1.1:1.1]" << endl;
	fout << "set size ratio -1" << endl;
	fout << "set nokey" << endl;
	fout << "set object circle at 0,0 size 1" << endl;
	
	for(int i = 0; i < 400; ++i){
		fout << "plot \"saved_files/f1_" << i << ".dat\" with points pointtype 7 pointsize 2, \\" << endl;
		fout << "     \"saved_files/f2_" << i << ".dat\" with points pointtype 7 pointsize 2" << endl;
	}
	
	return 0;
	
}

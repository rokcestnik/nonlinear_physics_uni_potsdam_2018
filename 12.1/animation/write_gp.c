#include<iostream>
#include<fstream>

using namespace std;

int main(void){

	ofstream fout("gp");
	
	fout << "set terminal gif animate delay 4" << endl;
	fout << "set output \"anim.gif\"" << endl;
	fout << "set xrange [-1.3:1.3]" << endl;
	fout << "set yrange [-1.3:1.3]" << endl;
	fout << "set size ratio -1" << endl;
	fout << "set nokey" << endl;
	
	fout << "set object circle at 0,0 size 1" << endl;
	
	int n = 30;
	for(int k = 0; k < 500; ++k){
		fout << "plot \"saves/f0_" << k << ".dat\" with points pointtype 7 pointsize 2 lc rgb \"#999999\", \\" << endl;
		for(int i = 1; i < n; ++i){
			fout << "     \"saves/f" << i << "_" << k << ".dat\" with points pointtype 7 pointsize 2 lc rgb \"#999999\", \\" << endl;
		}
		fout << "     \"saves/fmean_" << k << ".dat\" with points pointtype 7 pointsize 3 lc rgb \"#FF0000\"" << endl;
	}
	
	return 0;
	
}

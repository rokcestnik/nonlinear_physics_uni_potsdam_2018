rm freq.dat
g++ 4.1.1_forced_vdp_frequencies.c
./a.out >> freq.dat
gnuplot gp_vdp_freq

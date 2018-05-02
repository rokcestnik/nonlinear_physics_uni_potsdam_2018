rm vdp_forcing.dat
rm vdp_x.dat
rm vdp_y.dat
rm vdp_xy.dat
g++ 4.1.0_forced_vdp.c
./a.out
gnuplot gp_vdp

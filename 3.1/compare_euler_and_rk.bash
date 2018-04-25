rm euler.dat
rm rk.dat
g++ 3.1.2_euler_as_integrator.c
./a.out >> euler.dat
g++ 3.1.3_runge_kutta_4.c
./a.out >> rk.dat
gnuplot gp_exp

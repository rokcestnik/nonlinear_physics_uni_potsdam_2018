rm boundary_q1.dat
rm boundary_q2.dat
rm boundary_q3.dat
rm boundary_q4.dat
rm boundary_q5.dat
g++ 2.2.5_mandelbrot_quaternionic.c
./a.out 0.0 >> boundary_q1.dat
./a.out 0.15 >> boundary_q2.dat
./a.out 0.30 >> boundary_q3.dat
./a.out 0.45 >> boundary_q4.dat
./a.out 0.60 >> boundary_q5.dat
gnuplot gp_boundary_q

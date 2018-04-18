rm boundary.dat
g++ 2.2.4_mandelbrot_complex_boundary.c
./a.out >> boundary.dat
gnuplot gp_boundary

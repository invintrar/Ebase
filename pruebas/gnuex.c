#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

FILE *p;
#define SIZE 500
float x[SIZE] = {0};
float y[SIZE] = {0};
float z[SIZE] = {0};

void plot_array(float *x, float *y, int n) ;
void llenar(int n);

int main()
{
    p = popen("gnuplot", "w");
    
    fprintf(p, "set ylabel 'Aceleracion'\n"
    "set xlabel 'Run time [sec]'\n");
    fprintf(p,"set grid\n");
    for(int j = 0; j < 1000; j++){
        llenar(SIZE);
        plot_array(x,y,SIZE);
        plot_array(x,z,SIZE);
    }
    fprintf(p,"exit gnuplot\n");
    pclose(p);
    return 0;
}
void llenar(int n)
{
    for(int i = 0; i < n; i++){
        x[i] = rand();
        y[i] =  x[i]*-1;
        z[i] =  rand();
    }
}

void plot_array(float *x, float *y, int n) 
{
    //fprintf(p, "plot '-' u 1 title 'Eje X' with lines,'-' u 2 title 'Eje Y' w l, '-' u 3 title 'Eje Z' w l\n");
    fprintf(p, "plot '-' u 1 title 'Eje X' with lines,'-' u 1 title 'Eje Y' with lines, '-' u 1 title 'Eje Z' with lines\n");
    
    for(int i = 0; i < n; i++){
        fprintf(p, "%.2f\t%.2f\n", x[i]);
    }
    fprintf(p, "e\n");
    fflush(p);

    for(int i = 0; i < n; i++){
        fprintf(p, "%.2f\n", y[i]);
    }
    fprintf(p, "e\n");
    fflush(p);

    for(int i = 0; i < n; i++){
        fprintf(p, "%.2f\n", z[i]);
    }
    fprintf(p, "e\n");
    fflush(p);
    
}

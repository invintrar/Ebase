#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

FILE *p;
float x[200] = {0};
float y[200] = {0};
float z[200] = {0};
int j;
void plot_array(float *x, float *y, char name, int n) ;
void llenar();

int main(){
    j = 0;
    p = popen("gnuplot", "w");
    
    fprintf(p, "set ylabel 'Aceleracion'\n"
    "set xlabel 'Run time [sec]'\n");
    fprintf(p,"set grid\n");
    for(int j = 0; j < 1000; j++){
        llenar();
        plot_array(x,y,'Y',200);
        plot_array(x,z,'Z',200);
    }
    pclose(p);
    return 0;
}
void llenar(){
    for(int i = 0; i < 200; i++){
        x[i] = j;
        y[i] = rand();
        z[i] = rand();
        j++; 
    }
    
}

void plot_array(float *x, float *y,char name, int n) 
{
    fprintf(p, "plot '-' u 1:2 title 'Eje %c' with lines\n",name);
    for(int i = 0; i < n; i++){
        fprintf(p, "%.2f %.2f\n", x[i], y[i]);
    }
    fprintf(p, "e\n");
    fflush(p);
}

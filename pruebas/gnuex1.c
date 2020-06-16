#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

FILE *archivo;
int fX, fY, fZ, current, j, ret;
char running;

void videoCapture(void);

int main(){
    fX = fY = fZ = current = j = 0;
    char tmp[100] = {0};
    int i = 0;
    running = 1;

    for(i = 0; i<100; i++){
        archivo = fopen("logfile","at");
        if(archivo == NULL)
        {
            printf("Error al crear el archivo\n");
        }
        else
        {
            fX = rand();
            fY = rand();
            fZ = rand();
            current = rand();
            fprintf(archivo, "%10d\t%10d\t%10d\t%10d\t%10d\n",j, fX, fY, fZ, current);
			fclose(archivo);
		}
        j++;
        sleep(0.03);
    }

    videoCapture();

    while(running){
        archivo = fopen("logfile","at");
        if(archivo == NULL)
        {
            printf("Error al crear el archivo\n");
        }
        else
        {
            fX = rand();
            fY = rand();
            fZ = rand();
            current = rand();
            fprintf(archivo, "%10d\t%10d\t%10d\t%10d\t%10d\n",j, fX, fY, fZ, current);
			fclose(archivo);
		}
        j++;
        if(j>200000){
            exit(EXIT_SUCCESS);
            _exit(ret);
            break;
        }
            
        sleep(0.03);
    }
    return 0;
}

void videoCapture(void)
{
	pid_t pid;
	printf("Iniciando grafica...\n");
	pid = fork();
    if(pid == -1)
        perror("fork");
    /* the childe ... */
    if(!pid){
        char *const args[] = {"gnuplot" ,"monitor.gp", NULL};
        ret = execvp ("gnuplot", args);
        if (ret == -1){
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>


typedef struct dato
{
	char *cadena;
	int x,y;
}parametro;

void gotoxy(int x, int y){
	printf("\033[%d;%df", y, x);
}

void *saludo(void *args){
	unsigned char i;
	parametro *p =(parametro *) args ;
	for (i=0;i < strlen(p->cadena); i++){
		fflush(stdout);
		gotoxy(p->x,p->y);
		p->x++;
		printf("%c", p->cadena[i]);
		sleep(1);
	}
	printf("\n");
}

int main(int argc, char const *argv[])
{
	pthread_t hilo1, hilo2;
	parametro p1,p2;
	p1.cadena = "Hola";
	p1.x = 10;
	p1.y = 20;
	p2.cadena = "Mundo";
	p2.x = 20;
	p2.y = 20;
	pthread_create(&hilo1,NULL,saludo ,(void *)&p1);
	pthread_create(&hilo2,NULL,saludo ,(void *)&p2);
	pthread_join(hilo1,NULL);
	pthread_join(hilo2,NULL);

	return 0;
}

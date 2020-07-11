/**
 * @file main.h
 * @author DzhL (invintrar@gmail.com)
 * @brief  Use for definition variables and function prototype
 * @version 1.2
 * @date 2020-06-02
 * 
 * 
 */
#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <wiringPi.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/mman.h>
#include "nrf24l01.h"
#include "gps.h"
#include <X11/Xlib.h>
/**
 * @brief Define macros use en the program
 * 
 */
#define _XOPEN_SOURCE       700
#define LED 		        7
#define Led_SetOutput()		pinMode(LED, OUTPUT)
#define LedOn()        		digitalWrite(LED, HIGH)
#define LedOff()		 	digitalWrite(LED, LOW)


/**
 * @brief Variable global use in the program
 * 
 */
// Flag for control NRF24L01+
uint8_t bNrf = 0;
/* 
*  Usado para el boton multiestado 
*  1: Sincronizar
*  2: Iniciar Prueba 
*  3: Apagar modulo NRF
*/
uint8_t opcBn1 = 1;
uint8_t opcBn2 = 1;
// Flag use for toogle Led
uint8_t bBlinkLed;
// Use for save only one time
uint8_t bArchivo = 1;
// Use for new process
uint8_t sockId = 0;
// Usado para identificar el dispositivo
uint8_t idDispositivo = 0;
// Usado para mostrar el mesaje cuando  se envia el pulso de inicio de medicion
uint8_t idMesure = 0;
// Address transmitation NRF24L01+
uint8_t tx_addr[5] = {0};
// Addres Receive NRF24L01+
uint8_t rx_addr[5] = {0};
// Data sent 
uint8_t txEnv[SIZEDATA];
// Data receive 
uint8_t rxRec[SIZEDATA] = {0};
// Puerto serial of get data gps
int serialPort = 0;
//Variable store data Gps
dataGps data;
// Prompter for crear file.scv
FILE *archivo;
// Variable temporal
char tmp[1024];
// Use for identificar socket
int sockIdN1 = 0;
// Work with time.h
struct tm timeSet;
time_t timeSec;
time_t timeGet;
struct tm *pTimeGet;
int timeClock[2] = {0};
// Usado para graficar los datos obtenidos del acelerometro
int iteratorGraph = 0;
// Mesure time
GTimer *timer;
GTimer *timer1;
double start_time;
double end_time;
gulong start_us = 0;
gulong end_us = 0;
gulong start_usTR = 0;
gulong end_usTR = 0;
uint16_t time_us = 0;
uint16_t time_usTR = 0;

GdkRGBA color;

// Save value for record
uint8_t timerHoras = 0;
uint8_t timerMinutos = 0;
uint8_t timerSegundos = 0;
int sumCurrent = 0;
uint8_t countCurrent = 0;
uint8_t verificaSync = 0;
// Usado para verificar que todo los nodos inicien la medicion
uint8_t verificaInicioCorrecto = 0;


/**
 * @brief Variable for GUI
 * 
 */
GtkWidget 		*lbTime ;
GtkWidget 		*lbCurrentN1;
GtkWidget 		*lbCurrentN2;
GtkWidget 		*lbDate ;
GtkWidget 		*lbLatitud ;
GtkWidget 		*lbLongitud ;
GtkWidget 		*lbNTM;
GtkWidget 		*TextView;
GtkWidget 		*tvN1;
GtkWidget 		*tvN2;
GtkWidget 		*tvN3;
GtkWidget 		*tvN4;
GtkWidget 		*tvN5;
GtkWidget 		*tvN6;
GtkWidget 		*tvN7;
GtkWidget 		*tvN8;
GtkWidget 		*tvN9;
GtkWidget 		*tvN10;
GtkWidget 		*ScrollWindow;
GtkWidget 		*swN1;
GtkWidget 		*swN2;
GtkTextBuffer	*TextBuffer;
GtkTextBuffer	*tbN1;
GtkTextBuffer	*tbN2;
GtkTextBuffer	*tbN3;
GtkTextBuffer	*tbN4;
GtkTextBuffer	*tbN5;
GtkTextBuffer	*tbN6;
GtkTextBuffer	*tbN7;
GtkTextBuffer	*tbN8;
GtkTextBuffer	*tbN9;
GtkTextBuffer	*tbN10;
GtkWidget	 	*fSinc;
GtkTextIter  	iter ;
GtkTextIter  	iN1 ;
GtkTextIter  	iN2 ;
GtkTextIter  	iN3 ;
GtkTextIter  	iN4 ;
GtkTextIter  	iN5 ;
GtkTextIter  	iN6 ;
GtkTextIter  	iN7 ;
GtkTextIter  	iN8 ;
GtkTextIter  	iN9 ;
GtkTextIter  	iN10 ;
GtkWidget	 	*sock;
GtkWidget		*fNodo1;
GtkWidget		*button;
GtkWidget		*bSyncN1;
GtkWidget		*bSyncN2;
GtkWidget		*bSyncVideo;
GtkWidget		*sbHoras;
GtkWidget		*sbMinutos;
GtkWidget		*sbSegundos;
GtkWidget		*bxNodo1;
GtkWidget		*bxNodo2;
GtkWidget		*bxNodo3;
GtkWidget		*bxNodo4;
GtkWidget		*bxNodo5;
GtkWidget		*bxNodo6;
GtkWidget		*bxNodo7;
GtkWidget		*bxNodo8;
GtkWidget		*bxNodo9;
GtkWidget		*bxNodo10;

/**
 * @brief Function Prototype
 * 
 */
void on_window_destroy();
void on_bSyncVideo_clicked();
void on_bSyncN1_clicked();
void on_bSyncN2_clicked();
void on_bSyncN3_clicked();
void on_bSyncN4_clicked();
void on_bSyncN5_clicked();
void on_bSyncN6_clicked();
void on_bSyncN7_clicked();
void on_bSyncN8_clicked();
void on_bSyncN9_clicked();
void on_bSyncN10_clicked();
void bipMuestreo_clicked();
void blinkLed();
void interrupcionNRF();
gboolean showDataGps();
void setAddressTx(uint8_t value);
void setAddressTx(uint8_t value);
void setAddresNrf(uint8_t idNodo);
void myCSS(void);
void setClock(clockid_t clock, time_t tSec, long tnSec);
void getTimeClock(int in[2]);
void taskMaster(uint8_t opt);
void showMessageMxRt(uint8_t id);
void showMessageSnDt(uint8_t id);
void showMessageRcDt(uint8_t id);
void showMessageSync(uint8_t id);
void showMessagePruebas(uint8_t op);
uint8_t existFile(void);
void showCurrent(uint8_t op, float intencidad);
void generarGrafica(uint8_t idN);
void plotData(uint8_t id);
void sendPulseMesure(uint8_t device);
#endif
/**
 * @brief End file main.h
 * 
 */

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
// Usado para el boton multiestado 1: Sincronizar 2: Iniciar Prueba otro caso para muestra
uint8_t opcbNodos = 1;

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
GtkWidget 		*lbDate ;
GtkWidget 		*lbLatitud ;
GtkWidget 		*lbLongitud ;
GtkWidget 		*lbNTM;
GtkWidget 		*TextView;
GtkWidget 		*tvN1;
GtkWidget 		*ScrollWindow;
GtkWidget 		*swN1;
GtkTextBuffer	*TextBuffer;
GtkTextBuffer	*tbN1;
GtkWidget	 	*fSinc;
GtkTextIter  	iter ;
GtkTextIter  	iN1 ;
GtkWidget	 	*sockN1;
GtkWidget		*fNodo1;
GtkWidget		*button;
GtkWidget		*bSyncN1;
GtkWidget		*bSyncVideo;
GtkWidget		*sbHoras;
GtkWidget		*sbMinutos;
GtkWidget		*sbSegundos;
GtkWidget		*bxNodo1;


/**
 * @brief Function Prototype
 * 
 */
void on_window_destroy();
void on_bSyncVideo_clicked();
void on_bSyncN1_clicked();
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
void plotData(uint8_t id);
//void generarGraph(void);
uint8_t existFile(void);
void showCurrent(uint8_t op, float intencidad);
void generarGrafica(uint8_t idDptv);
#endif
/**
 * @brief End file main.h
 * 
 */
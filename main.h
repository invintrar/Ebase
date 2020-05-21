/*
*
* @author: DzhL
*
*/
#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <signal.h>
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

#define LED 		7

#define Led_SetOutput()		pinMode(LED, OUTPUT)
#define LedOn()        		digitalWrite(LED, HIGH)
#define LedOff()		 	digitalWrite(LED, LOW)

// Flag for control NRF24L01+
uint8_t bNrf = 0;
// Flag use for toogle Led
uint8_t bBlinkLed;
// Use for save data sensor
uint16_t sensor;
// Use for save only one time
uint8_t bArchivo = 1;
// Use for new process
uint8_t sockId = 0;

// Address transmitation NRF24L01+
uint8_t tx_addr[5];
// Addres Receive NRF24L01+
uint8_t rx_addr[5];
// Data sent 
uint8_t txEnv[8];
// Data receive 
uint8_t rxRec[8];

//Value of aceleromter
uint32_t valueX;
uint32_t valueY;
uint32_t valueZ;

// 
int serialPort;
//Variable store data Gps
dataGps data;

// Prompter for crear file.txt 
FILE *archivo;

// Variable temporal
char tmp[1024];
// Use for identificar socket
unsigned int sockIdN1 = 0;

//Mesure time
GTimer *timer;
double start_time;
double end_time;
gulong start_us;
gulong end_us;
uint16_t timeGps_us = 0;
GdkRGBA color;

// Flag Synchronization
uint8_t fSyc;

// Save value for record
uint8_t horasSyc = 0;
uint8_t minutosSyc = 0;

// Variable for GUI
GtkWidget 		*lbTime ;
GtkWidget 		*lbDate ;
GtkWidget 		*lbLatitud ;
GtkWidget 		*lbLongitud ;
GtkWidget 		*TextView;
GtkWidget 		*tvN1;
GtkWidget 		*ScrollWindow;
GtkWidget 		*swN1;
GtkTextBuffer	*TextBuffer;
GtkTextBuffer	*tbN1;
GtkWidget	 	*fSinc;
GtkTextIter  	iter;
GtkTextIter  	iN1;
GtkWidget	 	*sockN1;
GtkWidget		*fNodo1;
GtkWidget		*button;
GtkWidget		*bSyncN1;
GtkWidget		*sbHoras;
GtkWidget		*sbMinutos;
GtkWidget		*bxNodo1;

/**
 * Fuction Prototype
 */
void on_window_destroy();
void on_bSyncVideo_clicked();
void on_bSyncN1_clicked();
void bipMuestreo_clicked();
void blinkLed();
float fnabs(float a);
void interrupcion();
gboolean showDataGps();
void setAddressTx(uint8_t value);
void setAddressTx(uint8_t value);
void setAddresNrf(uint8_t idNodo);
void myCSS(void);

#endif
/**
 * End File
 **/
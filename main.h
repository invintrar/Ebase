/*
*
* Author: DzhL
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

//Flag for control Nrf24L0+
uint8_t bNrf = 0;
//Flag use for toogle Led
uint8_t bBlinkLed;
uint16_t sensor;
//Use for save only one time
uint8_t bArchivo = 1;
uint8_t sockId = 0;

//Address Transmitation Nrf24L01+
uint8_t tx_addr[5];
//Addres Receive Nrf24L01+
uint8_t rx_addr[5];
//Data sent 
uint8_t txEnv[8];
uint8_t rxRec[8];

//Value of aceleromter
uint32_t valueX;
uint32_t valueY;
uint32_t valueZ;

int serialPort;
//Variable store data Gps
dataGps data;

FILE *archivo;

char tmp[1024];

//Mesure time
GTimer *timer;
double start_time;
double end_time;
gulong start_us;
gulong end_us;
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
GtkWidget 		*ScrollWindow;
GtkTextBuffer	*TextBuffer;
GtkWidget	 	*fSinc;
GtkTextIter  	iter;
GtkWidget	 	*sock;
GtkWidget		*fNodo1;
GtkWidget		*button;
GtkWidget		*sbHoras;
GtkWidget		*sbMinutos;

/**
 * Fuction Prototype
 */
void on_bipEv_clicked();
void on_bfpEv_clicked();
void on_window_destroy();
void blinkLed();
void interrupcion();
gboolean showDataGps();
float fnabs(float a);
void setAddresNrf(uint8_t idNodo);
void bipMuestreo_clicked();
void myCSS(void);
gint getValueSpMinutos();
gint getValueSpHoras();

#endif
/**
 * End File
 **/

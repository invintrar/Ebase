#include "main.h"
#define ChanelNrf 22;

//Bandera para controlar Nrf24L0+
uint8_t bNrf;
uint16_t sensor;

//Address Transmisor Nrf24L01+
uint8_t tx_addr[5];
//Addres Reseive Nrf24L01+
uint8_t rx_addr[5];
//Data sent 
uint8_t txEnv[8];
uint8_t rxRec[8];


uint32_t valueX;
uint32_t valueY;
uint32_t valueZ;


int serialPort;
//Variable store data Gps
dataGps data;

uint8_t run = 1;
pthread_t hilo1;

GtkWidget *lbTime ;
GtkWidget *lbDate ;
GtkWidget *lbLatitud ;
GtkWidget *lbLongitud ;
//GtkWidget *framGps;

/*-------Fuction Prototype-----*/
void interrupcion();
void sincronizar();
gboolean getGps();
void stop();
void offLed();
float fnabs(float a);
void setAddresNrf(uint8_t idNodo);

/*-------Function Main--------*/
int main(int argc, char *argv[])
{
	bNrf=0;

    GtkBuilder      *builder; 
    GtkWidget       *window;

	//Setting Poer CE and SPI
	RF24L01_init();

	//Settign address nrf and channel
	
    wiringPiSetup();
  	
	if(initSerial())
  	{
  		printf("Error Setup Serial\n");
  	}


    pinMode(LED,OUTPUT);

	
    gtk_init(&argc, &argv);

    builder = gtk_builder_new();

    gtk_builder_add_from_file (builder, "gui.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "windowMain"));
    gtk_builder_connect_signals(builder, NULL);
	lbTime = GTK_WIDGET(gtk_builder_get_object(builder, "lbTime"));
	lbDate = GTK_WIDGET(gtk_builder_get_object(builder, "lbDate"));
	lbLatitud = GTK_WIDGET(gtk_builder_get_object(builder, "lbLatitud"));
	lbLongitud = GTK_WIDGET(gtk_builder_get_object(builder, "lbLongitud"));
	//framGps = GTK_WIDGET(gtk_builder_get_object(builder, "framGps"));

    g_object_unref(builder);

	g_timeout_add_seconds(1,(GSourceFunc) getGps,NULL);

    gtk_widget_show(window);                

    gtk_main();

    return 0;
}
//End main


// called when window is closed
void on_window_destroy()
{
    gtk_main_quit();
	offLed();
	run = 0;
}

void onLed()
{
	digitalWrite(LED,HIGH);
}

void offLed()
{
	digitalWrite(LED,LOW);
}

float fnabls(float a){
	if(a<0)
		a=-a;
	return a;
}
void sincronizar(){
	getGps();
}

void interrupcion(){
	//Return 1:Data Sent, 2:RX_DR, 3:Max_RT
	bNrf = RF24L01_status();
	RF24L01_clear_interrupts();
}

gboolean  getGps(){
	char buffer[10];
	
	if(run == 1){
		onLed();
		delay(250);
		run=0;
	}
	else{
		offLed();
		delay(250);
		run=1;
	}

	data = getDataGps();

 	sprintf(buffer, "%d:%d:%d", data.hour, data.minute, data.second);
	gtk_label_set_text(GTK_LABEL(lbTime), buffer);

	sprintf(buffer, "%d/%d/%d", data.month, data.day, data.year);
	gtk_label_set_text(GTK_LABEL(lbDate), buffer);
	
	sprintf(buffer, "%d%s%d%c%d%c %c", data.gradosLatitud, "°", data.minutosLatitud, 39, 
 	data.segundosLatitud, 34, data.latitud);
	gtk_label_set_text(GTK_LABEL(lbLatitud), buffer);

 	sprintf(buffer, "%d%s%d%c%d%c %c", data.gradosLongitud, "°", data.minutosLongitud, 39, 
	data.segundosLongitud, 34, data.longitud);
	gtk_label_set_text(GTK_LABEL(lbLongitud), buffer);

	return TRUE;
}

void stop(){
	run=0;
}

void setAddresNrf(uint8_t idNodo){
	switch(idNodo){
		case 1:
			//Addres Receive
        	rx_addr[0] = 0x78;
        	rx_addr[1] = 0x78;
        	rx_addr[2] = 0x78;
        	rx_addr[3] = 0x78;
        	rx_addr[4] = 0x78;
        	//Addres Transive
        	tx_addr[0] = 0x78;
        	tx_addr[1] = 0x78;
        	tx_addr[2] = 0x78;
        	tx_addr[3] = 0x78;
        	tx_addr[4] = 0x78;
			break;
		default:
			//Addres Receive
        	rx_addr[0] = 0x78;
        	rx_addr[1] = 0x78;
        	rx_addr[2] = 0x78;
        	rx_addr[3] = 0x78;
        	rx_addr[4] = 0x78;
        	//Addres Transive
        	tx_addr[0] = 0x78;
        	tx_addr[1] = 0x78;
        	tx_addr[2] = 0x78;
        	tx_addr[3] = 0x78;
        	tx_addr[4] = 0x78;
        	break;
	}
}

//Fin File

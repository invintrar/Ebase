/**
 * @author:DzhL
 */

#include "main.h"

/**
 * Function Main
 */
int main(int argc, char *argv[])
{
	bNrf=0;
	bBlinkLed = 1;

    GtkBuilder      *builder; 
    GtkWidget       *window;

    wiringPiSetup();

	//Setting Poer CE and SPI
	RF24L01_init();
  	

	if(initSerial())
  	{
  		printf("Error Setup Serial\n");
  	}

	
	//Set pin output
    pinMode(LED,OUTPUT);

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();

    gtk_builder_add_from_file (builder, "guiEb.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    gtk_builder_connect_signals(builder, NULL);

	lbTime = GTK_WIDGET(gtk_builder_get_object(builder, "lbTime"));
	lbDate = GTK_WIDGET(gtk_builder_get_object(builder, "lbDate"));
	lbLatitud = GTK_WIDGET(gtk_builder_get_object(builder, "lbLatitud"));
	lbLongitud = GTK_WIDGET(gtk_builder_get_object(builder, "lbLongitud"));
	ScrollWindow = GTK_WIDGET(gtk_builder_get_object(builder, "ScrollWindow"));
	TextView = GTK_WIDGET(gtk_builder_get_object(builder, "TextView"));
	fSinc = GTK_WIDGET(gtk_builder_get_object(builder, "fSinc"));


	TextBuffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(TextView));

    g_object_unref(builder);

	gtk_widget_hide(fSinc);

	g_timeout_add_seconds(1,(GSourceFunc) showDataGps,NULL);

    gtk_widget_show(window);                

    gtk_main();

    return EXIT_SUCCESS;
}//End main


// Called when window is closed
void on_window_destroy()
{
    gtk_main_quit();
	LedOff();
}

// Button for Init mesure of station video
void on_bipEv_clicked(){
	// Set Addres for Transmitir
	setAddresNrf(0);
	//Settign address nrf and channel
	RF24L01_setup(tx_addr, rx_addr, CHANNEL); 

	txEnv[0] = data.second;
	txEnv[1] = data.minute;
	txEnv[2] = data.hour;
	txEnv[3] = data.day;
	txEnv[4] = data.month;
	txEnv[5] = data.year;

	RF24L01_sendData(txEnv,8);

	gtk_widget_show(fSinc);
	
    strcpy(tmp,"Estableciendo conexion con la Estacion Video\n");
	gtk_text_buffer_set_text(TextBuffer, (const gchar *) tmp, (gint) -1);
			

}

// Button for end mesure of station video
void on_bfpEv_clicked(){
	RF24L01_powerDown();
    strcpy(tmp,"Conexion cerrada con la Estacion Video\n");
	gtk_text_buffer_set_text(TextBuffer, (const gchar *) tmp, (gint) -1);


}

void blinkLed()
{
	if(bBlinkLed){
		bBlinkLed = 0;
		LedOn();
	}else{
		bBlinkLed = 1;
		LedOff();
	}
}

float fnabls(float a){
	if(a<0)
		a=-a;
	return a;
}

void interrupcion(){
	printf("Interrupcion\n");
	//Return 1:Data Sent, 2:RX_DR, 3:Max_RT
	bNrf = RF24L01_status();
	switch(bNrf){
		case 1:
			strcpy(tmp,"Data Sent\n");
			gtk_text_buffer_set_text(TextBuffer, (const gchar *) tmp, (gint) -1);
			break;
		case 2:
			strcpy(tmp,"Data Rady from RX\n");
			gtk_text_buffer_set_text(TextBuffer, (const gchar *) tmp, (gint) -1);
			break;
		case 3:
			strcpy(tmp,"Maximu Retramition Transmitio\n");
			gtk_text_buffer_set_text(TextBuffer, (const gchar *) tmp, (gint) -1);
			break;
		default:
			strcpy(tmp,"Se produjo Interrupcion\n");
			gtk_text_buffer_set_text(TextBuffer, (const gchar *) tmp, (gint) -1);
			break;
	}

	RF24L01_clear_interrupts();
}

gboolean showDataGps(){
	char buffer[10];
	
	blinkLed();

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

	return 1;
}

void setAddresNrf(uint8_t idNodo){
	switch(idNodo){
		case 0://Station video
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

		case 1://Nodo1
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

/**
 * Fin File
 */

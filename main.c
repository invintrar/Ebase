/**
 * @author:DzhL
 */

#include "main.h"

GtkBuilder      *builder; 
GtkWidget       *window;


/**
 * Function Main
 */
int main(int argc, char *argv[])
{
	bNrf=0;
	bBlinkLed = 1;

    wiringPiSetup();

	//Setting Poer CE and SPI
	RF24L01_init();

	//Seting Interrupt
	wiringPiISR(RF_IRQ, INT_EDGE_FALLING, interrupcion);

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
    fNodo1 = GTK_WIDGET(gtk_builder_get_object(builder, "fNodo1"));


	TextBuffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(TextView));

    g_object_unref(builder);

	gtk_widget_hide(fSinc);
	
	gtk_text_buffer_get_iter_at_offset(TextBuffer, &iter, 0);

	g_timeout_add_seconds(1,(GSourceFunc) showDataGps,NULL);

    gtk_widget_show(window);                

    gtk_main();

    return EXIT_SUCCESS;
}//End main


// Called when window is closed
void on_window_destroy()
{
	RF24L01_powerDown();
    gtk_main_quit();
	LedOff();
}

// Button for Init mesure of station video
void on_bipEv_clicked()
{
	// Set Addres for Transmitir
	setAddresNrf(0);
	//Settign address nrf and channel
	RF24L01_setup(tx_addr, rx_addr, CHANNEL); 

    sprintf(tmp,"Estableciendo conexion con la Estacion Video\n");
	gtk_text_buffer_insert(TextBuffer, &iter, tmp, -1);

	gtk_widget_show(fSinc);

	txEnv[0] = data.hour;
	txEnv[1] = data.minute;
	txEnv[2] = data.second;
	txEnv[3] = data.day;
	txEnv[4] = data.month;
	txEnv[5] = data.year;

	RF24L01_sendData(txEnv,8);


}

// Button for end mesure of station video
void on_bfpEv_clicked()
{
	RF24L01_powerDown();
    strcpy(tmp,"Conexion cerrada con la Estacion Video\n");
   	gtk_text_buffer_insert(TextBuffer, &iter, tmp, -1);
}

void on_bipNodo1_clicked()
{
	archivo = fopen("conf.gp","w");
	if(archivo == NULL)
	{
		printf("Error al crear el archivo\n");
	}
	
	sock = gtk_socket_new();
	gtk_widget_show(sock);
    gtk_container_add(GTK_CONTAINER(fNodo1), sock);
	sockId = gtk_socket_get_id(GTK_SOCKET(sock));
	fprintf(archivo, "set term x11 window \"%x\" \n", sockId);
	fclose(archivo);
	//sprintf(tmp, "gnuplot animacion.gp %#x &", sockId);
	//Run Gnuplot Animation
   //	system(tmp);
} 

void on_bfpNodo1_clicked()
{

}

/* Function blink led */
void blinkLed()
{
	if(bBlinkLed){
		bBlinkLed = 0;
		LedOn();
	}else{
		bBlinkLed = 1;
		LedOff();
	}
} // end bllink led

/* Function get abs */
float fnabls(float a)
{
	if(a<0)
		a=-a;
	return a;
} // end get abs

/* Function Interrupcion */
void interrupcion()
{
	//Return 1:RX_DR , 2:Data sent, 3:Max_RT
	bNrf = RF24L01_status();

	switch(bNrf)
	{
		case 1:
			sprintf(tmp,"Data Rady from RX\n");
    		gtk_text_buffer_insert(TextBuffer, &iter, tmp, -1);

			RF24L01_read_payload(rxRec, sizeof(rxRec));

			sprintf(tmp, "Hora Estacion video:\n %d:%d:%d\n",rxRec[3],rxRec[2],rxRec[1]);
			gtk_text_buffer_insert(TextBuffer, &iter, tmp, -1);
			
			RF24L01_set_mode_RX();
			bNrf = 0;
			break;
	
		case 2:
			sprintf(tmp,"Dato Enviado\n");
         	gtk_text_buffer_insert(TextBuffer, &iter, tmp, -1);

			RF24L01_set_mode_RX();

	       	gtk_text_buffer_insert(TextBuffer, &iter, "Esperando Dato..\n", -1);

			break;
		case 3:
			sprintf(tmp, "Maximo numero de retransmisiones\n");
		   	gtk_text_buffer_insert(TextBuffer, &iter, tmp,-1);
			break;
		default:
			break;
	}

	RF24L01_clear_interrupts();

} // end interrupt

gboolean showDataGps()
{
	char buffer[10];
	
	blinkLed();

	data = getDataGps();

	if(bArchivo == 1 && data.month != 0 && data.day != 0 && data.year != 0)
	{
		archivo = fopen("DatosGps.txt","at");
		if(archivo == NULL)
		{
			printf("Error al crear el archivo\n");
		}
		else
		{
			fprintf(archivo, "Datos Gps\n");
			fprintf(archivo, "Hora: %d:%d:%d\n", data.hour, data.minute, data.second);
			fprintf(archivo, "Fecha: %d/%d/%d\n", data.month, data.day, data.year);
			fprintf(archivo, "Latitud: %d%s%d%c%d%c %c\n", data.gradosLatitud, "°", data.minutosLatitud, 39,
					data.segundosLatitud, 34, data.latitud);
			fprintf(archivo, "Longitud: %d%s%d%c%d%c %c\n\n", data.gradosLongitud, "°", data.minutosLongitud, 39,
					data.segundosLongitud, 34, data.longitud);
			fclose(archivo);
			bArchivo = 0;
		}

	} //End if

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
} // End showDataGps

void setAddresNrf(uint8_t idNodo)
{
	switch(idNodo)
	{
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
	} // End swintch
} // End setAddresNrf

/**
 * Fin File
 */

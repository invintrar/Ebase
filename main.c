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
	start_time = 0.0;
	end_time = 0.0;
	start_us = 0;
	end_us = 0;
	fSinc = 0;
	bNrf = 0;
	bBlinkLed = 1;

	gtk_init(&argc, &argv);
	// My styles for button
	myCSS();

    wiringPiSetup();

	// Setting port CE and SPI
	RF24L01_init();
	//Seting Interrupt
	wiringPiISR(RF_IRQ, INT_EDGE_FALLING, interrupcion);
	// Initial serial for comunication with Gps
	if(initSerial())
	{
		printf("Error Setup Serial\n");
	}
	// Initialize the timer
	timer = g_timer_new();
	timer1 = g_timer_new();
	
	//Set port of the lmaed how output
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
	swN1 = GTK_WIDGET(gtk_builder_get_object(builder, "swN1"));
	tvN1 = GTK_WIDGET(gtk_builder_get_object(builder, "tvN1"));
	fSinc = GTK_WIDGET(gtk_builder_get_object(builder, "fSinc"));
    bxNodo1 = GTK_WIDGET(gtk_builder_get_object(builder, "bxNodo1"));
    button = GTK_WIDGET(gtk_builder_get_object(builder, "bipMuestreo"));
	bSyncN1 = GTK_WIDGET(gtk_builder_get_object(builder, "bSyncN1"));
    sbHoras = GTK_WIDGET(gtk_builder_get_object(builder, "sbHoras"));
    sbMinutos = GTK_WIDGET(gtk_builder_get_object(builder, "sbMinutos"));



	gtk_widget_set_name(button, "myButton_green");
	gtk_widget_set_name(bSyncN1, "myButton_blue");
	

	TextBuffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(TextView));
	tbN1 = gtk_text_view_get_buffer (GTK_TEXT_VIEW(tvN1));

    g_object_unref(builder);

	gtk_widget_hide(fSinc);
	
	gtk_text_buffer_get_iter_at_offset(TextBuffer, &iter, 0);
	gtk_text_buffer_get_iter_at_offset(tbN1, &iN1, 0);

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
void on_bSyncVideo_clicked()
{
	// Set Addres for Transmitir
	setAddresNrf(0);
	//Settign address nrf and channel
	RF24L01_setup(tx_addr, rx_addr, CHANNEL); 
    sprintf(tmp,"Estableciendo conexion con el nodo\n");
	gtk_text_buffer_insert(TextBuffer, &iter, tmp, -1);
	gtk_widget_show(fSinc);
	fSyc = 1;

} // End on_bSyncVideo


// Action when clicked button sycn Nodo1
void on_bSyncN1_clicked()
{
	// Set Addres for Transmitir
	setAddresNrf(1);
	//Settign address nrf and channel
	RF24L01_setup(tx_addr, rx_addr, CHANNEL); 
	fSyc = 1;
	static gboolean runN1 = FALSE;

	if(!runN1)
	{
		// Cuand pulso Sincronizar
		gtk_widget_set_name(bSyncN1, "myButton_green");
		gtk_button_set_label((GtkButton *)bSyncN1, "Prueba");
		sprintf(tmp,"Pulsado Sincronizar\n");
		gtk_text_buffer_insert(tbN1, &iN1, tmp, -1);

	}
	else
	{
		// Cuando pulso Prueba
		gtk_widget_set_name(bSyncN1, "myButton_blue");
		gtk_button_set_label((GtkButton *)bSyncN1, "Sincronizar");
		sprintf(tmp,"Pulsado Prueba\n");
		gtk_text_buffer_insert(tbN1, &iN1, tmp, -1);

		sockN1 = gtk_socket_new ();
		gtk_widget_set_size_request(sockN1, 400, 400);
		gtk_container_add (GTK_CONTAINER (bxNodo1), sockN1);
		sockIdN1 = gtk_socket_get_id(GTK_SOCKET(sockN1));

		sprintf(tmp, "Socket created=%#x\n", sockIdN1);
		gtk_text_buffer_insert(tbN1, &iN1, tmp, -1);

		gtk_widget_show_all(window);
		
		sprintf(tmp, "gnuplot -c animacion.gp \"%x\" &\n", sockIdN1);
		gtk_text_buffer_insert(tbN1, &iN1, tmp, -1);

		system(tmp);
	}

	runN1 = !runN1;

} // End on_bSyncN1_clicked


// Action when clicked button start measuring
void bipMuestreo_clicked()
{
	static gboolean running = FALSE;
	
	horasSyc = gtk_spin_button_get_value_as_int((GtkSpinButton *)sbHoras);
    minutosSyc = gtk_spin_button_get_value_as_int((GtkSpinButton *)sbMinutos);

	sprintf(tmp, "Valor para sincronizar: %02d:%02d\n", horasSyc, minutosSyc);
	gtk_text_buffer_insert(TextBuffer, &iter, tmp, -1);

	if(!running)
	{
		gtk_widget_set_name(button, "myButton_red");
		gtk_button_set_label((GtkButton *)button, "Parar   Muestreo");
	}
	else
	{
		gtk_widget_set_name(button, "myButton_green");
		gtk_button_set_label((GtkButton *)button, "Iniciar Muestreo");
	}

	running = !running;
} // En bipMuestreo_clicked


/* Function blink Led */
void blinkLed()
{
	if(bBlinkLed){
		bBlinkLed = 0;
		LedOn();
	}else{
		bBlinkLed = 1;
		LedOff();
	}
} // end bllinkLed


/* Function convert to value absolute */
float fnabs(float a)
{
	if(a<0)
		a=-a;
	return a;
} // End fnabs


/* Function Interrupcion for NRF24L01+ */
void interrupcion()
{
	//Return 1:RX_DR , 2:Data send, 3:Max_RT
	bNrf = RF24L01_status();

	switch(bNrf)
	{
		case 1: // Data recive
			// show data received in text view
			sprintf(tmp,"Data Rady from RX\n");
			gtk_text_buffer_insert(TextBuffer, &iter, tmp, -1);
			// Read data of the module
			RF24L01_read_payload(rxRec, sizeof(rxRec));
			// show data in text viewpi
			sprintf(tmp, "Hora Estacion video:\n %d:%d:%d\n",rxRec[3],rxRec[2],rxRec[1]);
			gtk_text_buffer_insert(TextBuffer, &iter, tmp, -1);
			// Set in mode reception module NRF24L01+
			RF24L01_set_mode_RX();
			bNrf = 0;
			break;
		case 2: // Data send
			// stop timer
			g_timer_elapsed(timer1, &end_usTR);
			// calcule diferencia de time
			time_usTR = (end_usTR - start_usTR);
			//show data in text view
			sprintf(tmp, "Dato Enviado con un timpo: %d us\n", time_usTR);
			gtk_text_buffer_insert(TextBuffer, &iter, tmp, -1);
			// Set mode reception module NRF24L01+
			RF24L01_set_mode_RX();
			gtk_text_buffer_insert(TextBuffer, &iter, "Esperando Dato..\n", -1);
			break;
		case 3:
			sprintf(tmp, "Maximo numero de retransmisiones\n");
			gtk_text_buffer_insert(TextBuffer, &iter, tmp, -1);
			break;
		default:
			break;
	} // end switch
	// Clear register for quit interrupt
	RF24L01_clear_interrupts();
} // End interrupcion


// Function show time each second
gboolean showDataGps()
{
	if(fSyc)
	{
		txEnv[0] = 1;
		txEnv[1] = data.second;
		txEnv[2] = data.minute;
		txEnv[3] = data.hour;
		txEnv[4] = data.day;
		txEnv[5] = data.month;
		txEnv[6] = data.year; 
		txEnv[7] = time_us;
		txEnv[8] = (time_us >> 8);
		// Send data for synchronization
		g_timer_reset(timer1);
		g_timer_elapsed(timer1,&start_usTR);
		RF24L01_sendData(txEnv,12);
		// show data in text view
		sprintf(tmp, "Hora Gps: %02d:%02d:%02d:%02d\n", data.hour, data.minute, data.second, time_us);
		gtk_text_buffer_insert(TextBuffer, &iter, tmp, -1);
		
		fSyc = 0;
	} // end if 
	// Use for save date longitud y latitud when start aplication in file.txt
	if(bArchivo == 1 && data.month != 0 && data.day != 0 && data.year != 0)
	{
		printf("here\n");
		g_timer_reset(timer);
		g_timer_elapsed(timer,&start_us);
		// Get data of module Gps
		data = getDataGps();
		// Set clock of raspberry Pi with data the of Gps
		timeSet.tm_year = (2000 + data.year) - 1900;
		timeSet.tm_mon =  data.month;
		timeSet.tm_mday = data.day;
		timeSet.tm_hour = data.hour;
		timeSet.tm_min = data.minute;
		timeSet.tm_sec = data.second;
		timeSet.tm_isdst = 0;
		timeSec = mktime(&timeSet);
		if (timeSec == -1)
		{
			perror("unknown");
		}
		else
		{
			g_timer_elapsed(timer, &end_us);
			time_us = (end_us - start_us);
			setClock( CLOCK_REALTIME, timeSec, (time_us)*1000);
		}
		// Use for save dates in File DatosGps
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
	} //End save for first sometime in file.txt

	// Blink Led
	blinkLed();

	timeGet = time(NULL);
	pTimeGet = localtime(&timeGet);

	//Show data in graphical user interface
	sprintf( tmp, "%02d:%02d:%02d", pTimeGet->tm_hour, pTimeGet->tm_min, pTimeGet->tm_sec);
	gtk_label_set_text(GTK_LABEL(lbTime), tmp);
	sprintf( tmp, "%02d/%02d/%02d", data.month, data.day, data.year);
	gtk_label_set_text(GTK_LABEL(lbDate), tmp);
	sprintf( tmp, "%02d%s%02d%c%02d%c %c", data.gradosLatitud, "°", data.minutosLatitud, 39,
		data.segundosLatitud, 34, data.latitud);
	gtk_label_set_text(GTK_LABEL(lbLatitud), tmp);
	sprintf(tmp, "%02d%s%02d%c%02d%c %c", data.gradosLongitud, "°", data.minutosLongitud, 39, 
		data.segundosLongitud, 34, data.longitud);
	gtk_label_set_text(GTK_LABEL(lbLongitud), tmp);
	return 1;
} // End showDataGps


// Set Address of module NRF for Transmition
void setAddressTx(uint8_t value)
{
	uint8_t i;

	for(i=0;i<5;i++)
	{
		tx_addr[i] = value;
	}

} // End setAddressTx


// Set Address of module NRF for Recive
void setAddressRx(uint8_t value)
{
	uint8_t i ;

	for(i=0;i<5;i++)
	{
		rx_addr[i] = value;
	}

} // End setAddressRx


// Use for select address of the stattion video or  node
void setAddresNrf(uint8_t idNodo)
{
	switch(idNodo)
	{
		case 0://Station video
			//Addres Receive
			setAddressRx(0x78);
        	//Addres Transive
			setAddressTx(0x78);
			break;
		case 1://Nodo1
			//Addres Receive
			setAddressRx(0xA1);
		   	//Addres Transive
			setAddressTx(0x78);
			break;
		default:
			//Addres Receive
			setAddressRx(0x78);
        	//Addres Transive
			setAddressTx(0x78);
			break;
	} // End swintch
} // End setAddresNrf

// Use for color button
void myCSS(void)
{
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

    provider = gtk_css_provider_new ();
    display = gdk_display_get_default ();
    screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    const gchar *myCssFile = "mystyle.css";
    GError *error = 0;

    gtk_css_provider_load_from_file(provider, g_file_new_for_path(myCssFile), &error);
    g_object_unref (provider);
} // end my CSS

// Set clock of raspberry pi
void setClock(clockid_t clock, time_t tSec, long tnSec)
{
    struct timespec tp = {tSec, tnSec};
    if(clock_settime(clock, &tp) == -1 )
    {
        perror("clock_settime");
        exit(EXIT_FAILURE);
    }

}// set clock of raspberry pi

// get time of the raspberry opc:1 Seconds, microseconds
// other case date
void getTimeClock(void)
{
	int in[2];
	struct timeval tv = {0};
	gettimeofday(&tv, NULL);
	// Get Seconds and convert to uint8_t
	in[0] = (int) tv.tv_sec;
	txEnv[0] = 0;
	txEnv[1] = in[0];
	txEnv[2] = (in[0] >> 8);
	txEnv[3] = (in[0] >> 16);
	txEnv[4] = (in[0] >> 24);
	// Get microSeconds and convert to uint8_t
	in[1] = (int) tv.tv_usec;
	txEnv[5] = in[1];
	txEnv[6] = (in[1] >> 8);
	txEnv[7] = (in[1] >> 16);
	txEnv[8] = (in[1] >> 24);
	txEnv[9] = 0;
	txEnv[10] = 0;
	txEnv[11] = 0;
	txEnv[12] = 0;
	
} // end getTime


/**
 * Fin File
 */

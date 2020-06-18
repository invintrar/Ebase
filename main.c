/**
 * @file main.c
 * @author DzhL (invintrar@gmail.com)
 * @brief Program for the station base use for init network wirless of Structural Health Monitoring(SHM).
 * @version 1.2
 * @date 2020-06-02
 * 
 * 
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
	// Seting Interrupt module NRF24L01+
	wiringPiISR(RF_IRQ, INT_EDGE_FALLING, interrupcionNRF);
	// Initial port serial for comunication with Gps
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
	lbNTM = GTK_WIDGET(gtk_builder_get_object(builder, "lbNTM"));
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
	sbSegundos = GTK_WIDGET(gtk_builder_get_object(builder, "sbSegundos"));



	gtk_widget_set_name(button, "myButton_green");
	gtk_widget_set_name(bSyncN1, "myButton_blue");
	

	TextBuffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(TextView));
	tbN1 = gtk_text_view_get_buffer (GTK_TEXT_VIEW(tvN1));

    g_object_unref(builder);

	gtk_widget_hide(fSinc);
	
	gtk_text_buffer_get_iter_at_offset(TextBuffer, &iter, 0);
	gtk_text_buffer_get_iter_at_offset(tbN1, &iN1, 0);

	g_timeout_add_seconds(1,(GSourceFunc) showDataGps,NULL);

	gtk_widget_show(fSinc);

    gtk_widget_show(window);                

    gtk_main();

    return EXIT_SUCCESS;
}//End main


/**
 * @brief Called when window is closed
 * 
 * 
 */
void on_window_destroy()
{
	RF24L01_powerDown();
    gtk_main_quit();
	LedOff();
	// delete record video if exist 
	if(existFile())
    {
        sprintf(tmp, "rm logfile");
        system(tmp);
    }
}


/**
 * @brief Button for init mesure of station video
 * 
 */
void on_bSyncVideo_clicked()
{
	idMessage = 11;
	sprintf(tmp,"Inicio de Sincronizacion\n");
	gtk_text_buffer_insert(TextBuffer, &iter, tmp, -1);
	// Set Addres for Transmitir
	setAddresNrf(0);
	//Settign address nrf and channel
	RF24L01_setup(tx_addr, rx_addr, CHANNEL); 
	//RF24L01_set_mode_RX();
	//gtk_text_buffer_insert(TextBuffer, &iter, "Esperando Dato...\n", -1);
	//gtk_widget_show(fSinc);
	// Send data for synchronization
	//g_timer_reset(timer1);
	//g_timer_elapsed(timer1,&start_usTR);
	// get time of clock real of the raspberry pi
	getTimeClock(timeClock);
	// Option for synchronization 
	txEnv[0] = 1;
	// Option identify time 1 of del master that identify the slave
	txEnv[10]= 1;
	sendData(txEnv);

} // End on_bSyncVideo


/**
 * @brief Action when clicke button sycn nodo1
 * 
 */
void on_bSyncN1_clicked()
{
	idMessage = 1;
	// Set Addres for Transmitir
	setAddresNrf(1);
	//Settign address nrf and channel
	RF24L01_setup(tx_addr, rx_addr, CHANNEL); 

	switch(opcbNodos){
		case 1:
			// Cuand pulso Sincronizar
			//gtk_widget_set_name(bSyncN1, "myButton_green");
			//gtk_button_set_label((GtkButton *)bSyncN1, "Iniciar Prueba");
			sprintf(tmp,"Sincronizacion Iniciada...\n");
			gtk_text_buffer_insert(tbN1, &iN1, tmp, -1);
			getTimeClock(timeClock);
			txEnv[0] = 2;
			sendData(txEnv);
			break;
		case 2:
			// Cuando pulso Iniciar prueba
			gtk_widget_set_name(bSyncN1, "myButton_blue");
			gtk_button_set_label((GtkButton *)bSyncN1, "Para Prueba");
			sprintf(tmp,"Inicio de Prueba\n");
			gtk_text_buffer_insert(tbN1, &iN1, tmp, -1);
			txEnv[0] = 3;
			sendData(txEnv);		
			opcbNodos = 3;
			break;
		default:// Cuando se preciosa parar prueba
			gtk_widget_set_name(bSyncN1, "myButton_blue");
			gtk_button_set_label((GtkButton *)bSyncN1, "Iniar Prueba");
			stopMesure = 0;
			iteratorGraph = 0;
			txEnv[0] = 5;
			sendData(txEnv);
			opcbNodos = 2;
			archivo = fopen("logfile","at");
			if(archivo == NULL)
			{
				printf("Error al crear el archivo\n");
			}
			else
			{	
				fprintf(archivo,"%10d\t%10d\t%10d\t%10d\t%03.3f\t%10d\n",0, 0, 0, 0, 0.0, 1);
				fclose(archivo);
			}
			break;
	}
} // End on_bSyncN1_clicked


/**
 * @brief Action when clicked button start measuring
 * 
 */
void bipMuestreo_clicked()
{
	static gboolean running = true;
	idMessage = 12;
	
	horasSyc = gtk_spin_button_get_value_as_int((GtkSpinButton *)sbHoras);
    minutosSyc = gtk_spin_button_get_value_as_int((GtkSpinButton *)sbMinutos);
	segundosSyc = gtk_spin_button_get_value_as_int((GtkSpinButton *)sbSegundos);

	if(running)
	{
		if(minutosSyc > 0 || horasSyc > 0 || segundosSyc)
		{
			// Set Addres for Transmitir
			setAddresNrf(0);
			//Settign address nrf and channel
			RF24L01_setup(tx_addr, rx_addr, CHANNEL);
			// Opcion para Muestrear
			txEnv[0] = 2;
			txEnv[1] = segundosSyc;
			txEnv[2] = minutosSyc;
			txEnv[3] = horasSyc;
			sendData(txEnv);
			sprintf(tmp, "Valor para muestreo: %02d:%02d:%02d",
			horasSyc, minutosSyc, segundosSyc);
			gtk_label_set_text(GTK_LABEL(lbNTM), tmp);
			gtk_widget_set_name(button, "myButton_red");
			gtk_button_set_label((GtkButton *)button, "Parar   Muestreo");
			running = !running;
		}else
		{
			sprintf(tmp, "No ingreso valor para muestreo");
			gtk_label_set_text(GTK_LABEL(lbNTM), tmp);
		}
	}
	else
	{
		RF24L01_powerDown();
		//txEnv[0] = 3;
		//sendData(txEnv);
		sprintf(tmp, "Apagado modulo Nrf24L01+");
		gtk_label_set_text(GTK_LABEL(lbNTM), tmp);
		// Use for show start measure
		gtk_widget_set_name(button, "myButton_green");
		gtk_button_set_label((GtkButton *)button, "Iniciar Muestreo");
		running = !running;
	}
} // En bipMuestreo_clicked


/**
 * @brief Function blink led
 * 
 */
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


/**
 * @brief Function convert to value absolute
 * 
 * @param a 
 * @return float 
 */
float fnabs(float a)
{
	if(a<0)
		a=-a;
	return a;
} // End fnabs


/**
 * @brief Function interrupt for NRF24L01+ when 
 * send data or received data and maximum retransmition
 * 
 */
void interrupcionNRF()
{
	//Return 1:RX_DR , 2:Data send, 3:Max_RT
	bNrf = RF24L01_status();
	// switch
	switch(bNrf)
	{
		case 1: // Data recive
			//g_timer_reset(timer1);
			//g_timer_elapsed(timer1,&start_usTR);
			// show data received in text view
			//sprintf(tmp,"Dato  recibido...\n");
			//gtk_text_buffer_insert(TextBuffer, &iter, tmp, -1);
			// Read data of the module
			RF24L01_read_payload(rxRec, sizeof(rxRec));
			//showMessageRcDt(idMessage);
			//sprintf(tmp,"Opcion received: %d\n",rxRec[0]);
			//gtk_text_buffer_insert(TextBuffer, &iter, tmp, -1);
			delay(2);
			taskMaster(rxRec[0]);
			// Clear register for quit interrupt
			RF24L01_clear_interrupts();
			bNrf = 0;
			break;
		case 2: // Data send
			bNrf = 0;
			RF24L01_clear_interrupts();
			// Set mode reception module NRF24L01+
			RF24L01_set_mode_RX();
			//gtk_text_buffer_insert(TextBuffer, &iter, "Esperando Dato...\n", -1);
			// Clear register for quit interrupt
			//showMessageSnDt(idMessage);
			// stop timer
			//g_timer_elapsed(timer1, &end_usTR);
			// calcule diferencia de time
			//time_usTR = (end_usTR - start_usTR);
			//show data in text view
			//sprintf(tmp, "Tiempo transcurrido: %d us\n", time_usTR);
			//gtk_text_buffer_insert(TextBuffer, &iter, tmp, -1);
			break;
		case 3:
			// stop timer
			//g_timer_elapsed(timer1, &end_usTR);
			// calcule diferencia de time
			//time_usTR = (end_usTR - start_usTR);
			//show data in text view
			//sprintf(tmp, "Max RT tiempo: %d us\n", time_usTR);
			//gtk_text_buffer_insert(TextBuffer, &iter, tmp, -1);
			// Set mode reception module NRF24L01+
			RF24L01_set_mode_RX();
			//gtk_text_buffer_insert(TextBuffer, &iter, "Esperando Dato...\n", -1);
			// Clear register for quit interrupt
			RF24L01_clear_interrupts();
			showMessageMxRt(idMessage);
			bNrf = 0;
			break;
		default:
			break;
	} // end switch
} // End interrupcion

/**
 * @brief Opction that send time 1 and time 4 for calculate delay and offset in slave
 * 
 * @param opt 
 */
void taskMaster(uint8_t opt)
{
	switch(opt){
		case 1:// send time 1
			getTimeClock(timeClock);
			txEnv[0] = 1;
			txEnv[10] = 1;
			sendData(txEnv);
			break;
		case 2:// sent time 4
			getTimeClock(timeClock);
			txEnv[0] = 1;
			txEnv[10] = 2;
			sendData(txEnv);
			break;
		case 3:// End 
			showMessageSync(idMessage);
			RF24L01_powerDown();
			break;
		case 4://
			plotData(idMessage);
			//txEnv[0] = 4;
			//if(stopMesure)
			//	txEnv[0] = 5;
			//sendData(txEnv);
			break;
		case 5:
			showMessagePruebas(idMessage);
			RF24L01_powerDown();
			break;
		default:// show message end syncronization
			RF24L01_powerDown();
			break;	
	}
}

void plotData(uint8_t id)
{
	int aux, fX, fY, fZ;
	switch(id){
		case 1:
			aux = 0;
			aux = (int)rxRec[1]<<12 | (int)rxRec[2] << 4 | (int)rxRec[3]>> 4;
			if ((aux & (1 << 19)) != 0)
				aux = aux | ~((1 << 20) - 1);
			fX = aux;
			//fX = aux / 256000.00;
			aux = 0;
			aux = (int)rxRec[4]<<12 | (int)rxRec[5] << 4 | (int)rxRec[6]>> 4;
			if ((aux & (1 << 19)) != 0)
				aux = aux | ~((1 << 20) - 1);
			fY = aux;
			//fY = aux / 256000.00;

			aux = 0;
			aux = (int)rxRec[7]<<12 | (int)rxRec[8] << 4 | (int)rxRec[9]>> 4;
			if ((aux & (1 << 19)) != 0)
				aux = aux | ~((1 << 20) - 1);
			//fZ = aux / 256000.00;
			fZ = aux;

			aux = 0;
			// Get mesure corrient
			aux = (int)rxRec[11]<< 8 | rxRec[10] ;
			float voltage = (3.3/4095.0)*aux;
			voltage = voltage - 0.33;
			float current = (voltage/0.132)*1000; // current in Ampere
			// Use for save dates in File DatosGps
			FILE *p;
			p = fopen("logfile","at");
			if(p == NULL)
			{
				printf("Error al crear el archivo\n");
			}
			else
			{	
				fprintf(p,"%10d\t%10d\t%10d\t%10d\t%03.3f\t%10d\n",iteratorGraph, fX, fY, fZ, current, 0);
				iteratorGraph++;
				fclose(p);
			}
			if(iteratorGraph == 50){
				generarGraph();
			}
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
			break;
		case 10:
			break;
		default:
			break;
	}
}


/**
 * @brief Function show time each second and save date and time in file only first times and 
 * matching clock only first time whit the time of the Gps 
 * 
 * @return gboolean 
 */
gboolean showDataGps()
{
	// Use for save date longitud y latitud when start aplication in file.txt and match clock
	if(bArchivo == 1)
	{
		g_timer_reset(timer);
		g_timer_elapsed(timer,&start_us);
		// Get data of module Gps
		data = getDataGps();
		// Check out if there is data in Gps
		if(data.month != 0 && data.day != 0 && data.year != 0)
		{
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
		} // end check out if ther are data in Gps
	} //End save for first sometime in file.txt
	// Blink Led
	blinkLed();
	// get time 
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


/**
 * @brief Set the Address Tx object for transmition
 * 
 * @param value 
 */
void setAddressTx(uint8_t value)
{
	uint8_t i;

	for(i=0;i<5;i++)
	{
		tx_addr[i] = value;
	}

} // End setAddressTx


/**
 * @brief Set the Address Rx object
 * 
 * @param value 
 */
void setAddressRx(uint8_t value)
{
	uint8_t i ;

	for(i=0;i<5;i++)
	{
		rx_addr[i] = value;
	}

} // End setAddressRx


/**
 * @brief Set the Addres Nrf object of the sattion video or nodeX
 * 
 * @param idNodo 
 */
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
			setAddressTx(0xA1);
			break;
		default:
			//Addres Receive
			setAddressRx(0x78);
        	//Addres Transive
			setAddressTx(0x78);
			break;
	} // End swintch
} // End setAddresNrf


/**
 * @brief Use for color button
 * 
 */
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


/**
 * @brief Set the Clock object fo raspberry pi
 * 
 * @param clock 
 * @param tSec 
 * @param tnSec 
 */
void setClock(clockid_t clock, time_t tSec, long tnSec)
{
    struct timespec tp = {tSec, tnSec};
    if(clock_settime(clock, &tp) == -1 )
    {
        perror("clock_settime");
        exit(EXIT_FAILURE);
    }
}// set clock of raspberry pi

/**
 * @brief Get the Time Clock object, get time of the raspberry seconds,
 * nanoseconds and set data in txEnv
 * 
 * @param in 
 */
void getTimeClock(int in[2])
{
	struct timespec ts;
	if (clock_gettime(CLOCK_REALTIME, &ts) == -1) 
	{
		perror("clock_gettime");
		exit(EXIT_FAILURE);
	}
    in[0] = (int) ts.tv_sec;
    in[1] = (int) ts.tv_nsec;
	// Get Seconds and convert to uint8_t
	txEnv[0] = 0;
	txEnv[1] = in[0];
	txEnv[2] = (in[0] >> 8);
	txEnv[3] = (in[0] >> 16);
	txEnv[4] = (in[0] >> 24);
	// Get microSeconds and convert to uint8_t
	txEnv[5] = in[1];
	txEnv[6] = (in[1] >> 8);
	txEnv[7] = (in[1] >> 16);
	txEnv[8] = (in[1] >> 24);
	txEnv[9] = 0;
	txEnv[10] = 0;
	txEnv[11] = 0;
	txEnv[12] = 0;	
} // end getTime

void showMessageMxRt(uint8_t id)
{
	switch(id){
		case 1:// Message production for nodo 1
			sprintf(tmp,"Dato no enviado intente nuevamente\n");
			gtk_text_buffer_insert(tbN1, &iN1, tmp, -1);
			idMessage = 0;
			break;
		case 2:
			//show mesage of Nodo2
			break;
		case 3:
			//show mesage of Nodo3
			break;
		case 11: // message production for estacion video
			sprintf(tmp, "Maximo numero de retransmisiones\nIntente nuevamente\n");
			gtk_text_buffer_insert(TextBuffer, &iter, tmp, -1);
			idMessage = 0;
			break;
		case 12:// Mensage muestreo
			sprintf(tmp, "No se envio el dato para iniciar muestreo");
			gtk_label_set_text(GTK_LABEL(lbNTM), tmp);
			idMessage = 0;
			break;
		default:
			break;
		
	}
} // end showMessageMxRxt

void showMessageSnDt(uint8_t id)
{
	switch(id){
		case 1:// Message production for nodo 1
			sprintf(tmp,"Dato enviado correctamente\n");
			gtk_text_buffer_insert(tbN1, &iN1, tmp, -1);
			break;
		case 2:
			//show mesage of Nodo1
			break;
		case 3:
			//show mesage of Nodo2
			break;
		case 11: // message production for estacion video
			idMessage = 0;
			break;
		case 12:// Mensage muestreo
			sprintf(tmp, "Inicio Muestreo Correctamente");
			gtk_label_set_text(GTK_LABEL(lbNTM), tmp);
			idMessage = 0;
			break;
		default:
			break;
		
	}
	
}

void showMessageRcDt(uint8_t id)
{
	switch(id){
		case 1:// Message production for nodo 1
			sprintf(tmp,"Dato recibido\n");
			gtk_text_buffer_insert(tbN1, &iN1, tmp, -1);
			sprintf(tmp,"%02d:%02d:%02d  %02d/%02d/%02d \n",rxRec[3],rxRec[2],rxRec[1], rxRec[5],rxRec[4], rxRec[6]);
			gtk_text_buffer_insert(tbN1, &iN1, tmp, -1);
			break;
		case 2:
			//show mesage of Nodo1
			break;
		case 3:
			//show mesage of Nodo2
			break;
		case 11: // message production for estacion video
			
			break;
		case 12:// Mensage muestreo
			sprintf(tmp, "Inicio Muestreo Correctamente");
			gtk_label_set_text(GTK_LABEL(lbNTM), tmp);
			
			break;
		default:
			break;
		
	}
	
}


void showMessageSync(uint8_t id)
{
	switch(id){
		case 1:// Message production for nodo 1
			sprintf(tmp,"Sincronizacion Completada Exitosamente\n");
			gtk_text_buffer_insert(tbN1, &iN1, tmp, -1);
			gtk_widget_set_name(bSyncN1, "myButton_green");
			gtk_button_set_label((GtkButton *)bSyncN1, "Iniciar Prueba");
			opcbNodos = 2;
			//sprintf(tmp,"%02d:%02d:%02d  %02d/%02d/%02d \n",rxRec[3],rxRec[2],rxRec[1], rxRec[5],rxRec[4], rxRec[6]);
			//gtk_text_buffer_insert(tbN1, &iN1, tmp, -1);
			break;
		case 2:
			//show mesage of Nodo1
			break;
		case 3:
			//show mesage of Nodo2
			break;
		case 11: // message production for estacion video
			sprintf(tmp, "Sincronizacion Completada\n");
			gtk_text_buffer_insert(TextBuffer, &iter, tmp, -1);
			break;
		case 12:// Mensage muestreo
			sprintf(tmp, "Inicio Muestreo Correctamente");
			gtk_label_set_text(GTK_LABEL(lbNTM), tmp);
			
			break;
		default:
			break;
		
	}
	
}

void showMessagePruebas(uint8_t op){
	switch(op){
		case 1:
			sprintf(tmp,"Prueba realizada con exito\n");
			gtk_text_buffer_insert(tbN1, &iN1, tmp, -1);
			break;
		default:
			printf("Error\n");
			break;
	}
}

void generarGraph(void)
{				
	sockN1 = gtk_socket_new ();
	gtk_widget_set_size_request(sockN1, 400, 400);
	gtk_container_add (GTK_CONTAINER (bxNodo1), sockN1);
	sockIdN1 = gtk_socket_get_id(GTK_SOCKET(sockN1));
	sprintf(tmp, "gnuplot -c monitor.gp \"%x\" &\n",sockIdN1);
	gtk_widget_show_all(window);
	system(tmp);
}

uint8_t existFile(void)
{
    FILE *arch;
    arch = fopen("logfile","r");
    if (arch == NULL)
    {
        return 0;
    }
    else
    {
        fclose(arch);
        return 1;  
    }
} // en exist



/**
 * Fin File
 */

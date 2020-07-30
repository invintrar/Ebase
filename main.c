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



/**
 * Function Main
 */
int main(int argc, char *argv[])
{
	XInitThreads();
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
	//timer1 = g_timer_new();
	
	//Set port of the lmaed how output
    pinMode(LED,OUTPUT);

    builder = gtk_builder_new();

    gtk_builder_add_from_file (builder, "interfazG.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

    gtk_builder_connect_signals(builder, NULL);

	lbTime = GTK_WIDGET(gtk_builder_get_object(builder, "lbTime"));
	lbDate = GTK_WIDGET(gtk_builder_get_object(builder, "lbDate"));
	lbLatitud = GTK_WIDGET(gtk_builder_get_object(builder, "lbLatitud"));
	lbLongitud = GTK_WIDGET(gtk_builder_get_object(builder, "lbLongitud"));
	lbNTM = GTK_WIDGET(gtk_builder_get_object(builder, "lbNTM"));
	lbCurrentN1 = GTK_WIDGET(gtk_builder_get_object(builder, "lbCurrentN1"));
	lbCurrentN2 = GTK_WIDGET(gtk_builder_get_object(builder, "lbCurrentN2"));
	lbCurrentN3 = GTK_WIDGET(gtk_builder_get_object(builder, "lbCurrentN3"));
	lbCurrentN4 = GTK_WIDGET(gtk_builder_get_object(builder, "lbCurrentN4"));
	lbCurrentN5 = GTK_WIDGET(gtk_builder_get_object(builder, "lbCurrentN5"));
	lbCurrentN6 = GTK_WIDGET(gtk_builder_get_object(builder, "lbCurrentN6"));
	lbCurrentN7 = GTK_WIDGET(gtk_builder_get_object(builder, "lbCurrentN7"));
	lbCurrentN8 = GTK_WIDGET(gtk_builder_get_object(builder, "lbCurrentN8"));
	lbCurrentN90 = GTK_WIDGET(gtk_builder_get_object(builder, "lbCurrentN90"));
	lbCurrentN10 = GTK_WIDGET(gtk_builder_get_object(builder, "lbCurrentN10"));
	ScrollWindow = GTK_WIDGET(gtk_builder_get_object(builder, "ScrollWindow"));
	TextView = GTK_WIDGET(gtk_builder_get_object(builder, "TextView"));
	swN1 = GTK_WIDGET(gtk_builder_get_object(builder, "swN1"));
	swN2 = GTK_WIDGET(gtk_builder_get_object(builder, "swN2"));
	tvN1 = GTK_WIDGET(gtk_builder_get_object(builder, "tvN1"));
	tvN2 = GTK_WIDGET(gtk_builder_get_object(builder, "tvN2"));
	tvN3 = GTK_WIDGET(gtk_builder_get_object(builder, "tvN3"));
	tvN4 = GTK_WIDGET(gtk_builder_get_object(builder, "tvN4"));
	tvN5 = GTK_WIDGET(gtk_builder_get_object(builder, "tvN5"));
	tvN6 = GTK_WIDGET(gtk_builder_get_object(builder, "tvN6"));
	tvN7 = GTK_WIDGET(gtk_builder_get_object(builder, "tvN7"));
	tvN8 = GTK_WIDGET(gtk_builder_get_object(builder, "tvN8"));
	tvN9 = GTK_WIDGET(gtk_builder_get_object(builder, "tvN9"));
	tvN10 = GTK_WIDGET(gtk_builder_get_object(builder, "tvN10"));
	fSinc = GTK_WIDGET(gtk_builder_get_object(builder, "fSinc"));
    bxNodo1 = GTK_WIDGET(gtk_builder_get_object(builder, "bxNodo1"));
	bxNodo2 = GTK_WIDGET(gtk_builder_get_object(builder, "bxNodo2"));
	bxNodo3 = GTK_WIDGET(gtk_builder_get_object(builder, "bxNodo3"));
	bxNodo4 = GTK_WIDGET(gtk_builder_get_object(builder, "bxNodo4"));
	bxNodo5 = GTK_WIDGET(gtk_builder_get_object(builder, "bxNodo5"));
	bxNodo60 = GTK_WIDGET(gtk_builder_get_object(builder, "bxNodo60"));
	bxNodo7 = GTK_WIDGET(gtk_builder_get_object(builder, "bxNodo7"));
	bxNodo8 = GTK_WIDGET(gtk_builder_get_object(builder, "bxNodo8"));
	bxNodo6 = GTK_WIDGET(gtk_builder_get_object(builder, "bxNodo6"));
	bxNodo10 = GTK_WIDGET(gtk_builder_get_object(builder, "bxNodo10"));
    button = GTK_WIDGET(gtk_builder_get_object(builder, "bipMuestreo"));
	bSyncVideo = GTK_WIDGET(gtk_builder_get_object(builder, "bSyncVideo"));
	bSyncN1 = GTK_WIDGET(gtk_builder_get_object(builder, "bSyncN1"));
	bSyncN2 = GTK_WIDGET(gtk_builder_get_object(builder, "bSyncN2"));
	bSyncN3 = GTK_WIDGET(gtk_builder_get_object(builder, "bSyncN3"));
	bSyncN4 = GTK_WIDGET(gtk_builder_get_object(builder, "bSyncN4"));
	bSyncN5 = GTK_WIDGET(gtk_builder_get_object(builder, "bSyncN5"));
	bSyncN6 = GTK_WIDGET(gtk_builder_get_object(builder, "bSyncN6"));
	bSyncN7 = GTK_WIDGET(gtk_builder_get_object(builder, "bSyncN7"));
	bSyncN8 = GTK_WIDGET(gtk_builder_get_object(builder, "bSyncN8"));
	bSyncN9 = GTK_WIDGET(gtk_builder_get_object(builder, "bSyncN9"));
	bSyncN10 = GTK_WIDGET(gtk_builder_get_object(builder, "bSyncN10"));
    sbHoras = GTK_WIDGET(gtk_builder_get_object(builder, "sbHoras"));
    sbMinutos = GTK_WIDGET(gtk_builder_get_object(builder, "sbMinutos"));
	sbSegundos = GTK_WIDGET(gtk_builder_get_object(builder, "sbSegundos"));
	TextBuffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (TextView));
	tbN1 = gtk_text_view_get_buffer (GTK_TEXT_VIEW (tvN1));
	tbN2 = gtk_text_view_get_buffer (GTK_TEXT_VIEW (tvN2));
	tbN3 = gtk_text_view_get_buffer (GTK_TEXT_VIEW (tvN3));
	tbN4 = gtk_text_view_get_buffer (GTK_TEXT_VIEW (tvN4));
	tbN5 = gtk_text_view_get_buffer (GTK_TEXT_VIEW (tvN5));
	tbN6 = gtk_text_view_get_buffer (GTK_TEXT_VIEW (tvN6));
	tbN7 = gtk_text_view_get_buffer (GTK_TEXT_VIEW (tvN7));
	tbN8 = gtk_text_view_get_buffer (GTK_TEXT_VIEW (tvN8));
	tbN9 = gtk_text_view_get_buffer (GTK_TEXT_VIEW (tvN9));
	tbN10 = gtk_text_view_get_buffer (GTK_TEXT_VIEW (tvN10));

	gtk_widget_set_name(button, "myButton_yellow");
	gtk_widget_set_name(bSyncVideo, "myButton_green");
	gtk_widget_set_name(bSyncN1, "myButton_blue");
	gtk_widget_set_name(bSyncN2, "myButton_black");
	gtk_widget_set_name(bSyncN3, "myButton_blue");
	gtk_widget_set_name(bSyncN4, "myButton_black");
	gtk_widget_set_name(bSyncN5, "myButton_blue");
	gtk_widget_set_name(bSyncN6, "myButton_black");
	gtk_widget_set_name(bSyncN7, "myButton_blue");
	gtk_widget_set_name(bSyncN8, "myButton_black");
	gtk_widget_set_name(bSyncN9, "myButton_blue");
	gtk_widget_set_name(bSyncN10, "myButton_black");
	
    g_object_unref(builder);
	//gtk_widget_hide(fSinc);
	
	gtk_text_buffer_get_iter_at_offset(TextBuffer, &iter, 0);
	gtk_text_buffer_get_iter_at_offset(tbN1, &iN1, 0);
	gtk_text_buffer_get_iter_at_offset(tbN2, &iN2, 0);
	gtk_text_buffer_get_iter_at_offset(tbN3, &iN3, 0);
	gtk_text_buffer_get_iter_at_offset(tbN4, &iN4, 0);
	gtk_text_buffer_get_iter_at_offset(tbN5, &iN5, 0);
	gtk_text_buffer_get_iter_at_offset(tbN6, &iN6, 0);
	gtk_text_buffer_get_iter_at_offset(tbN7, &iN7, 0);
	gtk_text_buffer_get_iter_at_offset(tbN8, &iN8, 0);
	gtk_text_buffer_get_iter_at_offset(tbN9, &iN9, 0);
	gtk_text_buffer_get_iter_at_offset(tbN10, &iN10, 0);

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
	char tmp1[100];
	RF24L01_powerDown();
    gtk_main_quit();
	LedOff();
	// delete record video if exist 
	if(existFile())
    {
        sprintf(tmp1, "rm logfile");
        system(tmp1);
    }
}


/**
 * @brief Button for init mesure of station video
 * 
 */
void on_bSyncVideo_clicked()
{
	char tmp1[100] = {0};
	idDispositivo = 11; // Estacion video identificador 11
	sprintf(tmp1,"Synchronization start\n");
	mIter = gtk_text_buffer_get_insert (TextBuffer);
	gtk_text_buffer_get_iter_at_mark (tbN1, &iN1, mIter);
	gtk_text_buffer_insert(TextBuffer, &iter, tmp1, -1);
	// Set Addres for Transmitir
	setAddresNrf(idDispositivo);
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
	char tmp1[100] = {0};
	idDispositivo = 1;
	// Set Addres for Transmitir
	setAddresNrf(idDispositivo);
	//Settign address nrf and channel
	RF24L01_setup(tx_addr, rx_addr, CHANNEL); 

	switch(opcBn1){
		case 1:
			// Cuand pulso Sincronizar
			//gtk_widget_set_name(bSyncN1, "myButton_green");
			//gtk_button_set_label((GtkButton *)bSyncN1, "Iniciar Prueba");
			sprintf(tmp1,"Synchronization started Node%02d\n",idDispositivo);
			mN1 = gtk_text_buffer_get_insert (tbN1);
			gtk_text_buffer_get_iter_at_mark (tbN1, &iN1, mN1);
			gtk_text_buffer_insert(tbN1, &iN1, tmp1, -1);
			getTimeClock(timeClock);
			txEnv[0] = 2;
			sendData(txEnv);
			break;
		case 2:
			// Cuando pulso Iniciar prueba
			gtk_widget_set_name(bSyncN1, "myButton_blue");
			gtk_button_set_label((GtkButton *)bSyncN1, "Stop test"); // Parar prueba

			sprintf(tmp1,"Start test Node%02d\n",idDispositivo);
			mN1 = gtk_text_buffer_get_insert (tbN1);
			gtk_text_buffer_get_iter_at_mark (tbN1, &iN1, mN1);
			gtk_text_buffer_insert(tbN1, &iN1, tmp1, -1);
			txEnv[0] = 3;
			sendData(txEnv);		
			opcBn1 = 3;
			iteratorGraph = 0;
			break;
		default:// Cuando se preciona parar prueba
			gtk_widget_set_name(bSyncN1, "myButton_blue");
			gtk_button_set_label((GtkButton *)bSyncN1, "Satart test");
			archivo = fopen("logfile","at");
			if(archivo == NULL)
			{
				printf("Error al crear el archivo\n");
			}
			else
			{	
				fprintf(archivo,"%10d\t%10d\t%10d\t%10d\t%10d\n",0, 0, 0, 0, 1);
				fclose(archivo);
			}
			iteratorGraph = 0;
			opcBn1 = 2;
			txEnv[0] = 5;
			sendData(txEnv);
			break;
	}
} // End on_bSyncN1_clicked


void on_bSyncN2_clicked() 
{
	char tmp1[100] = {0};
	idDispositivo = 2;
	// Set Addres for Transmitir
	setAddresNrf(idDispositivo);
	//Settign address nrf and channel
	RF24L01_setup(tx_addr, rx_addr, CHANNEL); 

	switch(opcBn2){
		case 1:
			sprintf(tmp1,"Synchronization started...\n");
			mN2 = gtk_text_buffer_get_insert (tbN2);
			gtk_text_buffer_get_iter_at_mark (tbN2, &iN2, mN2);
			gtk_text_buffer_insert(tbN2, &iN2, tmp1, -1);
			getTimeClock(timeClock);
			txEnv[0] = 2;
			sendData(txEnv);
			break;
		case 2:
			// Cuando pulso Iniciar prueba
			gtk_widget_set_name(bSyncN2, "myButton_blue");
			gtk_button_set_label((GtkButton *)bSyncN2, "Stop test"); // Parar prueba
			// Escribimos en el buffer 
			sprintf(tmp1,"Start test\n");
			mN2 = gtk_text_buffer_get_insert (tbN2);
			gtk_text_buffer_get_iter_at_mark (tbN2, &iN2, mN2);
			gtk_text_buffer_insert(tbN2, &iN2, tmp1, -1);
			txEnv[0] = 3;
			sendData(txEnv);		
			opcBn2 = 3;
			break;
		default:// Cuando se preciona parar prueba
			gtk_widget_set_name(bSyncN2, "myButton_blue");
			gtk_button_set_label((GtkButton *)bSyncN2, "Satart test");
			archivo = fopen("logfile","at");
			if(archivo == NULL)
			{
				printf("Error al crear el archivo\n");
			}
			else
			{	
				fprintf(archivo,"%10d\t%10d\t%10d\t%10d\t%10d\n",0, 0, 0, 0, 1);
				fclose(archivo);
			}
			iteratorGraph = 0;
			opcBn2 = 2;
			txEnv[0] = 5;
			sendData(txEnv);
			break;
	}
} // End on_bSyncN2_clicked


void on_bSyncN3_clicked() 
{
	char tmp1[100] = {0};
	idDispositivo = 3;
	// Set Addres for Transmitir
	setAddresNrf(idDispositivo);
	//Settign address nrf and channel
	RF24L01_setup(tx_addr, rx_addr, CHANNEL); 

	switch(opcBn3){
		case 1:
			// Cuand pulso Sincronizar
			sprintf(tmp1,"Synchronization started...\n");
			mN3 = gtk_text_buffer_get_insert (tbN3);
			gtk_text_buffer_get_iter_at_mark (tbN3, &iN3, mN3);
			gtk_text_buffer_insert(tbN3, &iN3, tmp1, -1);
			getTimeClock(timeClock);
			txEnv[0] = 2;
			sendData(txEnv);
			break;
		case 2:
			// Cuando pulso Iniciar prueba
			gtk_widget_set_name(bSyncN3, "myButton_blue");
			gtk_button_set_label((GtkButton *)bSyncN3, "Stop test"); // Parar prueba
			// Escribimos en le buffer
			sprintf(tmp1,"Start test\n");
			mN3 = gtk_text_buffer_get_insert (tbN3);
			gtk_text_buffer_get_iter_at_mark (tbN3, &iN3, mN3);
			gtk_text_buffer_insert(tbN3, &iN3, tmp1, -1);
			txEnv[0] = 3;
			sendData(txEnv);		
			opcBn3 = 0;
			break;
		default:
			// Cuando se preciona parar prueba
			gtk_widget_set_name(bSyncN3, "myButton_blue");
			gtk_button_set_label((GtkButton *)bSyncN3, "Satart test");
			archivo = fopen("logfile","at");
			if(archivo == NULL)
			{
				printf("Error al crear el archivo\n");
			}
			else
			{	
				fprintf(archivo,"%10d\t%10d\t%10d\t%10d\t%10d\n",0, 0, 0, 0, 1);
				fclose(archivo);
			}
			iteratorGraph = 0;
			opcBn3 = 2;
			txEnv[0] = 5;
			sendData(txEnv);
			break;
	}
} // End on_bSyncN3_clicked


void on_bSyncN4_clicked() 
{
	char tmp1[100] = {0};
	idDispositivo = 4;
	// Set Addres for Transmitir
	setAddresNrf(idDispositivo);
	//Settign address nrf and channel
	RF24L01_setup(tx_addr, rx_addr, CHANNEL); 

	switch(opcBn4){
		case 1:
			// Cuand pulso Sincronizar
			sprintf(tmp1,"Synchronization started...\n");
			mN4 = gtk_text_buffer_get_insert (tbN4);
			gtk_text_buffer_get_iter_at_mark (tbN4, &iN4, mN4);
			gtk_text_buffer_insert(tbN4, &iN4, tmp1, -1);
			getTimeClock(timeClock);
			txEnv[0] = 2;
			sendData(txEnv);
			break;
		case 2:
			// Cuando pulso Iniciar prueba
			gtk_widget_set_name(bSyncN4, "myButton_blue");
			gtk_button_set_label((GtkButton *)bSyncN4, "Stop test"); // Parar prueba
			// Escribimos en el buffer
			sprintf(tmp1,"Start test\n");
			mN4 = gtk_text_buffer_get_insert (tbN4);
			gtk_text_buffer_get_iter_at_mark (tbN4, &iN4, mN4);
			gtk_text_buffer_insert(tbN4, &iN4, tmp1, -1);
			txEnv[0] = 3;
			sendData(txEnv);		
			opcBn4 = 0;
			break;
		default:
			// Cuando se preciona parar prueba
			gtk_widget_set_name(bSyncN4, "myButton_blue");
			gtk_button_set_label((GtkButton *)bSyncN4, "Satart test");
			archivo = fopen("logfile","at");
			if(archivo == NULL)
			{
				printf("Error al crear el archivo\n");
			}
			else
			{	
				fprintf(archivo,"%10d\t%10d\t%10d\t%10d\t%10d\n",0, 0, 0, 0, 1);
				fclose(archivo);
			}
			iteratorGraph = 0;
			opcBn4 = 2;
			txEnv[0] = 5;
			sendData(txEnv);
			break;
	}
} // End on_bSyncN4_clicked


void on_bSyncN5_clicked() 
{
	char tmp1[100] = {0};
	idDispositivo = 5;
	// Set Addres for Transmitir
	setAddresNrf(idDispositivo);
	//Settign address nrf and channel
	RF24L01_setup(tx_addr, rx_addr, CHANNEL); 

	switch(opcBn5){
		case 1:
			// Cuand pulso Sincronizar
			sprintf(tmp1,"Synchronization started...\n");
			mN5 = gtk_text_buffer_get_insert (tbN5);
			gtk_text_buffer_get_iter_at_mark (tbN5, &iN5, mN5);
			gtk_text_buffer_insert(tbN5, &iN5, tmp1, -1);
			getTimeClock(timeClock);
			txEnv[0] = 2;
			sendData(txEnv);
			break;
		case 2:
			// Cuando pulso Iniciar prueba
			gtk_widget_set_name(bSyncN5, "myButton_blue");
			gtk_button_set_label((GtkButton *)bSyncN5, "Stop test"); // Parar prueba
			// Escribimos en el buffer
			mN5 = gtk_text_buffer_get_insert (tbN5);
			gtk_text_buffer_get_iter_at_mark (tbN5, &iN5, mN5);
			sprintf(tmp1,"Start test\n");
			gtk_text_buffer_insert(tbN5, &iN5, tmp1, -1);
			txEnv[0] = 3;
			sendData(txEnv);		
			opcBn5 = 0;
			break;
		default:
			// Cuando se preciona parar prueba
			gtk_widget_set_name(bSyncN5, "myButton_blue");
			gtk_button_set_label((GtkButton *)bSyncN5, "Satart test");
			archivo = fopen("logfile","at");
			if(archivo == NULL)
			{
				printf("Error al crear el archivo\n");
			}
			else
			{	
				fprintf(archivo,"%10d\t%10d\t%10d\t%10d\t%10d\n",0, 0, 0, 0, 1);
				fclose(archivo);
			}
			iteratorGraph = 0;
			opcBn5 = 2;
			txEnv[0] = 5;
			sendData(txEnv);
			break;
	}
} // End on_bSyncN5_clicked


void on_bSyncN6_clicked() 
{
	char tmp1[100] = {0};
	idDispositivo = 6;
	// Set Addres for Transmitir
	setAddresNrf(idDispositivo);
	//Settign address nrf and channel
	RF24L01_setup(tx_addr, rx_addr, CHANNEL); 

	switch(opcBn6){
		case 1:
			// Cuand pulso Sincronizar
			sprintf(tmp1,"Synchronization started...\n");
			mN6 = gtk_text_buffer_get_insert (tbN6);
			gtk_text_buffer_get_iter_at_mark (tbN6, &iN6, mN6);
			gtk_text_buffer_insert(tbN6, &iN6, tmp1, -1);
			getTimeClock(timeClock);
			txEnv[0] = 2;
			sendData(txEnv);
			break;
		case 2:
			// Cuando pulso Iniciar prueba
			gtk_widget_set_name(bSyncN6, "myButton_blue");
			gtk_button_set_label((GtkButton *)bSyncN6, "Stop test"); // Parar prueba
			// Escribimo en el buffer
			sprintf(tmp1,"Start test\n");
			mN6 = gtk_text_buffer_get_insert (tbN6);
			gtk_text_buffer_get_iter_at_mark (tbN6, &iN6, mN6);
			gtk_text_buffer_insert(tbN6, &iN6, tmp1, -1);
			txEnv[0] = 3;
			sendData(txEnv);		
			opcBn6 = 0;
			break;
		default:
			// Cuando se preciona parar prueba
			gtk_widget_set_name(bSyncN6, "myButton_blue");
			gtk_button_set_label((GtkButton *)bSyncN6, "Satart test");
			archivo = fopen("logfile","at");
			if(archivo == NULL)
			{
				printf("Error al crear el archivo\n");
			}
			else
			{	
				fprintf(archivo,"%10d\t%10d\t%10d\t%10d\t%10d\n",0, 0, 0, 0, 1);
				fclose(archivo);
			}
			iteratorGraph = 0;
			opcBn6 = 2;
			txEnv[0] = 5;
			sendData(txEnv);
			break;
	}
} // End on_bSyncN5_clicked

void on_bSyncN7_clicked() 
{
	char tmp1[100] = {0};
	idDispositivo = 7;
	// Set Addres for Transmitir
	setAddresNrf(idDispositivo);
	//Settign address nrf and channel
	RF24L01_setup(tx_addr, rx_addr, CHANNEL); 

	switch(opcBn7){
		case 1:
			// Cuand pulso Sincronizar
			sprintf(tmp1,"Synchronization started...\n");
			mN7 = gtk_text_buffer_get_insert (tbN7);
			gtk_text_buffer_get_iter_at_mark (tbN7, &iN7, mN7);
			gtk_text_buffer_insert(tbN7, &iN7, tmp1, -1);
			getTimeClock(timeClock);
			txEnv[0] = 2;
			sendData(txEnv);
			break;
		case 2:
			// Cuando pulso Iniciar prueba
			gtk_widget_set_name(bSyncN7, "myButton_blue");
			gtk_button_set_label((GtkButton *)bSyncN7, "Stop test"); // Parar prueba
			// Escribimos buffer
			sprintf(tmp1,"Start test\n");
			mN7 = gtk_text_buffer_get_insert (tbN7);
			gtk_text_buffer_get_iter_at_mark (tbN7, &iN7, mN7);
			gtk_text_buffer_insert(tbN7, &iN7, tmp1, -1);
			txEnv[0] = 3;
			sendData(txEnv);		
			opcBn7 = 0;
			break;
		default:
			// Cuando se preciona parar prueba
			gtk_widget_set_name(bSyncN7, "myButton_blue");
			gtk_button_set_label((GtkButton *)bSyncN7, "Satart test");
			archivo = fopen("logfile","at");
			if(archivo == NULL)
			{
				printf("Error al crear el archivo\n");
			}
			else
			{	
				fprintf(archivo,"%10d\t%10d\t%10d\t%10d\t%10d\n",0, 0, 0, 0, 1);
				fclose(archivo);
			}
			iteratorGraph = 0;
			opcBn7 = 2;
			txEnv[0] = 5;
			sendData(txEnv);
			break;
	}
} // End on_bSyncN7_clicked


void on_bSyncN8_clicked() 
{
	char tmp1[100] = {0};
	idDispositivo = 8;
	// Set Addres for Transmitir
	setAddresNrf(idDispositivo);
	//Settign address nrf and channel
	RF24L01_setup(tx_addr, rx_addr, CHANNEL); 

	switch(opcBn8){
		case 1:
			// Cuand pulso Sincronizar
			sprintf(tmp1,"Synchronization started...\n");
			mN8 = gtk_text_buffer_get_insert (tbN8);
			gtk_text_buffer_get_iter_at_mark (tbN8, &iN8, mN8);
			gtk_text_buffer_insert(tbN8, &iN8, tmp1, -1);
			getTimeClock(timeClock);
			txEnv[0] = 2;
			sendData(txEnv);
			break;
		case 2:
			// Cuando pulso Iniciar prueba
			gtk_widget_set_name(bSyncN8, "myButton_blue");
			gtk_button_set_label((GtkButton *)bSyncN8, "Stop test"); // Parar prueba
			sprintf(tmp1,"Start test\n");
			mN8 = gtk_text_buffer_get_insert (tbN8);
			gtk_text_buffer_get_iter_at_mark (tbN8, &iN8, mN8);
			gtk_text_buffer_insert(tbN8, &iN8, tmp1, -1);
			txEnv[0] = 3;
			sendData(txEnv);		
			opcBn8 = 0;
			break;
		default:
			// Cuando se preciona parar prueba
			gtk_widget_set_name(bSyncN8, "myButton_blue");
			gtk_button_set_label((GtkButton *)bSyncN8, "Satart test");
			archivo = fopen("logfile","at");
			if(archivo == NULL)
			{
				printf("Error al crear el archivo\n");
			}
			else
			{	
				fprintf(archivo,"%10d\t%10d\t%10d\t%10d\t%10d\n",0, 0, 0, 0, 1);
				fclose(archivo);
			}
			iteratorGraph = 0;
			opcBn8 = 2;
			txEnv[0] = 5;
			sendData(txEnv);
			break;
	}
} // End on_bSyncN8_clicked

void on_bSyncN9_clicked() 
{
	char tmp1[100] = {0};
	idDispositivo = 9;
	// Set Addres for Transmitir
	setAddresNrf(idDispositivo);
	//Settign address nrf and channel
	RF24L01_setup(tx_addr, rx_addr, CHANNEL); 

	switch(opcBn9){
		case 1:
			// Cuand pulso Sincronizar
			sprintf(tmp1,"Synchronization started...\n");
			mN9 = gtk_text_buffer_get_insert (tbN9);
			gtk_text_buffer_get_iter_at_mark (tbN9, &iN9, mN9);
			gtk_text_buffer_insert(tbN9, &iN9, tmp1, -1);
			getTimeClock(timeClock);
			txEnv[0] = 2;
			sendData(txEnv);
			break;
		case 2:
			// Cuando pulso Iniciar prueba
			gtk_widget_set_name(bSyncN9, "myButton_blue");
			gtk_button_set_label((GtkButton *)bSyncN9, "Stop test"); // Parar prueba
			sprintf(tmp1,"Start test\n");
			mN9 = gtk_text_buffer_get_insert (tbN9);
			gtk_text_buffer_get_iter_at_mark (tbN9, &iN9, mN9);
			gtk_text_buffer_insert(tbN9, &iN9, tmp1, -1);
			txEnv[0] = 3;
			sendData(txEnv);		
			opcBn9 = 0;
			break;
		default:
			// Cuando se preciona parar prueba
			gtk_widget_set_name(bSyncN9, "myButton_blue");
			gtk_button_set_label((GtkButton *)bSyncN9, "Satart test");
			archivo = fopen("logfile","at");
			if(archivo == NULL)
			{
				printf("Error al crear el archivo\n");
			}
			else
			{	
				fprintf(archivo,"%10d\t%10d\t%10d\t%10d\t%10d\n",0, 0, 0, 0, 1);
				fclose(archivo);
			}
			iteratorGraph = 0;
			opcBn9 = 2;
			txEnv[0] = 5;
			sendData(txEnv);
			break;
	}
} // End on_bSyncN9_clicked

void on_bSyncN10_clicked() 
{
	char tmp1[100] = {0};
	idDispositivo = 10;
	// Set Addres for Transmitir
	setAddresNrf(idDispositivo);
	//Settign address nrf and channel
	RF24L01_setup(tx_addr, rx_addr, CHANNEL); 

	switch(opcBn10){
		case 1:
			// Cuand pulso Sincronizar
			sprintf(tmp1,"Synchronization started...\n");
			mN10 = gtk_text_buffer_get_insert (tbN10);
			gtk_text_buffer_get_iter_at_mark (tbN10, &iN10, mN10);
			gtk_text_buffer_insert(tbN10, &iN10, tmp1, -1);
			getTimeClock(timeClock);
			txEnv[0] = 2;
			sendData(txEnv);
			break;
		case 2:
			// Cuando pulso Iniciar prueba
			gtk_widget_set_name(bSyncN10, "myButton_blue");
			gtk_button_set_label((GtkButton *)bSyncN10, "Stop test"); // Parar prueba
			sprintf(tmp1,"Start test\n");
			mN10 = gtk_text_buffer_get_insert (tbN10);
			gtk_text_buffer_get_iter_at_mark (tbN10, &iN10, mN10);
			gtk_text_buffer_insert(tbN10, &iN10, tmp1, -1);
			txEnv[0] = 3;
			sendData(txEnv);		
			opcBn10 = 0;
			break;
		default:
			// Cuando se preciona parar prueba
			gtk_widget_set_name(bSyncN10, "myButton_blue");
			gtk_button_set_label((GtkButton *)bSyncN10, "Satart test");
			archivo = fopen("logfile","at");
			if(archivo == NULL)
			{
				printf("Error al crear el archivo\n");
			}
			else
			{	
				fprintf(archivo,"%10d\t%10d\t%10d\t%10d\t%10d\n",0, 0, 0, 0, 1);
				fclose(archivo);
			}
			iteratorGraph = 0;
			opcBn10 = 2;
			txEnv[0] = 5;
			sendData(txEnv);
			break;
	}
} // End on_bSyncN10_clicked


/**
 * @brief Action when clicked button start measuring
 * 
 */
void bipMuestreo_clicked()
{
	char tmp1[100] = {0};
	static gboolean running = true;
	
	timerHoras = gtk_spin_button_get_value_as_int((GtkSpinButton *)sbHoras);
    timerMinutos = gtk_spin_button_get_value_as_int((GtkSpinButton *)sbMinutos);
	timerSegundos = gtk_spin_button_get_value_as_int((GtkSpinButton *)sbSegundos);

	if(running)
	{
		if(timerMinutos > 0 || timerHoras > 0 || timerSegundos)
		{
			if(verificaSync == 66){// utilizado para verificar que se sincronize el nodo all//66
				sprintf(tmp1, "Sent pulse start");
				gtk_label_set_text(GTK_LABEL(lbNTM), tmp1);
				// identificador de dispositivo
				idDispositivo = 1;
				// Set Addres for Transmitir
				setAddresNrf(idDispositivo);
				//Settign address nrf and channel
				RF24L01_setup(tx_addr, rx_addr, CHANNEL);
				// Obtenemos el tiempo que se enviara para inicio de muestreo
				getTimeClock(timeClock);
				// Opcion para Muestrear y el tiempo de muestreo
				txEnv[0] = 4; // instruccion para los nodos
				txEnv[9] = timerSegundos;
				txEnv[10] = timerMinutos;
				txEnv[11] = timerHoras;
				idMesure = 1;
				sendData(txEnv);
				//sprintf(tmp, "Valor para muestreo: %02d:%02d:%02d",
				//timerHoras, timerMinutos, timerSegundos);
				//gtk_label_set_text(GTK_LABEL(lbNTM), tmp);
				gtk_widget_set_name(button, "myButton_red");
				gtk_button_set_label((GtkButton *)button, "Turn Off NRF");
				running = !running;

			}else{
				sprintf(tmp1, "Synchronize all devices");
				gtk_label_set_text(GTK_LABEL(lbNTM), tmp1);
			}
			
		}else
		{
			sprintf(tmp1, "Enter value > 0");
			gtk_label_set_text(GTK_LABEL(lbNTM), tmp1);
		}
	}
	else
	{
		RF24L01_powerDown();
		sprintf(tmp1, "Turn off Nrf24L01+ module");
		gtk_label_set_text(GTK_LABEL(lbNTM), tmp1);
		// Use for show start measure
		gtk_widget_set_name(button, "myButton_green");
		gtk_button_set_label((GtkButton *)button, "Start Measuring");
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
 * @brief Function interrupt for NRF24L01+ when 
 * send data or received data and maximum retransmition
 * 
 */
void interrupcionNRF()
{
	char tmp1[100] = {0};
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
			delay(3); // Cuidado con este tiempo es el ideal para la sincronizacion 3ms
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
			if(idMesure){
				sprintf(tmp1, "Error en la transmision Intente nuevamente");
				gtk_label_set_text(GTK_LABEL(lbNTM), tmp1);
				idMesure = 0;
			}
			showMessageMxRt(idDispositivo);
			bNrf = 0;
			break;
		default:
			break;
	} // end switch
} // End interrupcionNRF

/**
 * @brief Opction that send time 1 and time 4 for calculate delay and offset in slave
 * 
 * @param opt 
 */
void taskMaster(uint8_t opt)
{
	char tmp1[100] = {0};
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
		case 3:// End Sincronizacion
			showMessageSync(idDispositivo);
			RF24L01_powerDown();
			break;
		case 4://Recive datos del nodo
			generarGrafica(idDispositivo);
			break;
		case 5: // Termina la prueba de envio de datos
			showMessagePruebas(idDispositivo);
			RF24L01_powerDown();
			break;
		case 6:
			RF24L01_powerDown();
			if(rxRec[1] == idDispositivo)
			{
				verificaInicioCorrecto += idDispositivo;
				if(verificaInicioCorrecto == 66)// 66
				{
					sprintf(tmp1, "Correct Start Of Start Pulse.");
					gtk_label_set_text(GTK_LABEL(lbNTM), tmp1);
					verificaInicioCorrecto = 0;
				}else
				{
					idDispositivo +=  1;
					sendPulseMesure(idDispositivo); 
				}
			}else{
				sendPulseMesure(idDispositivo);
			}
			break;
		default:// show message end syncronization
			RF24L01_powerDown();
			break;	
	}
} // end taskMaster


void sendPulseMesure(uint8_t device)
{
	// Set Addres for Transmitir
	setAddresNrf(device);
	//Settign address nrf and channel
	RF24L01_setup(tx_addr, rx_addr, CHANNEL);
	idMesure = 1;
	sendData(txEnv);
} // end sendPulseMesure


void generarGrafica(uint8_t idN)
{
	int aux, fX, fY, fZ;
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
	sumCurrent += aux;
	if(countCurrent > 10){
		float average = (float) sumCurrent / 10.0;
		float voltage = (3.3/4095.0) * average;
		voltage = voltage - 0.33;
		current = (voltage/0.132) * 1000.0; // current in mA
		current = current/2.25;
		showCurrent(idDispositivo,current);
		countCurrent = 0;
		sumCurrent = 0;
	}
	countCurrent++;
	// Use for save dates in File DatosGps
	FILE *p;
	p = fopen("logfile","at");
	if(p == NULL)
	{
		printf("Error al crear el archivo\n");
	}
	else
	{
		fprintf(p,"%10d\t%10d\t%10d\t%10d\t%10d\n",iteratorGraph, fX, fY, fZ, 0);
		iteratorGraph++;
		fclose(p);
	}
	if(iteratorGraph == 10){
		plotData(idN);
	}
} // end generarGrafica


void plotData(uint8_t id)
{
	char tmp1[200] = {0};
	int sockId = 0;
	sock = gtk_socket_new ();
	gtk_widget_set_size_request(sock, 400, 400);
	switch(id){
		case 1:
			gtk_container_add (GTK_CONTAINER (bxNodo1), sock);
			break;
		case 2:
			gtk_container_add (GTK_CONTAINER (bxNodo2), sock);
			break;
		case 3:
			gtk_container_add (GTK_CONTAINER (bxNodo3), sock);
			break;
		case 4:
			gtk_container_add (GTK_CONTAINER (bxNodo4), sock);
			break;
		case 5:
			gtk_container_add (GTK_CONTAINER (bxNodo5), sock);
			break;
		case 6:
			gtk_container_add (GTK_CONTAINER (bxNodo60), sock);
			break;
		case 7:
			gtk_container_add (GTK_CONTAINER (bxNodo7), sock);
			break;
		case 8:
			gtk_container_add (GTK_CONTAINER (bxNodo8), sock);
			break;
		case 9:
			gtk_container_add (GTK_CONTAINER (bxNodo6), sock);
			break;
		case 10:
			gtk_container_add (GTK_CONTAINER (bxNodo10), sock);
			break;
		default:
			printf("No existe box contenedor\n");
			break;
	}
	sockId = gtk_socket_get_id(GTK_SOCKET(sock));
	sprintf(tmp1, "gnuplot -c monitor.gp \"%x\" &\n",sockId);
	gtk_widget_show_all(window);
	system(tmp1);
} // end plotData

void* create(void *data)
{
	char tmp1[100] = {0};
	int sockId = 0;
	sock = gtk_socket_new ();
	gtk_widget_set_size_request(sock, 400, 400);
	gtk_container_add (GTK_CONTAINER (bxNodo6), sock);
	sockId = gtk_socket_get_id(GTK_SOCKET(sock));
	sprintf(tmp1, "gnuplot -c monitor.gp \"%x\" &\n",sockId);
	gtk_widget_show_all(window);
	system(tmp1);
	return NULL;
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
			timeSet.tm_mday = data.day0;
			timeSet.tm_hour = data.hour0;
			timeSet.tm_min = data.minute;
			timeSet.tm_sec = data.second;
			//timeSet.tm_isdst = 0;
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
} // End showDataGps each seconds


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
		case 1://Nodo1
			//Addres Receive
			setAddressRx(0xA1);
		   	//Addres Transive
			setAddressTx(0xA1);
			break;
		case 2://Nodo2
			//Addres Receive
			setAddressRx(0xA2);
		   	//Addres Transive
			setAddressTx(0xA2);
			break;
		case 3://Nodo3
			//Addres Receive
			setAddressRx(0xA3);
		   	//Addres Transive
			setAddressTx(0xA3);
			break;
		case 4://Nodo4
			//Addres Receive
			setAddressRx(0xA4);
		   	//Addres Transive
			setAddressTx(0xA4);
			break;
		case 5://Nodo5
			//Addres Receive
			setAddressRx(0xA5);
		   	//Addres Transive
			setAddressTx(0xA5);
			break;
		case 6://Nodo6
			//Addres Receive
			setAddressRx(0xA6);
		   	//Addres Transive
			setAddressTx(0xA6);
			break;
		case 7://Nodo7
			//Addres Receive
			setAddressRx(0xA7);
		   	//Addres Transive
			setAddressTx(0xA7);
			break;
		case 8://Nodo8
			//Addres Receive
			setAddressRx(0xA8);
		   	//Addres Transive
			setAddressTx(0xA8);
			break;
		case 9://Nodo9
			//Addres Receive
			setAddressRx(0xA9);
		   	//Addres Transive
			setAddressTx(0xA9);
			break;
		case 10://Nodo10
			//Addres Receive
			setAddressRx(0x79);
		   	//Addres Transive
			setAddressTx(0x79);
			break;
		case 11://Estacion video
			//Addres Receive
			setAddressRx(0x78);
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
	char tmp1[100] = {0};
	sprintf(tmp1,"Maximum number of retransmissions\nTry again\n");
	switch(id){
		case 1:// Message production for nodo 1
			mN1 = gtk_text_buffer_get_insert (tbN1);
			gtk_text_buffer_get_iter_at_mark (tbN1, &iN1, mN1);
			gtk_text_buffer_insert(tbN1, &iN1, tmp1,-1);
			//insertTextN1 ("Maximum number of retransmissions\nTry again\n");
			//insertText();
			break;
		case 2:// Message production for nodo 2
			mN2 = gtk_text_buffer_get_insert (tbN2);
			gtk_text_buffer_get_iter_at_mark (tbN2, &iN2, mN2);
			gtk_text_buffer_insert(tbN2, &iN2, tmp1, -1);
			break;
		case 3:// Message production for nodo 3
			mN3 = gtk_text_buffer_get_insert (tbN3);
			gtk_text_buffer_get_iter_at_mark (tbN3, &iN3, mN3);
			gtk_text_buffer_insert(tbN3, &iN3, tmp1, -1);
			break;
		case 4:// Message production for nodo 4
			mN4 = gtk_text_buffer_get_insert (tbN4);
			gtk_text_buffer_get_iter_at_mark (tbN4, &iN4, mN4);
			gtk_text_buffer_insert(tbN4, &iN4, tmp1, -1);
			break;
		case 5:// Message production for nodo 5
			mN5 = gtk_text_buffer_get_insert (tbN5);
			gtk_text_buffer_get_iter_at_mark (tbN5, &iN5, mN5);
			gtk_text_buffer_insert(tbN5, &iN5, tmp1, -1);
			break;
		case 6:// Message production for nodo 6
			mN6 = gtk_text_buffer_get_insert (tbN6);
			gtk_text_buffer_get_iter_at_mark (tbN6, &iN6, mN6);
			gtk_text_buffer_insert(tbN6, &iN6, tmp1, -1);
			break;
		case 7:// Message production for nodo 7
			mN7 = gtk_text_buffer_get_insert (tbN7);
			gtk_text_buffer_get_iter_at_mark (tbN7, &iN7, mN7);
			gtk_text_buffer_insert(tbN7, &iN7, tmp1, -1);
			break;
		case 8:// Message production for nodo 8
			mN8 = gtk_text_buffer_get_insert (tbN8);
			gtk_text_buffer_get_iter_at_mark (tbN8, &iN8, mN8);
			gtk_text_buffer_insert(tbN8, &iN8, tmp1, -1);
			break;
		case 9:// Message production for nodo 9
			mN9 = gtk_text_buffer_get_insert (tbN9);
			gtk_text_buffer_get_iter_at_mark (tbN9, &iN9, mN9);
			gtk_text_buffer_insert(tbN9, &iN9, tmp1, -1);
			break;
		case 10:// Message production for nodo 10
			mN10 = gtk_text_buffer_get_insert (tbN10);
			gtk_text_buffer_get_iter_at_mark (tbN10, &iN10, mN10);
			gtk_text_buffer_insert(tbN10, &iN10, tmp1, -1);
			break;
		case 11: // message production for estacion video
			mIter = gtk_text_buffer_get_insert (TextBuffer);
			gtk_text_buffer_get_iter_at_mark (TextBuffer, &iter, mIter);
			gtk_text_buffer_insert(TextBuffer, &iter, tmp1, -1);
			break;
		default:
			break;
	}
} // end showMessageMxRxt

void showMessageSync(uint8_t id)
{
	char tmp1[100] = {0};
	switch(id){
		case 1:// Message production for nodo 1
			sprintf(tmp1,"Synchronization Successfully Completed\n");
			mN1 = gtk_text_buffer_get_insert (tbN1);
			gtk_text_buffer_get_iter_at_mark (tbN1, &iN1, mN1);
			gtk_text_buffer_insert(tbN1, &iN1, tmp1, -1);

			gtk_widget_set_name(bSyncN1, "myButton_green");
			gtk_button_set_label((GtkButton *)bSyncN1, "Start test");
			opcBn1 = 2;
			sprintf(tmp1,"%02d:%02d:%02d  %02d/%02d/%02d \n",rxRec[3],rxRec[2],rxRec[1], rxRec[5],rxRec[4], rxRec[6]);
			mN1 = gtk_text_buffer_get_insert (tbN1);
			gtk_text_buffer_get_iter_at_mark (tbN1, &iN1, mN1);
			gtk_text_buffer_insert(tbN1, &iN1, tmp1, -1);
			verificaSync += id;
			break;
		case 2:// Message production for nodo 2
			sprintf(tmp1,"Synchronization Successfully Completed\n");
			mN2 = gtk_text_buffer_get_insert (tbN2);
			gtk_text_buffer_get_iter_at_mark (tbN2, &iN2, mN2);
			gtk_text_buffer_insert(tbN2, &iN2, tmp1, -1);
			gtk_widget_set_name(bSyncN2, "myButton_green");
			gtk_button_set_label((GtkButton *)bSyncN2, "Start test");
			opcBn2 = 2;
			sprintf(tmp1,"%02d:%02d:%02d  %02d/%02d/%02d \n",rxRec[3],rxRec[2],rxRec[1], rxRec[5],rxRec[4], rxRec[6]);
			mN2 = gtk_text_buffer_get_insert (tbN2);
			gtk_text_buffer_get_iter_at_mark (tbN2, &iN2, mN2);
			gtk_text_buffer_insert(tbN2, &iN2, tmp1, -1);
			verificaSync += id;
			break;
		case 3:// Message production for nodo 3
			sprintf(tmp1,"Synchronization Successfully Completed\n");
			mN3 = gtk_text_buffer_get_insert (tbN3);
			gtk_text_buffer_get_iter_at_mark (tbN3, &iN3, mN3);
			gtk_text_buffer_insert(tbN3, &iN3, tmp1, -1);
			gtk_widget_set_name(bSyncN3, "myButton_green");
			gtk_button_set_label((GtkButton *)bSyncN3, "Start test");
			opcBn3 = 2;
			sprintf(tmp1,"%02d:%02d:%02d  %02d/%02d/%02d \n",rxRec[3],rxRec[2],rxRec[1], rxRec[5],rxRec[4], rxRec[6]);
			mN3 = gtk_text_buffer_get_insert (tbN3);
			gtk_text_buffer_get_iter_at_mark (tbN3, &iN3, mN3);
			gtk_text_buffer_insert(tbN3, &iN3, tmp1, -1);
			verificaSync += id;
			break;
		case 4:// Message production for nodo 4
			sprintf(tmp1,"Synchronization Successfully Completed\n");
			mN4 = gtk_text_buffer_get_insert (tbN4);
			gtk_text_buffer_get_iter_at_mark (tbN4, &iN4, mN4);
			gtk_text_buffer_insert(tbN4, &iN4, tmp1, -1);
			gtk_widget_set_name(bSyncN4, "myButton_green");
			gtk_button_set_label((GtkButton *)bSyncN4, "Start test");
			opcBn4 = 2;
			sprintf(tmp1,"%02d:%02d:%02d  %02d/%02d/%02d \n",rxRec[3],rxRec[2],rxRec[1], rxRec[5],rxRec[4], rxRec[6]);
			mN4 = gtk_text_buffer_get_insert (tbN4);
			gtk_text_buffer_get_iter_at_mark (tbN4, &iN4, mN4);
			gtk_text_buffer_insert(tbN4, &iN4, tmp1, -1);
			verificaSync += id;
			break;
		case 5:// Message production for nodo 5
			sprintf(tmp1,"Synchronization Successfully Completed\n");
			mN5 = gtk_text_buffer_get_insert (tbN5);
			gtk_text_buffer_get_iter_at_mark (tbN5, &iN5, mN5);
			gtk_text_buffer_insert(tbN5, &iN5, tmp1, -1);
			gtk_widget_set_name(bSyncN5, "myButton_green");
			gtk_button_set_label((GtkButton *)bSyncN5, "Start test");
			opcBn5 = 2;
			sprintf(tmp1,"%02d:%02d:%02d  %02d/%02d/%02d \n",rxRec[3],rxRec[2],rxRec[1], rxRec[5],rxRec[4], rxRec[6]);
			mN5 = gtk_text_buffer_get_insert (tbN5);
			gtk_text_buffer_get_iter_at_mark (tbN5, &iN5, mN5);
			gtk_text_buffer_insert(tbN5, &iN5, tmp1, -1);
			verificaSync += id;
			break;
		case 6:// Message production for nodo 6
			sprintf(tmp1,"Synchronization Successfully Completed\n");
			mN6 = gtk_text_buffer_get_insert (tbN6);
			gtk_text_buffer_get_iter_at_mark (tbN6, &iN6, mN6);
			gtk_text_buffer_insert(tbN6, &iN6, tmp1, -1);
			gtk_widget_set_name(bSyncN6, "myButton_green");
			gtk_button_set_label((GtkButton *)bSyncN6, "Start test");
			opcBn6 = 2;
			sprintf(tmp1,"%02d:%02d:%02d  %02d/%02d/%02d \n",rxRec[3],rxRec[2],rxRec[1], rxRec[5],rxRec[4], rxRec[6]);
			mN6 = gtk_text_buffer_get_insert (tbN6);
			gtk_text_buffer_get_iter_at_mark (tbN6, &iN6, mN6);
			gtk_text_buffer_insert(tbN6, &iN6, tmp1, -1);
			verificaSync += id;
			break;
		case 7:// Message production for nodo 7
			sprintf(tmp1,"Synchronization Successfully Completed\n");
			mN7 = gtk_text_buffer_get_insert (tbN7);
			gtk_text_buffer_get_iter_at_mark (tbN7, &iN7, mN7);
			gtk_text_buffer_insert(tbN7, &iN7, tmp1, -1);
			gtk_widget_set_name(bSyncN7, "myButton_green");
			gtk_button_set_label((GtkButton *)bSyncN7, "Start test");
			opcBn7 = 2;
			sprintf(tmp1,"%02d:%02d:%02d  %02d/%02d/%02d \n",rxRec[3],rxRec[2],rxRec[1], rxRec[5],rxRec[4], rxRec[6]);
			mN7 = gtk_text_buffer_get_insert (tbN7);
			gtk_text_buffer_get_iter_at_mark (tbN7, &iN7, mN7);
			gtk_text_buffer_insert(tbN7, &iN7, tmp1, -1);
			verificaSync += id;
			break;
		case 8:// Message production for nodo 8
			sprintf(tmp1,"Synchronization Successfully Completed\n");
			mN8 = gtk_text_buffer_get_insert (tbN8);
			gtk_text_buffer_get_iter_at_mark (tbN8, &iN8, mN8);
			gtk_text_buffer_insert(tbN8, &iN8, tmp1, -1);
			gtk_widget_set_name(bSyncN8, "myButton_green");
			gtk_button_set_label((GtkButton *)bSyncN8, "Start test");
			opcBn8 = 2;
			sprintf(tmp1,"%02d:%02d:%02d  %02d/%02d/%02d \n",rxRec[3],rxRec[2],rxRec[1], rxRec[5],rxRec[4], rxRec[6]);
			mN8 = gtk_text_buffer_get_insert (tbN8);
			gtk_text_buffer_get_iter_at_mark (tbN8, &iN8, mN8);
			gtk_text_buffer_insert(tbN8, &iN8, tmp1, -1);
			verificaSync += id;
			break;
		case 9:// Message production for nodo 9
			sprintf(tmp1,"Synchronization Successfully Completed\n");
			mN9 = gtk_text_buffer_get_insert (tbN9);
			gtk_text_buffer_get_iter_at_mark (tbN9, &iN9, mN9);
			gtk_text_buffer_insert(tbN9, &iN9, tmp1, -1);
			gtk_widget_set_name(bSyncN9, "myButton_green");
			gtk_button_set_label((GtkButton *)bSyncN9, "Start test");
			opcBn9 = 2;
			sprintf(tmp1,"%02d:%02d:%02d  %02d/%02d/%02d \n",rxRec[3],rxRec[2],rxRec[1], rxRec[5],rxRec[4], rxRec[6]);
			mN9 = gtk_text_buffer_get_insert (tbN9);
			gtk_text_buffer_get_iter_at_mark (tbN9, &iN9, mN9);
			gtk_text_buffer_insert(tbN9, &iN9, tmp1, -1);
			verificaSync += id;
			break;	
		case 10:// Message production for nodo 10
			sprintf(tmp1,"Synchronization Successfully Completed\n");
			mN10 = gtk_text_buffer_get_insert (tbN10);
			gtk_text_buffer_get_iter_at_mark (tbN10, &iN10, mN10);
			gtk_text_buffer_insert(tbN10, &iN10, tmp1, -1);
			gtk_widget_set_name(bSyncN10, "myButton_green");
			gtk_button_set_label((GtkButton *)bSyncN10, "Start test");
			opcBn10 = 2;
			sprintf(tmp1,"%02d:%02d:%02d  %02d/%02d/%02d \n",rxRec[3],rxRec[2],rxRec[1], rxRec[5],rxRec[4], rxRec[6]);
			gtk_text_buffer_insert(tbN10, &iN10, tmp1, -1);
			verificaSync += id;
			break;	
		case 11: // message production for estacion video
			sprintf(tmp1,"Synchronization Successfully Completed\n");
			mIter = gtk_text_buffer_get_insert (TextBuffer);
			gtk_text_buffer_get_iter_at_mark (TextBuffer, &iter, mIter);
			gtk_text_buffer_insert(TextBuffer, &iter, tmp1, -1);
			verificaSync += id;
			gtk_widget_hide(bSyncVideo);
			break;
		default:
			break;
	}
	
} // end showMessageSync


void showMessagePruebas(uint8_t op)
{
	char tmp1[100] = {0};
	sprintf(tmp1,"Test successfully completed\n");
	switch(op){
		case 1:
			mN1 = gtk_text_buffer_get_insert (tbN1);
			gtk_text_buffer_get_iter_at_mark (tbN1, &iN1, mN1);
			gtk_text_buffer_insert(tbN1, &iN1, tmp1, -1);
			break;
		case 2:
			mN2 = gtk_text_buffer_get_insert (tbN2);
			gtk_text_buffer_get_iter_at_mark (tbN2, &iN2, mN2);
			gtk_text_buffer_insert(tbN2, &iN2, tmp1, -1);
			break;
		case 3:
			mN3 = gtk_text_buffer_get_insert (tbN3);
			gtk_text_buffer_get_iter_at_mark (tbN3, &iN3, mN3);
			gtk_text_buffer_insert(tbN3, &iN3, tmp1, -1);
			break;
		case 4:
			mN4 = gtk_text_buffer_get_insert (tbN4);
			gtk_text_buffer_get_iter_at_mark (tbN4, &iN4, mN4);
			gtk_text_buffer_insert(tbN4, &iN4, tmp1, -1);
			break;
		case 5:
			mN5 = gtk_text_buffer_get_insert (tbN5);
			gtk_text_buffer_get_iter_at_mark (tbN5, &iN5, mN5);
			gtk_text_buffer_insert(tbN5, &iN5, tmp1, -1);
			break;
		case 6:
			mN6 = gtk_text_buffer_get_insert (tbN6);
			gtk_text_buffer_get_iter_at_mark (tbN6, &iN6, mN6);
			gtk_text_buffer_insert(tbN6, &iN6, tmp1, -1);
			break;
		case 7:
			mN7 = gtk_text_buffer_get_insert (tbN7);
			gtk_text_buffer_get_iter_at_mark (tbN7, &iN7, mN7);
			gtk_text_buffer_insert(tbN7, &iN7, tmp1, -1);
			break;
		case 8:
			mN8 = gtk_text_buffer_get_insert (tbN8);
			gtk_text_buffer_get_iter_at_mark (tbN8, &iN8, mN8);
			gtk_text_buffer_insert(tbN8, &iN8, tmp1, -1);
			break;
		case 9:
			mN9 = gtk_text_buffer_get_insert (tbN9);
			gtk_text_buffer_get_iter_at_mark (tbN9, &iN9, mN9);
			gtk_text_buffer_insert(tbN9, &iN9, tmp1, -1);
			break;
		case 10:
			mN10 = gtk_text_buffer_get_insert (tbN10);
			gtk_text_buffer_get_iter_at_mark (tbN10, &iN10, mN10);
			gtk_text_buffer_insert(tbN10, &iN10, tmp1, -1);
			break;
		default:
			printf("Error\n");
			break;
	}
} // end showMessagePruebas


void showCurrent(uint8_t op, float intensidad)
{
	char tmp1[100] = {0};
	sprintf( tmp1, "Current: %.3f mA", intensidad);
	switch(op){
		case 1:
			gtk_label_set_text(GTK_LABEL(lbCurrentN1), tmp1);
			break;
		case 2:
			gtk_label_set_text(GTK_LABEL(lbCurrentN2), tmp1);
			break;
		case 3:
			gtk_label_set_text(GTK_LABEL(lbCurrentN3), tmp1);
			break;
		case 4:
			gtk_label_set_text(GTK_LABEL(lbCurrentN4), tmp1);
			break;
		case 5:
			gtk_label_set_text(GTK_LABEL(lbCurrentN5), tmp1);
			break;
		case 6:
			gtk_label_set_text(GTK_LABEL(lbCurrentN6), tmp1);
			break;
		case 7:
			gtk_label_set_text(GTK_LABEL(lbCurrentN7), tmp1);
			break;
		case 8:
			gtk_label_set_text(GTK_LABEL(lbCurrentN8), tmp1);
			break;
		case 9:
			gtk_label_set_text(GTK_LABEL(lbCurrentN90), tmp1);
			break;
		case 10:
			gtk_label_set_text(GTK_LABEL(lbCurrentN10), tmp1);
			break;
		default:
			break;
	}
} // end showCurrent


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
} // end existFile


/**
 * Fin File
 */

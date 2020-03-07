#include "main.h"

int serialPort;
dataGps data;
uint8_t run = 1;
pthread_t hilo1;

GtkWidget *lbTime ;
GtkWidget *lbDate ;
GtkWidget *lbLatitud ;
GtkWidget *lbLongitud ;
//GtkWidget *framGps;

void sincronizar();
gboolean getGps();
void stop();

int main(int argc, char *argv[])
{
    GtkBuilder      *builder; 
    GtkWidget       *window;

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

// called when window is closed
void on_window_destroy()
{
    gtk_main_quit();
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

void sincronizar(){
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
	getGps();
}

gboolean  getGps(){
	char buffer[10];
    //gtk_widget_show(framGps);                

	//pthread_create(&hilo1,NULL,sincronizar,NULL);
	//pthread_join(hilo1,NULL);

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


//Fin File

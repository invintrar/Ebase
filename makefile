all:
	gcc -o out main.c gps.c nrf24l01.c -lm -lwiringPi -Wall  `pkg-config --cflags --libs gtk+-3.0` -export-dynamic -lX11 -rdynamic

all:
	gcc -o output main.c gps.c nrf24l01.c -lm -lwiringPi -Wall  `pkg-config --cflags --libs gtk+-3.0` -export-dynamic 
	./output
	rm output

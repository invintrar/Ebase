/**
 * @author: DzhL
 * @version: v1.0
 * @since: 2/14/2020
 */

#include "main.h"

uint8_t run;
/**
 * @brief Bucle main
 * 
 */
int main(int argc, char *argv[])
{
    uint8_t i;
	run = 1;
    // Setting Port CE and SPI and wiringPi
	RF24L01_init();
	// Setting address nrf and channel 
    for(i = 0; i<5;i++){
        tx_addr[i]= 0x78;
        rx_addr[i]= 0x78;
    }
	RF24L01_setup(tx_addr, rx_addr, CHANNEL);
    // Setting led output
	Led_SetOutput();
	// Setting Interrupt for NRF2L01+
	wiringPiISR(RF_IRQ , INT_EDGE_FALLING, interrupcion);
	// Interrupt when catch Ctrl-C
	signal(SIGINT, intHandler);
	//turn On led
	LedOn();
    //RF24L01_sendData(txEnv);
	//delay(3); luego de enviar el dato no tenemos que hacer nada durante 3 ms o mas
	// Bucle while
	while(run)
	{
		switch(bNrf)
		{
			case 1://Data received
				bNrf = 0;
				RF24L01_read_payload(rxRec, sizeof(rxRec));
				printf("Dato Recibido Opcion: %d\n", rxRec[0]);
                break;
			case 2://Date Sent
				printf("Dato Enviado\n");
				bNrf = 4;
				break;
			case 3://MAX_RT
				printf("Maximo Numero de Retransmisiones\n");
                bNrf = 0;
				break;
            case 4:// Set module NRF24L01+ in mode reception
                bNrf = 0;
                RF24L01_set_mode_RX();
				printf("-----Mode  RX-----\nEsperando  Dato...\n");
                break;
			default:
				break;
		} // end switch
	} // End while
	return 0;
} // End Main


/**
 * @brief Interrupt of the nrf when receive data or sent data
 * or error in transmition.
 * 
 */
void interrupcion(void)
{
	// Return 1:RX_DR(Data Received), 2:Data Sent,
    // 3:MAX_RT(Maximun number retransmition in mode Transmisition
	bNrf = RF24L01_status();
	RF24L01_clear_interrupts();
} // end Interrupt


/**
 * @brief Interrupcion utilizada para terminar el programa 
 * utilizando Ctrl c
 * 
 * @param dummy 
 */
void intHandler(int dummy)
{
	LedOff();
	RF24L01_powerDown();
	run =0;
} // end catch Ctrl C


/**
 * End File
 */
/*
 * spi.c
 *
 *  Created on: 24/11/2022
 *      Author: jppma
 */

#include "spi.h"
#include "fgpio.h"
#include "timers.h"

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

//#include <stddef.h>

void SPI_Init ( void){
	//Configura GPIO

	//gpiodir(0, 18, OUT);
	//iopullup(0, 18, NONE);
	iotype(0, 18, THIRD);		//MOSI pag 118

	//gpiodir(0, 17, IN);
	//iopullup(0, 17, NONE);
	iotype(0, 17, THIRD);		//MISO pag 118

	//gpiowrbit(0, 16, SET);		//CS=1
	//gpiodir(0, 16, OUT);
	iotype(0, 16, THIRD);		//SSEL é entrada para Slave  pag 118

	//gpiodir(0, 15, OUT);
	//iopullup(0, 15, NONE);
	iotype(0, 15, THIRD);		//SCK pag 117

	gpiowrbit(0, 23, SET);		//CS=1
	gpiodir(0, 23, OUT);
	iotype(0, 23, GPIO);

	//Configura SPI
	LPC_SC->PCONP |= 1<<PCSPI;				//Power SPI pag 65
	LPC_SC->PCLKSEL0 &= ~(3 << PCLK_SPI);
	LPC_SC->PCLKSEL0 |= 1 << PCLK_SPI;		//Clock for SPI = CCLK  (pag 58 e 59)

}



void SPI_Config(int frequency, int bitData , int mode){
	unsigned int div=SystemCoreClock/frequency;
	if (div & 0x1){
		++div;								//Número par
	}
	if(div<8) div=8;						//O valor da divisão não pode ser menor do que 8 pag 420

	//Página 418
	//CPOL é o bit 4, CPHA é o bit 3
	//Mode 0 -> CPOL=0 e CPHA=0
	//Mode 1 -> CPOL=0 e CPHA=1
	//Mode 2 -> CPOL=1 e CPHA=0
	//Mode 3 -> CPOL=1 e CPHA=1

	//1º passo
	LPC_SPI->SPCCR=div;						//Table 361 e 365. Contador de 8 bits.
	//100MHz/254 = 393,7KHz frequência mais baixa neste kit

	//2ºpasso
	bitData &= 0x0000000F;					//Máscara dos 4 bits menos significativos
	mode &= 0x00000003;
	//LPC_SPI->SPCR &= ~(0b1111<<BITS);
	LPC_SPI->SPCR = bitData<<BITS;			//Define o número de bits
	LPC_SPI->SPCR |= mode<<CPHA;			//Define o modo 0,1,2,3
	LPC_SPI->SPCR |= 1<<MSTR;				//Master
	LPC_SPI->SPCR |= 1<<BitEnable;			//para colocar os bits de dados
	//LPC_SPI->SPCR |= 1<<SPIE;				//ativa o enable SPI

}


unsigned short SPI_Transfere(unsigned short value ) {

	LPC_SPI->SPDR = value;
	while(!(LPC_SPI->SPSR & 1<<SPIF));		//pag 419

	return LPC_SPI->SPDR;

}


int SPI_Transfer (unsigned short * txBuffer , unsigned short * rxBuffer , int lenght ){
	gpiowrbit(0, 23, CLR);		//CS=0
	unsigned int fault;
	for(int i=0 ;i < lenght ; ++i){
	//for(int i=0 ;i < lenght ; ++i){
		LPC_SPI->SPDR = txBuffer[i];
		do{
			fault = LPC_SPI->SPSR;
		}while (!(LPC_SPI->SPSR & 1<<SPIF));

		rxBuffer[i] = LPC_SPI->SPDR;
		if ((fault & 0x78) != 0) break;
		//rxBuffer[i] = SPI_Transfere(txBuffer[i] );
		//fault = LPC_SPI->SPINT & 0b01111000;		//pag 419 Após a aleitura apaga todos os bits
		//bit7-SPIF, bit6-WCOL, bit5-ROVR, bit4-MODF, bit3-ABRT
	}
	gpiowrbit(0, 23, SET);		//CS=1
	//0111 1000
	if(fault & 0x78) return -1;
	return 0;
}

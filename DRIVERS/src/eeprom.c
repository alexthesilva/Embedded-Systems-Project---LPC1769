/*
 * eeprom.c
 *
 *  Created on: 01/12/2022
 *
 */

#include "eeprom.h"
#include "spi.h"
#include "fgpio.h"
#include "timers.h"

//CAT25128

void eeprominit(){
	unsigned char temp;
	CAT25128_ReadByte (&temp , ASS_ADDR);
	if(temp!=ASSINATURA){

		CAT25128_WriteByte( ASSINATURA, ASS_ADDR);			//Escreve a assinatura
		CAT25128_WriteByte (0x00 , N_REG );					//Poe os numero de registos a zero
		CAT25128_WriteByte (0x00 , N_REG +1);
		CAT25128_WriteByte (DEFAULT_LIGHT , LUZ );			//Define o valor da luz
		CAT25128_WriteByte (0 , LUZ +1);
	}
}

void write_disable(void){
	unsigned short txBuffer[1];
	unsigned short rxBuffer[1];
	txBuffer[0] = WRDI;
	SPI_Transfer ( txBuffer , rxBuffer , 1 );
}

void write_enable(void){
	unsigned short txBuffer[1];
	unsigned short rxBuffer[1];
	txBuffer[0] = WREN;
	SPI_Transfer ( txBuffer , rxBuffer , 1 );
}

unsigned short read_status(void){
	unsigned short txBuffer[2];
	unsigned short rxBuffer[2];
	txBuffer[0] = RDSR;
	txBuffer[1] = 0x00;
	SPI_Transfer ( txBuffer , rxBuffer , 2 );
	unsigned short value=rxBuffer[1] & 0xFF;
	return value;
}

void dados_write(unsigned short data, unsigned int address){
	//Verifica o bit0 RDY do Status Register
	while (read_status() & 0x1);		//Verifica se a escrita está concluida

	write_enable();
	unsigned short txBuffer[4];
	unsigned short rxBuffer[4];
	txBuffer[0] = WRITE;
	txBuffer[1] = (address>>8) & 0x000000FF;
	txBuffer[2] = address & 0x000000FF;
	txBuffer[3] = data;
	SPI_Transfer ( txBuffer , rxBuffer , 4 );
	//delay de 5 milisegundos
	//WAIT_Stopwatch (6000);
}

unsigned short dados_read(unsigned int address){
	unsigned short txBuffer[4];
	unsigned short rxBuffer[4];
	txBuffer[0] = READ;
	txBuffer[1] = (address>>8) & 0x000000FF;
	txBuffer[2] = address & 0x000000FF;
	txBuffer[3] = 0x00;
	SPI_Transfer ( txBuffer , rxBuffer , 4 );
	unsigned short value=rxBuffer[3] & 0xFF;
	return value;
}


int CAT25128_WriteByte (unsigned char value , unsigned int address ){
	while (read_status() & 0x1);		//Verifica se a escrita está concluida
	write_enable();

	unsigned short txBuffer[4];
	unsigned short rxBuffer[4];
	txBuffer[0] = WRITE;
	txBuffer[1] = (address>>8) & 0x000000FF;
	txBuffer[2] = address & 0x000000FF;
	txBuffer[3] = value;
	int estado = SPI_Transfer ( txBuffer , rxBuffer , 4 );
	//delay de 5 milisegundos
	//WAIT_Stopwatch (6000);
	return estado;
}

int CAT25128_ReadByte (unsigned char * dstValue , unsigned int address ){
	unsigned short txBuffer[4];
	unsigned short rxBuffer[4];
	txBuffer[0] = READ;
	txBuffer[1] = (address>>8) & 0x000000FF;
	txBuffer[2] = address & 0x000000FF;
	txBuffer[3] = 0x00;
	int error = SPI_Transfer ( txBuffer , rxBuffer , 4 );
	*dstValue = (rxBuffer[3] & 0xFF);
	return error;

}

int CAT25128_WriteBlock ( void * srcAddr , unsigned int size , unsigned int address ){
	while (read_status() & 0x1);		//Verifica se a escrita está concluida
	write_enable();

	unsigned short txBuffer[3+size];
	unsigned short rxBuffer[3+size];

	//address=0x3E;

	txBuffer[0] = WRITE;
	txBuffer[1] = (address>>8) & 0x000000FF;
	txBuffer[2] = address & 0x000000FF;

	for(int i=0 ; i<size ; ++i){
				txBuffer[i+3] =  ((unsigned char *)srcAddr)[i];

	}

	int temp = address & 0x3F;				//Para verificar os 6 bits de página
	int estado;
	int size_temp;
	if (temp+size-1 <= 0x3F){				//Não pode ultrapassar a página
		estado = SPI_Transfer ( txBuffer , rxBuffer , size+3 );

	}else{
		size_temp=3 + 0x40-temp;
		estado = SPI_Transfer ( txBuffer , rxBuffer , size_temp);
		int j=3;
		for(int i=0x40-temp ; i<size ; ++i){
			txBuffer[j++] = txBuffer[i+3] ;		//Passa os ultimos bytes e coloca-os a partir da posição 3
		}
		address += 0x40-temp;
		txBuffer[1] = (address>>8) & 0x000000FF;
		txBuffer[2] = address & 0x000000FF;
		size_temp=3+(size-(0x40-temp));
		while (read_status() & 0x1);		//Verifica se a escrita está concluida
		write_enable();
		estado = SPI_Transfer ( txBuffer , rxBuffer , size_temp); //Envia os restantes
	}
	return estado;
}

int CAT25128_ReadBlock ( void * dstAddr , unsigned int size , unsigned int address ){
	unsigned short txBuffer[3+size];
	unsigned short rxBuffer[3+size];
	txBuffer[0] = READ;
	txBuffer[1] = (address>>8) & 0x000000FF;
	txBuffer[2] = address & 0x000000FF;

	int temp = address & 0x3F;				//Para verificar os 6 bits de página
	int estado;
	int size_temp;

	if (temp+size-1 <= 0x3F){				//Não pode ultrapassar a página
		estado = SPI_Transfer ( txBuffer , rxBuffer , size+3 );

		for(int i=0 ; i<size ; i++){
			((unsigned char *)dstAddr)[i] = rxBuffer[i+3];
		}

	}else{
		//Com mudança de página
		size_temp=3 + 0x40-temp;
		estado = SPI_Transfer ( txBuffer , rxBuffer , size_temp);
		//Recebeu o 1º conjunto de bytes
		int i;
		for(i=0 ; i<size_temp ; i++){
			((unsigned char *)dstAddr)[i] = rxBuffer[i+3];
		}

		address += 0x40-temp;				//Início da próxima página
		txBuffer[1] = (address>>8) & 0x000000FF;
		txBuffer[2] = address & 0x000000FF;
		size_temp=3+(size-(0x40-temp));
		//Lê os restantes bytes
		estado = SPI_Transfer ( txBuffer , rxBuffer , size_temp); //Recebe os restantes
		int j=3;
		for(; i<size ; i++){
			((unsigned char *)dstAddr)[i] = rxBuffer[j++];
		}

	}

	return estado;

}

#include "fgpio.h"

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

/*
FIO0SET - 0x2009 C018
FIO1SET - 0x2009 C038
FIO2SET - 0x2009 C058
FIO3SET - 0x2009 C078
FIO4SET - 0x2009 C098
*/

//estão separados 0x20 posições (ver página 132)
#define PORTOFFSET2 0x2		//2*4=8

void gpiotoggle(int port, int portbit){
	gpiowrbit(port, portbit, !gpiordlatch(port, portbit));
	//gpiowrbit(port, portbit, !gpiordpin(port, portbit));
}

bool gpiordpin(int port, int portbit){

	uint32_t *addr = (uint32_t *)&LPC_GPIO0->FIOPIN;  //pagina 132
	uint32_t *addr1 = (uint32_t *)&LPC_GPIO1->FIOPIN;

	addr += port * (addr1-addr);

	portbit = 1<<portbit;

	return (portbit & *addr);

}

bool gpiordlatch(int port, int portbit){
	//int *addr = (int *)&LPC_GPIO0->FIOSET;
	uint32_t *addr = (uint32_t *)&LPC_GPIO0->FIOSET;
	uint32_t *addr1 = (uint32_t *)&LPC_GPIO1->FIOSET;

	addr += port * (addr1-addr);

	portbit = 1<<portbit;

	return (portbit & *addr);

}

//******************
void iopullup(int port, int portbit, int type){
	//type = UP 0 (00), REPEAT 1 (01), NONE 2 (10), DOWN 3 (11)
	//Ver página 115
	type = type & 0x00000003;

	uint32_t *addr = (uint32_t *)&LPC_PINCON->PINMODE0;
	//Os endereços estão espaçados 0x4 + 0x4 posições (ver página 117)
	//O port0 está no PINMODE0(0 a 15) e PINMODE1(16 a 31)
	//O port1 está no PINMODE2 e 3
	addr += port * PORTOFFSET2;
	if(portbit>15) addr += 1; //1*4 Para passar para a parte alta da palavra de 32bits

	int data = *addr;

	if(portbit>15){
		*addr = data & ~(3<<((portbit-16)<<1));
		*addr = data | (type<<((portbit-16)<<1));
	}else{
		*addr = data & ~(3<<(portbit<<1));
		*addr = data | (type<<(portbit<<1));
	}
}
void iotype(int port, int portbit, int type){
	//type = GPIO 0 (00), FIRST 1 (01), SECOND 2 (10), THIRD 3 (11) pág 114

	type = type & 0x00000003;

	uint32_t *addr = (uint32_t *)&LPC_PINCON->PINSEL0;
	//Os endereços estão espaçados 0x4 + 0x4 posições (ver página 118)
	addr += port * PORTOFFSET2;
	if(portbit>15) addr += 1; //1*4 Para passar para a parte alta da palavra de 32bits

	int data = *addr;

	//LPC_PINCON->PINSEL1 &= ~(3<<((22-16)<<1));

	if(portbit>15){
		*addr = data & ~(3<<((portbit-16)<<1));
		*addr = data | (type<<((portbit-16)<<1));
	}else{
		*addr = data & ~(3<<(portbit<<1));
		*addr = data | (type<<(portbit<<1));
	}
}
//*********************
void gpiowr8(int port, int numbyte, int data){
	//Não existem mais do que 4 bytes
	if(numbyte>3) numbyte=3;

	//Mascara de 8 bits
	data = data & 0x000000FF;

	uint32_t *addr = (uint32_t *)&LPC_GPIO0->FIOPIN0;
	uint32_t *addr1 = (uint32_t *)&LPC_GPIO1->FIOPIN0;
	addr += port * (addr1-addr);

	//Ver páginas 138,139 e 150
	//Os endereços estão espaçados 0x20 posições

	//Os endereços estão espaçados 0x1 posições
	addr += numbyte;
	*addr = data;
}

//****************
void gpiowr16(int port, int numword, int data){
	//Não existem mais do que 2 palavras de 16bits
	if(numword>1) numword=1;
	//Mascara de 16 bits
	data = data & 0x0000FFFF;

	uint32_t *addr = (uint32_t *)&LPC_GPIO0->FIOPINL;
	uint32_t *addr1 = (uint32_t *)&LPC_GPIO1->FIOPINL;

	addr += port * (addr1-addr);

	//Ver páginas 138,139 e 150
	//Os endereços estão espaçados 0x20 posições

	//Os endereços estão espaçados 0x1 posições
	addr += numword;
	*addr = data;

}


void gpiodir(int port, int portbit, int dir){

	uint32_t *addr = (uint32_t *)&LPC_GPIO0->FIODIR;  //pag 132
	uint32_t *addr1 = (uint32_t *)&LPC_GPIO1->FIODIR;

	addr += port * (addr1-addr);

	int data = *addr;
	if(dir==OUT){
		data |= 1<<portbit;
	}else{
		data &= ~(1<<portbit);
	}

	*addr = data;

}

void gpiowrbit(int port, int portbit, bool portdata){
	//LPC_GPIO0->FIOSET = 1<<22;
	//LPC_GPIO0->FIOCLR = 1<<22;
	uint32_t *addr;
	uint32_t *addr1;

	if(portdata){
		addr = (uint32_t *)&LPC_GPIO0->FIOSET;
		addr1 = (uint32_t *)&LPC_GPIO1->FIOSET;
	}else{
		addr = (uint32_t *)&LPC_GPIO0->FIOCLR;
		addr1 = (uint32_t *)&LPC_GPIO1->FIOCLR;
	}

	addr += port * (addr1-addr);

	//estão separados 0x20 posições (ver página 132)
	*addr = 1<<portbit;
}


void gpiowr32(int port, int data){
	uint32_t *addr = (uint32_t *)&LPC_GPIO0->FIOPIN;
	uint32_t *addr1 = (uint32_t *)&LPC_GPIO1->FIOPIN;

	addr += port * (addr1-addr);

	//Os endereços estão espaçados 0x20 posições (ver página 132)


	*addr = data;
	//pode haver alterações de acordo com a página 31

}

uint32_t gpiord32_gpio(int port){
	//int *addr = (int *)&LPC_GPIO0->FIOSET;
	uint32_t *addr = (uint32_t *)&LPC_GPIO0->FIOPIN;
	uint32_t *addr1 = (uint32_t *)&LPC_GPIO1->FIOPIN;

	addr += port * (addr1-addr);


	return *addr;
}

/*
void gpiowr32_2(int port, int data){
	switch(port){
	case 0:
		//LPC_GPIO0->FIOSET |= data;
		//LPC_GPIO0->FIOCLR &= data;
		LPC_GPIO0->FIOPIN = data;
		break;

	case 1:
		//LPC_GPIO1->FIOSET |= data;
		//LPC_GPIO1->FIOCLR &= data;
		LPC_GPIO1->FIOPIN = data;
		break;

	case 2:
		//LPC_GPIO2->FIOSET |= data;
		//LPC_GPIO2->FIOCLR &= data;
		LPC_GPIO2->FIOPIN = data;
		break;
	case 3:
		//LPC_GPIO3->FIOSET |= data;
		//LPC_GPIO3->FIOCLR &= data;
		LPC_GPIO3->FIOPIN = data;
		break;
	case 4:
		//LPC_GPIO4->FIOSET |= data;
		//LPC_GPIO4->FIOCLR &= data;
		LPC_GPIO4->FIOPIN = data;
		break;
	default:
		break;
	}
}
*/
/*
uint32_t gpiord32_2(int port){

	switch(port){
	case 0:

		return LPC_GPIO0->FIOPIN;

	case 1:

		return LPC_GPIO1->FIOPIN;

	case 2:

		return LPC_GPIO2->FIOPIN;

	case 3:

		return LPC_GPIO3->FIOPIN;

	case 4:

		return LPC_GPIO4->FIOPIN;

	default:
		return 0;
	}

}
*/
/*
void gpiowr8_2(int port, int numbyte, int data){
	//ver página 138, 150 e mudar a função

	//Não existem mais do que 4 bytes
	if(numbyte>3) numbyte=3;
	//Mascara de 8 bits
	data = data & 0x000000FF;
	data = data << numbyte * 8;

	int datard = gpiord32_latch(port);

	datard = datard || data;

	gpiowr32(port, datard);

}
*/
/*
void gpiowr16_2(int port, int numword, int data){
	//Não existem mais do que 2 palavras de 16bits
	if(numword>1) numword=1;
	//Mascara de 16 bits
	data = data & 0x0000FFFF;
	data = data << numword * 16;

	int datard = gpiord32_latch(port);

	datard = datard || data;

	gpiowr32(port, datard);
}

*/

/*
void gpiowrbit_2(int port, int portbit, bool portdata){

//Nº porto
//Nº bit
//set ou clear
	int data = gpiord32_latch(port);

	if(portdata){
		data |= 1<<portbit;
	}else{
		data &= ~(1<<portbit);
	}
	gpiowr32(port, data);
}
*/

//x nanos
/*
void delay(int time){
	for(int i=0; i<time;i++) ;
}
*/

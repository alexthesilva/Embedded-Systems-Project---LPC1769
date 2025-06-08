#include "display.h"

#include "fgpio.h"
#include <stdarg.h>
#include <stdio.h>
#include <timers.h>

void niblle_write(int rs, int data){
	/*
	* Apesar da validação dos dados ser feita na transição descendente do enable
	* eles podem ser colocados no barramento antes do tempo
	* Os bits de entrada são os menos significativos
	*/
	/*
	data = data << 4;				//Deslocamento dos bits menos significativos para a esquerda
	gpiowr8(DATA_PORT, DATA_BYTE, data);	//Funciona, mas vai ser mudada
	*/

	data &= 0x0000000F;
	gpiowrbit(DB7_PORT, DB7_BIT, (data & 0b1000)!=0);	//DB7
	gpiowrbit(DB6_PORT, DB6_BIT, (data & 0b0100)!=0);	//DB6
	gpiowrbit(DB5_PORT, DB5_BIT, (data & 0b0010)!=0);	//DB5
	gpiowrbit(DB4_PORT, DB4_BIT, (data & 0b0001)!=0);	//DB4


	gpiowrbit(RS_PORT, RS_BIT, rs);		//Seleciona RS
	WAIT_Stopwatch (1);					//espera 1 micro segundo
	gpiowrbit(E_PORT, E_BIT, true);		//Liga Enable
	WAIT_Stopwatch (1);					//espera 1 micro segundo
	gpiowrbit(E_PORT, E_BIT, false);	//Desliga Enable
	WAIT_Stopwatch (1);					//espera 1 micro segundo
}

void byte_write(int rs, int data){
	niblle_write(rs, data>>4); 			//Escreve os 4 bits mais significativos
	niblle_write(rs, data); 			//Escreve os 4 bits menos significativos

}

void cmd_write(int data){
	byte_write(RS_COM, data);
	WAIT_Stopwatch (1700);				//espera mais do que 1,64 mili segundos

}

void data_write(int data){
	byte_write(RS_DAT, data);
	WAIT_Stopwatch (1700);				//espera mais do que 1,64 mili segundos

}

void LCDText_Init(void){
	//PINO RS
	iotype(RS_PORT, RS_BIT, GPIO);
	gpiodir(RS_PORT, RS_BIT, OUT);
	//PINO E
	iotype(E_PORT, E_BIT, GPIO);
	gpiodir(E_PORT, E_BIT, OUT);
	//Dados
	iotype(DB7_PORT, DB7_BIT, GPIO);
	gpiodir(DB7_PORT, DB7_BIT, OUT);
	iotype(DB6_PORT, DB6_BIT, GPIO);
	gpiodir(DB6_PORT, DB6_BIT, OUT);
	iotype(DB5_PORT, DB5_BIT, GPIO);
	gpiodir(DB5_PORT, DB5_BIT, OUT);
	iotype(DB4_PORT, DB4_BIT, GPIO);
	gpiodir(DB4_PORT, DB4_BIT, OUT);

	WAIT_Stopwatch (16000);			//Espera mais do que 15 mili segundos
	//00110000=0x30
	niblle_write(RS_COM, LCD_Reset);
	WAIT_Stopwatch (4200);			//Espera mais do que 4,1 mili segundos
	niblle_write(RS_COM, LCD_Reset);
	WAIT_Stopwatch (200);			//Espera 0,2 mili segundos
	niblle_write(RS_COM, LCD_Reset);
	WAIT_Stopwatch (200);			//Espera 0,2 mili segundos
	byte_write(RS_COM, LCD_Set4bit);
	WAIT_Stopwatch (50);			//Espera 50 micro segundos
	byte_write(RS_COM, LCD_EntryMode);
	WAIT_Stopwatch (50);			//Espera 50 micro segundos
	LCDText_Clear ();
	//Faz wait dentro da função Clear
	byte_write(RS_COM, LCD_DisplayOn);
	WAIT_Stopwatch (50);			//Espera 50 micro segundos
}

void LCDText_WriteChar(char ch){
	int dados= (int) ch;
	data_write( dados);

}

void LCDText_WriteString ( char * str ){

	for (int i=0;str[i]!='\0';i++){
		LCDText_WriteChar(str[i]);
	}
}

void LCDText_SetCursor ( int row , int column ) {
	int posicao;
	posicao=column-1+(row-1)*LCD_LineTwo;
	posicao |= LCD_SetCursor;
	cmd_write(posicao);
	//WAIT_Stopwatch (1700);			//Espera 1,7 mili segundos
}

void LCDText_Home(void){
	cmd_write(LCD_Home);
	//WAIT_Stopwatch (1700);			//Espera 1,7 mili segundos

}
void LCDText_Clear (void ){
	cmd_write(LCD_Clear);
	//WAIT_Stopwatch (1700);			//Espera 1,7 mili segundos
}

/*
void LCDText_Printf (char *fmt , ... ){
	//va_list ap;
	char *p;
	char buffer[20];
	buffer=sprintf(p);
	LCDText_WriteString ( buffer );
}*/

//
void LCDText_Printf (char *fmt , ... ){
	va_list ap;
	va_start(ap, fmt);
	char buffer[20];
	vsprintf(buffer, fmt, ap);
	va_end(ap);
	LCDText_WriteString ( buffer );
}

//Versão aprendida em PG2
/*
void LCDText_Printf (char *fmt , ... ){
	va_list ap;
	char *p, *sval;

	int ival;

	double dval;
	char buffer[20];

	va_start(ap, fmt);

	for(p = fmt; *p; p++) {
		if(*p != '%') {
			//LCDText_WriteString ( p );
			LCDText_WriteChar(*p);
			continue;
		}
		switch(*++p){
			case 'd':
				ival = va_arg(ap, int);
				//printf("%d", ival);
				//LCDText_WriteString ( itoa(ival) );

				sprintf(buffer,"%d", ival);
				LCDText_WriteString (buffer);
				break;

			case 'f':
				dval = va_arg(ap, double);
				//printf("%d", ival);
				//LCDText_WriteString ( itoa(ival) );

				sprintf(buffer,"%f", dval);
				LCDText_WriteString (buffer);
				break;

			case 's':
				for(sval=va_arg(ap, char *); *sval; sval++)
					LCDText_WriteChar(*sval);

				break;

			default:
				LCDText_WriteChar(*p);
				break;
		}

	}
}*/


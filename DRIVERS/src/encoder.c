#include "encoder.h"
#include "fgpio.h"
#include "timers.h"
#include "led.h"

//Switch do encoder
#define SW_BIT 1
#define SW_PORT 2
//DT do encoder
#define DT_BIT 3
#define DT_PORT 2
//CLK do encoder
#define CLK_BIT 2
#define CLK_PORT 2

#define TEMPO_BOTAO 60		//Número de interrupções de atraso do botão para 200Hz -> 5ms * 60 = 0,6seg

static volatile int rotacao;	//Contém o valor e a direção das rotações do encoder
static volatile int p_button;	//Estado do botao
static volatile unsigned int last_state;
static volatile unsigned int state;
static volatile ENCODER_ButtonValueType state_button = BUTTON_NOTPRESSED;
static volatile ENCODER_ButtonValueType state_button_utilizador = BUTTON_NOTPRESSED;
static volatile bool button;
static volatile int  button_time=0;

void ENCODER_Init ( int repet) {
	//Cofigurar o Repetitive Timer
	Rep_timer_init(repet);

	//PINO Switch
	iotype(SW_PORT, SW_BIT, GPIO);
	gpiodir(SW_PORT, SW_BIT, IN);
	//PINO CLK
	iotype(CLK_PORT, CLK_BIT, GPIO);
	gpiodir(CLK_PORT, CLK_BIT, IN);
	//PINO DT
	iotype(DT_PORT, DT_BIT, GPIO);
	gpiodir(DT_PORT, DT_BIT, IN);
}

unsigned int state_encoder(void){
	//Código do encoder

	bool b = gpiordpin(CLK_PORT, CLK_BIT);
	bool a = gpiordpin(DT_PORT, DT_BIT);
	return (2*a+b);

}

bool button_pressed(void){
	return !gpiordpin(SW_PORT, SW_BIT); //inverte o estado do botão
}

void RIT_IRQHandler(void){
	button_time++;

	switch(last_state){
		case 0:	//00
			if(state_encoder()!=last_state){
				if (state_encoder()==1){
					rotacao=1;
				}

				last_state=state_encoder();
			}
			break;

		case 1:	//01
			if(state_encoder()!=last_state){
				if (state_encoder()==0){
					rotacao=-1;
				}

				last_state=state_encoder();
			}
			break;

		case 2:	//10
			if(state_encoder()!=last_state){
				if (state_encoder()==3){
					rotacao=-1;
				}

				last_state=state_encoder();
			}
			break;

		case 3:	//11
			if(state_encoder()!=last_state){
				if (state_encoder()==2){
					rotacao=1;
				}

				last_state=state_encoder();
			}
			break;

		default:
			break;
	}

	//Código do Switch

	switch(state_button){
		case BUTTON_NOTPRESSED:
			if (button_pressed()){
				button_time=0;
				state_button = BUTTON_PRESSED;
				//state_button_utilizador = BUTTON_PRESSED;
			}
			break;

		case BUTTON_PRESSED:
			if (!button_pressed()){
				state_button = BUTTON_CLICKED;
			}
			if(button_time >= TEMPO_BOTAO){
				state_button = BUTTON_HELD;
				state_button_utilizador = BUTTON_HELD;
			}
			break;

		case BUTTON_HELD:
			if (!button_pressed()){
				button_time=0;
				state_button = BUTTON_NOTPRESSED;
				state_button_utilizador = BUTTON_NOTPRESSED;
			}
			break;

		case BUTTON_RELEASE:
			state_button = BUTTON_NOTPRESSED;
			break;

		case BUTTON_CLICKED:
			if (button_time >= TEMPO_BOTAO){
				state_button = BUTTON_NOTPRESSED;
				state_button_utilizador = BUTTON_CLICKED;
			}
			if (button_pressed()){

				state_button = BUTTON_DCLICKED;
			}
			break;

		case BUTTON_DCLICKED:
			button_time=0;
			if (!button_pressed()){
				state_button = BUTTON_NOTPRESSED;
				state_button_utilizador = BUTTON_DCLICKED;
			}
			break;

		default:
			break;
		}

	RIT_IRQACK();
}

/*
 switch(state_button){
		case BUTTON_NOTPRESSED:
			if (button){
				button_time=0;
				state_button = BUTTON_PRESSED;
			}
			break;

		case BUTTON_PRESSED:
			if (!button) state_button = BUTTON_CLICKED;

			if (button_time >= TEMPO_BOTAO){
				state_button = BUTTON_HELD;
			}
			break;

		case BUTTON_HELD:
			if (!button){
				button_time=0;
				state_button = BUTTON_RELEASE;
			}
			break;

		case BUTTON_RELEASE:
			if (button_time >= TEMPO_BOTAO){
				state_button = BUTTON_NOTPRESSED;
			}
			break;

		case BUTTON_CLICKED:
			if (button_time >= TEMPO_BOTAO){
				state_button = BUTTON_NOTPRESSED;
			}
			if (button){
				button_time=0;
				state_button = BUTTON_DCLICKED;
			}
			break;

		case BUTTON_DCLICKED:
			if (button_time >= TEMPO_BOTAO){
				state_button = BUTTON_NOTPRESSED;
			}
			break;

		default:
			break;
		}
 */


int ENCODER_GetValue(){
	int temp=rotacao;
	rotacao=0;
	return temp;
}

ENCODER_ButtonValueType ENCODER_GetButton(){
	//O botão utiliza pull-up e é ativado com zero
	//return !gpiordpin(SW_PORT, SW_BIT); //inverte o estado do botão

	ENCODER_ButtonValueType tmp = state_button_utilizador;
	if(state_button_utilizador != BUTTON_HELD){
		state_button_utilizador = BUTTON_NOTPRESSED;
	}


	return tmp;

}

/*
ENCODER_ButtonValueType ENCODER_GetButton1(){
	//O botão utiliza pull-up e é ativado com zero
	//return !gpiordpin(SW_PORT, SW_BIT); //inverte o estado do botão

	return state_button_utilizador;

}
*/


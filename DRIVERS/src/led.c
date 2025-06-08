#include "fgpio.h"

#include "led.h"



void LED_Init ( bool state){

	iotype(LED_PORT, LED_PIN, GPIO);
	gpiodir(LED_PORT, LED_PIN, OUT);

	gpiowrbit(LED_PORT, LED_PIN, state);

}

bool LED_GetState ( void){
	return gpiordpin(LED_PORT, LED_PIN);
}

void LED_On( void){
	gpiowrbit(LED_PORT, LED_PIN, SET);
}

void LED_Off (void){
	gpiowrbit(LED_PORT, LED_PIN, CLR);
}

void LED_Toggle (void){
	/*
	if(gpiordlatch(0, 22))
		gpiowrbit(0, 22, CLR);
	else
		gpiowrbit(0, 22, SET);
	*/
	//gpiowrbit(0, 22, !gpiordlatch(0, 22));

	gpiotoggle(LED_PORT, LED_PIN);

}

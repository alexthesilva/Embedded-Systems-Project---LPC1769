#include <timers.h>
#include "fgpio.h"

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

void RIT_IRQACK(void){

	//Control register Interrupt página 513
	LPC_RIT->RICTRL |= 1<<RITINT; 	//bit 0 = 1, a escrita de 1 apaga o bit
}

//Repetitive Timer	//página 512
void Rep_timer_init(int repet){
	LPC_SC->PCONP |= 1<<PCRIT;			//página 65
	LPC_SC->PCLKSEL1 |= 1 << CLKRIT;	//CLK = 100MHz

	LPC_RIT->RICTRL &= ~(1<<RITEN); 	//Desligar o enable para poder atualizar valores
	LPC_RIT->RICOUNTER = 0;

	//RI Valor de comparação página 512 e 514
	LPC_RIT->RICOMPVAL = SystemCoreClock/repet-1;	//Valor do divisor

	//RI mask register -> RI mask, para comparar
	LPC_RIT->RIMASK = 0x00000000;		//pág 514

	//RI Registo de controlo página 513
	LPC_RIT->RICTRL |= 1<<RITENCLR; 	//bit 1 = 1 => apaga o contador quando  é igual a RICOMPVAL
	LPC_RIT->RICTRL |= 1<<RITEN; 		//bit 3 = 1 => Timer enable

	//RI TINT interrupt
	NVIC_EnableIRQ(RIT_IRQn);
}


//System Tick
int WAIT_Init ( void) {
	SystemCoreClockUpdate();
	//SYSTICK_FREQ contém o valor do divisor de frequência
	if (SysTick_Config(SYSTICK_FREQ) == 1) return -1;

	return 0;
}

static volatile uint32_t __ms;
static volatile uint32_t __micros;

void SysTick_Handler(void){
		__ms++;
}

void WAIT_Milliseconds ( uint32_t millis ){
	uint32_t start = __ms;
	while ((__ms - start) < millis){
		__WFI();
	}
}

uint32_t WAIT_GetElapsedMillis ( uint32_t start ){

	return __ms-start;

}

//Timer0
void WAIT_StopwatchInit ( void){
	LPC_SC->PCONP |= (1 << TIMER0_BIT_POS);     // bit 1 PCTIM0 power/clock control bit (pag 65)
	LPC_SC->PCLKSEL0 |= 1 << CLK0;				//Clock for timer = CCLK  (pag 58 e 59)
	//CCLK = 100MHz								//bit 3 e 2 da pag 58
	//LPC_TIM0->MR0 = 1;

	//LPC_TIM0->PR = 99;


	LPC_TIM0->PR = PRESCALER0-1;				// pre-scaller com resolução de 1 micro seg (pag 503)

	LPC_TIM0->MCR |= 1 << MR0I;      			// Interrupt on MR0 (pag 507)
	LPC_TIM0->MCR |= 1 << MR0S;      			// STOP on MR0.

	//LPC_TIM0->MCR = (1<<MR0I)|(1<<MR0R);

	LPC_TIM0->TCR |= 1 << COUNTER_RESET;      	// Counter reset (pag 505)
	LPC_TIM0->TCR &= ~(1 << COUNTER_RESET);   	// stop reset the timer.

	//LPC_TIM0->TCR |= 1 << COUNTER_ENABLE;		// Enable timer (pag 505)

	//NVIC_EnableIRQ(TIMER0_IRQn);  				// Enable timer interrupt (pag 79)

	}

void WAIT_Stopwatch ( uint32_t waitUs ){
	LPC_TIM0->MR0 = waitUs;      				// Match Registor , multiplos de 1 micro seg  (pag 503)
	LPC_TIM0->TCR |= 1 << COUNTER_RESET;      	// Counter reset (pag 505)
	LPC_TIM0->TCR &= ~(1 << COUNTER_RESET);   	// stop reset the timer.
	LPC_TIM0->TCR |= 1 << COUNTER_ENABLE;		// Enable timer (pag 505)

	while (!(LPC_TIM0->IR & 1 << MR0I));

	LPC_TIM0->IR|= 1 << MR0I;
}

void TIMER0_IRQHandler (void)
{
	//Não utilizado
	//gpiowrbit(2, 5, CLR);
	//gpiowrbit(0, 22, CLR);
	//LPC_TIM0->IR|= 1 << MR0I;


	//unsigned int ir;
	//ir = LPC_TIM0->IR;
	//LPC_TIM0->IR = ir;

    //if((ir & 0x01) == 0x01) 	// if MR0 interrupt (pag 504)
    //{
		//__micros++;

        //Apenas para teste, toggle LED
    	 // gpiotoggle(0, 22);
    	//gpiowrbit(0, 22, CLR);
    //}

}

/**
 * @file timers.h
 * @brief Contém todas as funções relacionadas com os TIMER do microcontrolador
 * @version 1
 * @author Grupo 2
 */
#ifndef TIMERS_H
#define TIMERS_H



#include <stdint.h>

#define SYSTICK_FREQ (SystemCoreClock / 1000)	//100MHz/1000 = 100000 (valor da divisão)
#define PRESCALER0 (SystemCoreClock / 1000000)	//100MHz/1000000 = 100 (valor da divisão)
//#define PRESCAL_RIT (SystemCoreClock / 100)	    //Para 100Hz

#define CLK0 2		//bit 2 e 3
#define TIMER0_BIT_POS 1
#define MR0I 0
#define MR0R 1
#define MR0S 2
#define COUNTER_ENABLE 0
#define COUNTER_RESET 1
//RIT
//#define RITINT 0
#define RITENCLR 1	//página 513
#define RITEN 3		//página 513
#define PCRIT 16
#define CLKRIT 26	//bit 26 e 27

#define RITINT 0

/**
 * Apaga o bit IRQ do RIT
 * @param : não tem parâmetros de entrada
 */
void RIT_IRQACK(void);

/**
 * Initializa o System repetitive timer
 * @param : não tem parâmetros de entrada
 */
void Rep_timer_init(int repet);

/**
 * Initializa o System tick timer
 * O timer vai gerar um pedido de interrupção a cada milisegundo
 * O pedido de interrupção irá executar o ISR SysTick_Handler
 * @param : não tem parâmetros de entrada
 */
int WAIT_Init ( void) ;

/**
 * Esta função bloqueia durante o valor entrado como parâmetro em milisegundos
 * @param milis: Entra o valor em mili-segundos
 */
void WAIT_Milliseconds ( uint32_t millis ) ;

/**
 * A função retorna a diferença entre o valor colocado como parâmetro e o tempo atual.
 * @param start: valor inicial para contar o tempo que passou
 */

uint32_t WAIT_GetElapsedMillis ( uint32_t start ) ;


/**
 * Não tem parâmetros de entrada nem de saída
 * Initializa o TIMER0 com resolução de 1 micro segundo
 * O TIMER0 é configurado para fazer stop quando faz match
 * @param :não tem parâmetros de entrada
 */
void WAIT_StopwatchInit ( void) ;

/**
 * Este valor é colocado no MR0
 * O contador inicia a contagem e a funçao fica bloqueada até atingir o valor inserido
 * @param waitUs: Entra com o valor em micro segundos
 */
void WAIT_Stopwatch ( uint32_t waitUs ) ;


//não usado
void TIMER0_IRQHandler (void);

#endif

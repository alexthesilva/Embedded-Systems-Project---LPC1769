/**
 * @file rtchall.h
 * @brief Contém todas as funções relacionadas com o encoder rotativo
 * @version 1
 * @author Grupo 2
 */

#ifndef RTCHALL_H
#define RTCHALL_H



#include <time.h>
#define SBIT_CTCRST 1
#define SBIT_CCALEN 4
#define SBIT_CLKEN 0
#define PCRTC 9		//página 65

/**
 * Liga o relógio.
 * @param : sem parâmetros.
 */
void RTC_Start(void);
/**
 * Desliga o relógio.
 * @param : sem parâmetros.
 */
void RTC_Stop(void);

/**
 * Faz a iniciação do RTC.
 * O RTC é iniciado com o valor do parâmetro seconds, que representa
 * @param seconds: os segundos desde 00:00:00 UTC de 1 janeiro 1970.
 */
void RTC_HallInit (void );

/**
 * Devolve em dateTime o valor corrente e do RTC.
 * O dia da semana varia entre 0 e 6
 * O mês varia entre 0 e 11
 * O valor do ano a partir de 1900
 * @param dateTime: endereço da estrutura tipo tm
 */
void RTC_HallGetValue ( struct tm *dateTime );

/**
 * Realiza a atualização do RTC com os valores do parâmetro dateTime.
 * O dia da semana varia entre 0 e 6
 * O mês varia entre 0 e 11
 * O valor do ano a partir de 1900
 * @param dateTime: endereço da estrutura tipo tm
 */
void RTC_HallSetValue ( struct tm *dateTime );

#endif

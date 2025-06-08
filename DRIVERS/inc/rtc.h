/**
 * @file rtc.h
 * @brief Contém todas as funções relacionadas com o detetor de movimento
 * @version 1
 * @author Grupo 2
 */
#ifndef RTC_H
#define RTC_H

#include <time.h>
#include "rtchall.h"

/**
 * Faz a iniciação do RTC.
 * O RTC é iniciado com o valor do parâmetro seconds, que representa
 * @param seconds: os segundos desde 00:00:00 UTC de 1 janeiro 1970.
 */
void RTC_Init ( time_t seconds ) ;

/**
 * Devolve em dateTime o valor corrente e do RTC.
 * O dia da semana varia entre 0 e 6
 * O mês varia entre 0 e 11
 * O valor do ano a partir de 1900
 * @param dateTime: endereço da estrutura tipo tm
 */
void RTC_GetValue ( struct tm *dateTime ) ;

/**
 * Realiza a atualização do RTC com os valores do parâmetro dateTime.
 * O dia da semana varia entre 0 e 6
 * O mês varia entre 0 e 11
 * O valor do ano a partir de 1900
 * @param dateTime: endereço da estrutura tipo tm
 */
void RTC_SetValue ( struct tm *dateTime ) ;

/**
 * Realiza a atualização do RTC com o valor do parâmetro seconds,
 * @param seconds: segundos desde 00:00:00 UTC de 1 janeiro 1970.
 */
void RTC_SetSeconds ( time_t seconds ) ;

/**
 * Retorna o valor corrente do RTC, em segundos
 * desde 00:00:00 UTC de 1 janeiro 1970.
 * @param: sem parâmetros de entrada
 */
time_t RTC_GetSeconds ( void) ;


#endif

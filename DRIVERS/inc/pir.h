/**
 * @file pir.h
 * @brief Contém todas as funções relacionadas com o detetor de movimento
 * @version 1
 * @author Grupo 2
 */
#ifndef PIR_H
#define PIR_H

#include "stdbool.h"

#define PIR_PIN 21
#define PIR_PORT 0

/**
 * Configura o pino do PIR como GPIO entrada
 * @param : Não tem parametros de entrada
 */
void PIR_Init ( void );

/**
 * Faz a leitura do pino de entrada ligada ao PIR
 * @param : Não tem parametros de entrada
 */
bool PIR_GetPresence ( void );

#endif

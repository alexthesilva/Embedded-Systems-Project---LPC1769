/**
 * @file led.h
 * @brief Contém todas as funções relacionadas com o built-in LED
 * @version 1
 * @author Grupo 2
 */
#ifndef LED_H
#define LED_H

#include <stdbool.h>

#define LED_PIN 22
#define LED_PORT 0

/**
 * Initializa o pino do Built-in LED como saída GPIO
 * e define o estado inicial do LED passado como parâmetro
 * @param state: state contém o estado inicial do built-in LED
 */
void LED_Init ( bool state);

/**
 * Lê o estado do Built-in LEd e retorna o seu valor lógico
 * @param : Não tem parametros de entrada
 */
bool LED_GetState ( void);

/**
 * Liga o Built-in LED.
 * @param : Não tem parametros de entrada
 */
void LED_On( void);

/**
 * Desliga o Built-in LED.
 * @param : Não tem parametros de entrada
 */
void LED_Off (void);

/**
 * Inverte o estado do Built-in LED.
 * @param : Não tem parametros de entrada
 */
void LED_Toggle (void);

#endif


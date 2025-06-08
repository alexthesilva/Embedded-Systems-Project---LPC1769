/**
 * @file fgpio.h
 * @brief Contém todas as funções relacionadas com os pinos do micro-controlador
 * @version 1
 * @author Grupo 2
 */
#ifndef FGPIO_H
#define FGPIO_H



#include "stdbool.h"
#include "stdint.h"

#define	OUT	1
#define IN 0
#define	SET	1
#define CLR 0
//GPIO mode
#define GPIO 0
#define FIRST 1
#define SECOND 2
#define THIRD 3
//Pull-up/down
#define UP 0
#define REPEAT 1
#define NONE 2
#define DOWN 3


void delay(int time);

/**
 * Activa o pino com SET e desativa o pino com CLR
 * Não devolve nenhum parâmetro
 * @param port: Número do porto
 * @param portbit: Número do bit dentro do porto
 * @param portdata: valor do bit a ser escrito
 */
void gpiowrbit(int port, int portbit, bool portdata);

/**
 * Entra com os parâmetros nº do port e o nº do bit
 * Semelhante  ou gpiordlatch, mas retorna o valor lógico do pino indicado
 * @param port: Número do porto
 * @param portbit: Número do bit dentro do porto
 */
bool gpiordpin(int port, int portbit);

/**
 * Semelhante  ou gpiordlatch, mas retorna o valor lógico do pino indicado
 * @param port: Número do porto
 * @param portbit: Número do bit dentro do porto
 */
bool gpiordlatch(int port, int portbit);

/**
 * Função para definir a direção do pino.
 * A direção do pino é indicada com OUT para saída e IN para entrada
 * @param port: Número do porto
 * @param portbit: Número do bit dentro do porto
 * @param portdata: valor do bit a ser escrito
 */
void gpiodir(int port, int portbit, int dir);

/**
 * Define o tipo do pino
 * GPIO, FIRST function, SECOND function, THIRD function
 * Não devolve nenhum parâmetro
 * @param port: Número do porto
 * @param portbit: Número do bit dentro do porto
 * @param portdata: valor do bit a ser escrito
 */
void iotype(int port, int portbit, int type);

/**
 * Escreve os oito bits de dados no port e no byte especificado
 * Não devolve nenhum parâmetro
 * @param port: Número do porto
 * @param portbit: Número do bit dentro do porto
 */
void gpiowr8(int port, int numbyte, int data);


/**
 * Escreve os dezasseis bits de dados no port e na word especificado
 * Não devolve nenhum parâmetro
 * @param port: Número do porto
 * @@param numword: Número da word (0-bit 0 a 7, 1-bit 8 a 15)
 * @param portbit: Número do bit dentro do porto
 */
void gpiowr16(int port, int numword, int data);

/**
 * Entra com os parametros número de port (0 a 4)
 * Escreve 32 bits de dados colocados em data
 * Não devolve nenhum parâmetro
 * @param port: Número do porto
 * @param portbit: Número do bit dentro do porto
 */
void gpiowr32(int port, int data);

/**
 * Lê os 32 bits de dados disponiveis na saída de cada latch do port
 * Devolve o valor de 32 bits
 * @param port: Número do porto
 *
 */

uint32_t gpiord32_gpio(int port);

/**
 * Define o tipo de Pull-up ou Pull-down
 * UP para pull-ip, REPEAT para repeater mode
 * NONE para desativado, DOWN para pull-down
 * Não devolve nenhum parâmetro
 * @param port: Número do porto
 * @param portbit: Número do bit dentro do porto
 * @param portdata: valor do bit a ser escrito
 */
void iopullup(int port, int portbit, int type);

/**
 * Activa o pino se estiver desativado
 * Desativa o pino se estiver ativado
 * Não devolve nenhum parâmetro
 * @param port: Número do porto
 * @param portbit: Número do bit dentro do porto
 */
void gpiotoggle(int port, int portbit);

#endif

/**
 * @file encoder.h
 * @brief Contém todas as funções relacionadas com o encoder rotativo
 * @version 1
 * @author Grupo 2
 */
#ifndef ENCODER_H
#define ENCODER_H


typedef enum ButtonEnum {
	BUTTON_NOTPRESSED, 		// 0 Nao pressionado
	BUTTON_PRESSED, 		// 1 Pressionado ( transicao de nao pressionado para pressionado )
	BUTTON_HELD, 			// 2 Mantem−se pressionado entre chamadas consecutivas
	BUTTON_RELEASE, 		// 3 Libertado ( transicao de pressionado para nao pressionado )
	BUTTON_CLICKED, 		// 4 Pressionado e libertado num intervalo de tempo curto
	BUTTON_DCLICKED 		// 5 Pressionado e libertado num intervalo de tempo curto duas vezes
} ENCODER_ButtonValueType ;


/**
 * Não tem de saída
 * Inicializa o Repetitive Timer com resolução
 * Inicializa o GPIO do encoder
 * @param repet: Volor da frequência do timer indicando o número de interrupções por seg
 */
void ENCODER_Init ( int repet) ;

/**
 * Retorna o estado do interruptor
 * BUTTON_NOTPRESSED, 	0 Nao pressionado
 * BUTTON_PRESSED, 		1 Pressionado ( transicao de nao pressionado para pressionado )
 * BUTTON_HELD, 		2 Mantem−se pressionado entre chamadas consecutivas
 * BUTTON_RELEASE, 		3 Libertado ( transicao de pressionado para nao pressionado )
 * BUTTON_CLICKED, 		4 Pressionado e libertado num intervalo de tempo curto
 * BUTTON_DCLICKED 		5 Pressionado e libertado num intervalo de tempo curto duas vezes
 * @param :não tem parâmetros
 */
ENCODER_ButtonValueType ENCODER_GetButton(void);
//ENCODER_ButtonValueType ENCODER_GetButton1(void);

/**
 * Retorna o número e a direção das voltas
 * Direita maior do que 0
 * Esquerda menor do que 0
 * @param :não tem parâmetros
 */
int ENCODER_GetValue(void);

#endif

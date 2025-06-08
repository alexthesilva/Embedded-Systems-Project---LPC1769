/**
 * @file display.h
 * @brief Contém todas as funções relacionadas com o display LCD
 * @version 1
 * @author Grupo 2
 */

#ifndef DISPLAY_H
#define DISPLAY_H

//RS do display
#define RS_BIT 12
#define RS_PORT 2
//Enable do display
#define E_BIT 11
#define E_PORT 2
//DB7
#define DB7_BIT 7
#define DB7_PORT 2
//DB6
#define DB6_BIT 6
#define DB6_PORT 2
//DB5
#define DB5_BIT 5
#define DB5_PORT 2
//DB4
#define DB4_BIT 4
#define DB4_PORT 2
//DATA
//#define DATA_PORT 2
//#define DATA_BYTE 0

#define RS_COM 0
#define RS_DAT 1

//Comandos
#define LCD_Clear           0b00000001          // todos os caracteres ASCII 'space'
#define LCD_Home            0b00000010          // põe o cursor no inicio da primeira linha
#define LCD_EntryMode       0b00000110          // desloca o cursor da esquerda para a direita na escrita
#define LCD_DisplayOff      0b00001000          // desliga o display
#define LCD_DisplayOn       0b00001100          // display on, cursor off, não pisca o caracter
#define LCD_Reset   		0b0011		        // Faz reset ao LCD
#define LCD_Set4bit 		0b00100000         	// 4-bits data
#define LCD_SetCursor       0b10000000          // define a posição do cursor
#define LCD_LineOne     	0x00                // inicio da linha 1
#define LCD_LineTwo     	0x40                // inicio da linha 2

/**
 * Inicializa os pinos para o display
 * Inicializa o display
 * @param : Não tem parâmetros de entrada
 */
void LCDText_Init(void);

/**
 * Escreve um caracter na posição atual do cursor e desloca o cursor uma posição
 *@param ch: Entra um caracter
 */
void LCDText_WriteChar(char ch);

/**
 * Escreve uma string no display
 * @param str: Contém o endereço da string a ser escrita
 */
void LCDText_WriteString ( char * str );

/**
 * Define a posição do cursor
 * @param row:define o número da linha 1 ou 2
 * @param column: define o número da coluna 1 a 16
 */
void LCDText_SetCursor ( int row , int column ) ;

/**
 * Apaga o texto do display
 * @param : Não tem parâmetros de entrada
 */
void LCDText_Clear (void );

/**
 * Põe o cursor no inicio da primeira linha
 * @param : Não tem parâmetros de entrada
 */
void LCDText_Home(void);

/**
 * Função semelhante ao printf
 * O texto é enviado para o LCD
 * @param: Igual ao printf
 */
void LCDText_Printf (char *fmt , ... );

/**
 * Escreve 4 bits no barramento do display
 * Os dados entram pelos bits 3..0
 * @param data: nibble de dados
 * @param rs:0 - comando, 1 - dados
 */
void niblle_write(int rs, int data);

/**
 * Escreve 8 bits no display
 * @param rs: Define se é comando (RS=0) ou dados (RS=1)
 * @param data: Dados de 8 bits a escrever no display
 */
void byte_write(int rs, int data);

/**
 * Envia um comando ao display
 * @param data: Dados referentes ao comando
 */
void cmd_write(int data);

/**
 * Envia dados ao display
 * @param data: Dados referentes aos caracteres
 */
void data_write(int data);

#endif

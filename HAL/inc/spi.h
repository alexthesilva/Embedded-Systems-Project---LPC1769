/**
 * @file spi.h
 * @brief Contém todas as funções relacionadas com o SPI
 * @version 1
 * @author Grupo 2
 */

#ifndef SPI_H_
#define SPI_H_


#define PCSPI 8
#define PCLK_SPI 16
#define BitEnable 2
#define BITS 8
#define MSTR 5
#define CPHA 3
#define SPIE 7
#define SPIF 7

/**
 *  Faz a iniciacao do controlador e configura os respetivos pinos .
 * @param : Não tem parametros de entrada
 */
void SPI_Init ( void) ;

/**
*  Configura o ritmo de envio / rececao , o numero de bits de dados e o modo ( 0 , 1 , 2 ou 3) .
* @param frequency: frequência de comunicação em Hz
* @param data: bitData dados a enviar
* @param data: mode 0, 1, 2, 3
*/
void SPI_Config(int frequency, int bitData , int mode);

/**
*  Realiza uma transferencia, envia uma palavra e devolve a palavra recebida.
* @param value: valor de 8 bits a enviar
*/
unsigned short SPI_Transfere(unsigned short value );

/**
*  Realiza uma transferencia . Retorna sucesso ou erro na transferencia , em que o parametro lenght indica no numero de palavras a transmitir e /ou receber .
* @param txbuffer: endereço do buffer com os dados a enviar
* @param rxbuffer: endereço do buffer com os dados a receber
* @param lenght: Tamanho dos buffers de transmissão e receção. devem ter o mesmo tamanho.
*/
int SPI_Transfer (unsigned short * txBuffer , unsigned short * rxBuffer , int lenght ) ;


#endif /* SPI_H_ */

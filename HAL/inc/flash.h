/**
 * @file flash.h
 * @brief Contém as funções relacionadas com a memória FLASH do LPC1769
 * @version 1
 * @author Grupo 2
 */

#ifndef FLASH_H
#define FLASH_H

/**
 * Prepara o sector para ser escrito ou apagado.
 * @param setor: introduzir o número do setor
 */
unsigned int FLASH_PrepareSector (unsigned int sector);

/**
 * Apaga o conteudo de um sector.
 * @param setor: introduzir o número do setor
 */
unsigned int FLASH_EraseSector (unsigned int sector) ;

/**
* Escreve o bloco de dados referenciado por srcAddr , de dimensao size bytes , no endereco da Flash
* referenciado por dstAddr .
* @param dstAddr: Endereço do buffer de destino
* @param srcAddr: Endereço do buffer fonte
* @param size: o tamanho do buffer
*/
unsigned int FLASH_WriteData ( void *dstAddr , void * srcAddr , unsigned int size ) ;

/**
*  Compara o conte ´udo do bloco de dados referenciado por srcAddr , de dimens ˜ao s i z e bytes , com o conte ´udo do
* bloco de dados referenciado por dstAddr .
* @param dstAddr: Endereço do buffer de destino
* @param srcAddr: Endereço do buffer fonte
* @param size: o tamanho do buffer
*/
unsigned int FLASH_VerifyData ( void *dstAddr , void * srcAddr , unsigned int size ) ;


#endif

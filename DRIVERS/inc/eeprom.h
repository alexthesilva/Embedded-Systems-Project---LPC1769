/**
 * @file eeprom.h
 * @brief Contém as funções de acesso à EEPROM
 * @version 1
 * @author Grupo 2
 */

#ifndef EEPROM_H_
#define EEPROM_H_

#define WREN 	0x06		//Enable Write Operations
#define WRDI 	0x04		//Disable Write Operations
#define RDSR 	0x05		//Read Status Register
#define WRSR 	0x01		//Write Status Register
#define READ 	0x03		//Read Data from Memory
#define WRITE 	0x02		//Write data to Memory

#define ASSINATURA 0x55
#define ASS_ADDR 0
#define LUZ 1				//Endereço da intensidade da luz
#define N_REG 3				//Endereço do número de registos
#define REG_SIZE 8
#define DEFAULT_LIGHT 90

/**
*  Verifica se assinatura está correta
*  Se não estiver correta inicia a eeprom
*  @param  Não tem nenhum parêmetro de entrada
*/
void eeprominit();

/**
* Escreve o byte value no conteudo do endereco indicado no parametro address . A funcao retorna 0 se
*  escreveu com sucesso ou −1 se ocorreu um erro .
*  @param value: Dados a serem enviados
*  @param address: endereço da EEPROM
*/
int CAT25128_WriteByte (unsigned char value , unsigned int address );

/**
*  Lê o byte que está armazenado no conteudo do endereco indicado no parametro address para o endereco
*  referenciado por dstValue . A funcao retorna o valor do byte lido ou −1 se ocorreu um erro.
*  @param dstValue: Endereço do buffer onde vão ser recebidos os dados
*  @param address: endereço da EEPROM
*/
int CAT25128_ReadByte (unsigned char * dstValue , unsigned int address );

/**
*  Escreve o bloco de dados referenciado por srcAddr , de dimensao size bytes , no conteudo do endereco
* inicial da EEPROM indicado no parametro address . A funcao retorna o valor do byte lido ou −1 se ocorreu
* um erro .
*  @param srcAddr: Endereço do buffer com os dados a serem enviados
*  @param address: endereço da EEPROM
*  @param size: tamanho do buffer
*/
int CAT25128_WriteBlock ( void * srcAddr , unsigned int size , unsigned int address );

/**
*  Le para bloco de dados referenciado por dstAddr , de dimensao size bytes , do conteudo do endereco inicial
*  indicado no parametro address . A funcao retorna o valor do byte lido ou −1 se ocorreu um erro .
*  @param dstAddr: Endereço do buffer de destino onde vão ser recebidos os dados
*  @param address: endereço da EEPROM
*  @param size: tamanho do buffer de destino
*/
int CAT25128_ReadBlock ( void * dstAddr , unsigned int size , unsigned int address );

/**
*  Desativa a escrita
*  @param não tem parâmetros
*/
void write_disable(void);

/**
*  Ativa a escrita
*  @param não tem parâmetros
*/
void write_enable(void);

/**
*  Escreve na EEPROM um conjunto de 8 bits
*  @param data: Byte a ser escrito
*  @param address: endereço da EEPROM
*/
void dados_write(unsigned short data, unsigned int address);

/**
*  Lê da EEPROM um conjunto de 8 bits
*  Retorna o valor lido
*  @param data: Byte a ser escrito
*/
unsigned short dados_read(unsigned int address);

#endif /* EEPROM_H_ */

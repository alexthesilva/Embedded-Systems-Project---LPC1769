#include "flash.h"


#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#define SECTORm16 4096
#define SECTORM16 32768

// comandos IAP
#define	IAP_CMD_PREPARE_SECTORS			50
#define	IAP_CMD_COPY_RAM_TO_FLASH		51
#define	IAP_CMD_ERASE_SECTORS			52
#define	IAP_CMD_BLANK_CHECK_SECTORS		53
#define	IAP_CMD_READ_PART_ID			54
#define	IAP_CMD_READ_BOOT_ROM_VERSION	55
#define	IAP_CMD_COMPARE					56
#define	IAP_CMD_REINVOKE_ISP			57
#define IAP_CMD_READ_SERIAL_NUMBER		58

// Acesso à flash
#define ENDERECOIAP				0x1FFF1FF1UL
#define IAPCMD(a, b)			((void (*)())(ENDERECOIAP))(a, b)

enum error_code {
    CMD_SUCCESS,
    INVALID_COMMAND,
    SRC_ADDR_ERROR,
    DST_ADDR_ERROR,
    SRC_ADDR_NOT_MAPPED,
    DST_ADDR_NOT_MAPPED,
    COUNT_ERROR,
    INVALID_SECTOR,
    SECTOR_NOT_BLANK,
    SECTOR_NOT_PREPARED_FOR_WRITE_OPERATION,
    COMPARE_ERROR,
    BUSY,
    PARAM_ERROR,
    ADDR_ERROR,
    ADDR_NOT_MAPPED,
    CMD_LOCKED,
    INVALID_CODE,
    INVALID_BAUD_RATE,
    INVALID_STOP_BIT,
    CODE_READ_PROTECTION_ENABLED
};

unsigned int FLASH_BlankCheck (unsigned int sector){
	unsigned int endSector;
	unsigned int comando[5];
	unsigned int resultado[5];

	if(sector<16)
		endSector=sector+SECTORm16;
	else
		endSector=sector+SECTORM16;


	comando[0] = IAP_CMD_BLANK_CHECK_SECTORS;
	comando[1] = sector;
	comando[2] = endSector;
	IAPCMD(comando, resultado);

	return resultado[0];
}

unsigned int FLASH_PrepareSector (unsigned int sector) {
	unsigned int endSector;
	unsigned int comando[5];
	unsigned int resultado[5];

	if(sector<16)
		endSector=sector+SECTORm16;
	else
		endSector=sector+SECTORM16;

	//Preparação para a escrita
	comando[0] = IAP_CMD_PREPARE_SECTORS;
	comando[1] = sector;
	comando[2] = endSector;
	IAPCMD(comando, resultado);
	return resultado[0];
}

unsigned int FLASH_EraseSector (unsigned int sector) {

	unsigned int endSector;
	unsigned int comando[5];
	unsigned int resultado[5];

	if(sector<16)
		endSector=sector+SECTORm16;
	else
		endSector=sector+SECTORM16;

	comando[0] = IAP_CMD_ERASE_SECTORS;
	comando[1] = sector;
	comando[2] = endSector;
	comando[3] = SystemCoreClock / 1000UL;	// frequência em kHz
	IAPCMD(comando, resultado);

	return resultado[0];
}

unsigned int FLASH_WriteData ( void *dstAddr , void * srcAddr , unsigned int size ) {
	unsigned int comando[5];
	unsigned int resultado[5];

	comando[0] = IAP_CMD_COPY_RAM_TO_FLASH;
	comando[1] = (unsigned int)dstAddr;
	comando[2] = (unsigned int)srcAddr;
	comando[3] = size;
	comando[4] = SystemCoreClock / 1000UL;	// frequência em kHz

	IAPCMD(comando, resultado);

	return resultado[0];

	return 0;
}

unsigned int FLASH_VerifyData ( void *dstAddr , void * srcAddr , unsigned int size ) {
	unsigned int comando[5];
	unsigned int resultado[5];

	comando[0] = IAP_CMD_COMPARE;
	comando[1] = (unsigned int)dstAddr;
	comando[2] = (unsigned int)srcAddr;
	comando[3] = size;
	IAPCMD(comando, resultado);

	return resultado[0];
}

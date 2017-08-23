/*
 * executeVariousCommand.c
 */

#include <string.h>
#include <stdint.h>
#include "strtonum.h"
#include <stdio.h>
#include <stdlib.h>
#include "stm32f1xx_hal.h"
#include "main.h"
#include "SM_CommandLineInterface.h"
#include "executeVariousCommand.h"

extern SPI_HandleTypeDef hspi1;
extern UART_HandleTypeDef huart1;
extern uint8_t rxBuffer;

#define MAXCLISTRING	300 	// Biggest string the user will type
extern char rxString[MAXCLISTRING];
extern int rxindex;
#define CR		13				//"\r"
#define LF	 	10				//"\n"
#define BS		8				//"\b"
#define	del		127				//"del"

uint8_t lineFeed[] ={'\n'};
uint8_t backspace[] ={'\b'};
uint8_t doubleQuote[] = {'"'};
uint8_t space[] ={' '};
uint8_t messageCommand[] = {"this command does not exit, please type 'help' to see the command list.\n"};
uint8_t messageError[] = {"is not a digit\n"};
uint8_t messageAddress[] = {"is an invalid register address. The example of command read should be as: read 0x2XXXXXXX 8\n"};
uint8_t messageErrorFlashRead[] = {"is an invalid address. The example of command for flash read the page data should be as: flash read <msb address 23-16 bit> <msb address 15 - 8> <msb address 7 - 0> < max. no. of data to read is 256>\n"};
uint8_t messageErrorFlashWrite[] = {"is an invalid address. The example of command for flash page program should be as: flash write <msb address 23-16 bit> <msb address 15 - 8> <msb address 7 - 0> < max. no. of data write is 256>\n"};
uint8_t messageErrorFlashErase[] = {"is an invalid address. The example of command for flash erase sector should be as: flash erase <msb address 23-16 bit> <msb address 15 - 8> <msb address 7 - 0>\n"};
long int getValue;
char *getChar;
volatile int sizeofData = 0;
uint8_t uartTxBuffetForSpi[] = {0};

uint8_t helpMessg[] = {"This shell commands are defined internally. Type 'help' to see this list \n write <address of register> <data> <data>\t write the data into the provide register address \n\t example: write 0x20000000 0xa 23\n\t\t write 0xa into 0x20000000 address \n\t\t write 23 into 0x200000001 address\n read <address> <number of byte> \t read the data from provide register address\n flash erase <msb address 23-16 bit> <msb address 15 - 8> <msb address 7 - 0> \t\t erase sector \n flash read <msb address 23-16 bit> <msb address 15 - 8> <msb address 7 - 0> <no. of byte read data> \t\t read page \n flash write <msb address 23-16 bit> <msb address 15 - 8> <msb address 7 - 0> <data max. no. of data is 256> \t\t page program \n "};
uint8_t RxData[256] = {0};

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi){
	char hexNum[3] = {0 , 0 , ' '};
	uint8_t receiveData[128] = {0};
	int indexData = 0;
	volatile int i = 0;
	int indexSpi = 0;
	uint8_t reply[] = {"receive signal:\t"};
	indexSpi = (int)((hspi1.RxXferSize)*3);
	int j = 0;
	HAL_GPIO_WritePin(nss_GPIO_Port, nss_Pin, GPIO_PIN_SET);
	  while(j != (int)(hspi1.RxXferSize)){
	    sprintf(hexNum, "%02x",RxData[j]);
	    printf("[%c%c%c]\n", hexNum[0], hexNum[1], hexNum[2]);
	    receiveData[i] = (uint8_t)hexNum[0];
	    i++;
	    receiveData[i] = (uint8_t)hexNum[1];
	    i++;
	    receiveData[i] = (uint8_t)hexNum[3];
	    i++;
	    j++;
	    indexData = i;
	  }
	  receiveData[indexData+1] = LF;
	  __HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
	  memset( uartTxBuffetForSpi, 0, sizeofData );
	  HAL_UART_Transmit(&huart1, reply, sizeof(reply),20);
	  HAL_UART_Transmit_IT(&huart1, &receiveData[0], sizeof(receiveData));
}

void communicateUsingSpi(SPI_HandleTypeDef *hspi, uint8_t TXSPI[], uint8_t RXSPI[]){
  HAL_GPIO_WritePin(nss_GPIO_Port, nss_Pin, GPIO_PIN_RESET);
  __HAL_UART_DISABLE_IT(&huart1, UART_IT_RXNE);
  HAL_SPI_TransmitReceive_IT(&hspi1, TXSPI, RxData, sizeofData);
}

/*
 *
 */
void executeCMD(UART_HandleTypeDef *huart){
/**
 * Bits   |   Access   |   Name   | Reset  | Description |
 * [31:8] | Read only  | -------- | ------ |  Reserved   |
 * [7:0]  | Read-write | REG[7:0] | 0xXX   | ----------- |
 */

	char *tempString;
	int i = 0;
	char *writew = "writew";
	char *help ="help";
	char *read = "read";
	char *spi ="spi";
	char *flash = "flash";
	char *erase = "erase";
	char *write = "write";
	uint8_t address1 = 0;
	uint8_t address2 = 0;
	uint8_t address3 = 0;
	__IO uint32_t *addressw = NULL;
	//uint8_t spimode[] = {"SPI in mode 0 mean CPHOL is low and CPHA is first edge\n"};
	int getVal;
	int dataByte;
	int size =0;

	rxString[rxindex] = (char)rxBuffer;
	rxindex++;
	HAL_UART_Transmit(&huart1, &rxBuffer, 1, 0); // Echo the character that caused this callback so the user can see what they are typing
	printf("rxindex = [ %d ]	rxBuffer= [ '%c' ]\n", rxindex, rxBuffer);
	if (rxBuffer  == del || rxBuffer == BS){
		rxindex-=2;
		HAL_UART_Transmit(&huart1, space, sizeof(space),20);
		HAL_UART_Transmit(&huart1, backspace, sizeof(backspace),20);

		if(rxindex < 0){
			rxindex = 0;
		}
	}
	if (rxBuffer == LF){	// If user enter, response the cmd
		rxindex = 0;
		tempString = &rxString[0];
		printf("response\n");
		getChar = getSubString(&tempString);
		if(strcmp(getChar, help) == 0){
			HAL_UART_Transmit_IT(&huart1, (uint8_t *)helpMessg, sizeof(helpMessg));
			printf("help\n");
		}
		else if(strcmp(getChar, writew) == 0){
			getVal = getNumber(&tempString);
			if(getVal == -1){
				HAL_UART_Transmit(&huart1,doubleQuote, sizeof(doubleQuote),20);
				HAL_UART_Transmit(&huart1,doubleQuote, sizeof(doubleQuote),20);
			  HAL_UART_Transmit_IT(&huart1, &messageError[0], sizeof(messageError));
			}
			else{
			  addressw = (uint32_t *)getVal;
			  while(*tempString != '\n'){
			    if((getVal = getNumber(&tempString))!= -1){
		          *(__IO uint32_t *)addressw = getVal;
		          addressw++;
			    }
			    else{
			      HAL_UART_Transmit_IT(&huart1, &messageError[0], sizeof(messageError));
			      break;
			    }
		     }
		   }
		 }
		else if(strcmp(getChar, read) == 0){
			while(*tempString == ' ' || *tempString == '\t'){
			  tempString++;
			}
			if (isdigit((unsigned char)*tempString)){
			  addressw = (uint32_t *)getNumber(&tempString);
			  HAL_UART_Transmit(&huart1, (uint8_t *)addressw, sizeof(addressw),50);
			  HAL_UART_Transmit(&huart1, lineFeed, sizeof(lineFeed),50);
			}
			else{
              HAL_UART_Transmit_IT(&huart1, &messageError[0], sizeof(messageError));
		    }
			  while(*tempString == ' ' || *tempString == '\t'){
			    tempString++;
			  }
			  if (isdigit((unsigned char)*tempString)){
			    while(*tempString != '\n'){
			      dataByte = getNumber(&tempString);
			        while(dataByte > 1){
			        	dataByte--;
			        	addressw++;
			        	HAL_UART_Transmit(&huart1, (uint8_t *)addressw, sizeof(addressw),30);
			        	HAL_UART_Transmit(&huart1, lineFeed, sizeof(lineFeed),50);
			        }
			    }
			  }
			  else if (isalpha((char)*tempString)){
                HAL_UART_Transmit_IT(&huart1, &messageError[0], sizeof(messageError));
		     }
		}
		else if(strcmp(getChar, spi) == 0){
			getChar = NULL;
		    while(*tempString == ' ' || *tempString == '\t'){
		    	tempString++;
		    }
		    if (isdigit((unsigned char)*tempString)){
				sizeofData = getNumber(&tempString);
				if(sizeofData != 0){
				  memset( uartTxBuffetForSpi, 0, sizeofData );
				  while(*tempString == ' ' || *tempString == '\t'){
					  tempString++;
				 }
				  if (isdigit((unsigned char)*tempString)){
				    for(i = 0; i < sizeofData;i++){
					  while(*tempString == ' ' || *tempString == '\t'){
				   	    tempString++;
					  }
					  if (isdigit((unsigned char)*tempString)){
					    uartTxBuffetForSpi[i]= (char)getNumber(&tempString);
					  }
					  else{
					    HAL_UART_Transmit_IT(&huart1, &messageCommand[0], sizeof(messageCommand));
					    break;
					  }
				   }
				    communicateUsingSpi(&hspi1, uartTxBuffetForSpi, RxData);
				  }
				  else if(*tempString == '\n'){
				    HAL_UART_Transmit_IT(&huart1, &messageCommand[0], sizeof(messageCommand));
				  }
				  else{
					  HAL_UART_Transmit_IT(&huart1, &messageCommand[0], sizeof(messageCommand));
				  }
				}
			    else{
				   HAL_UART_Transmit_IT(&huart1, &messageCommand[0], sizeof(messageCommand));
				 }

			}
			 else{
			   HAL_UART_Transmit_IT(&huart1, &messageCommand[0], sizeof(messageCommand));
			 }
		}
		else if(strcmp(getChar, flash) == 0){
		  getChar = NULL;
	      while(*tempString == ' ' || *tempString == '\t'){
	    	tempString++;
	      }
		  if(isalpha((char)*tempString)){
		    getChar = getSubString(&tempString);
		    if(strcmp(getChar, erase) == 0){
		      flashEraseInterpreter(tempString);
		    }
		    else if(strcmp(getChar, write) == 0){
		      flashWriteInterpreter(tempString);
			  }
		    else if(strcmp(getChar, read) == 0){
		      flashReadInterpreter (tempString);
		    }
			else{
			  HAL_UART_Transmit_IT(&huart1, &messageCommand[0], sizeof(messageCommand));
			}
		  }
		  else{
		    HAL_UART_Transmit_IT(&huart1, &messageCommand[0], sizeof(messageCommand));
		  }
		}
		else{
		  HAL_UART_Transmit_IT(&huart1, &messageCommand[0], sizeof(messageCommand));
		}
	}
}

/*void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    executeCMD(&huart1);
    HAL_UART_Receive_IT(&huart1, &rxBuffer, 1);

}*/

// erase sector
/*
 * addressMSB1 = Address 23 bit to 16
 * addressMSB2 = Address 15 bit to 8
 * addressMSB2 = Address 7 bit to 0
 */
void flashSectorErase(uint8_t AddressMSB1, uint8_t AddressMSB2, uint8_t AddressMSB3){
  //sector from 0 -> 15
  int noByte = 4;
  uint8_t txdata[4] = {0x20, 0 , 0, 0};
  txdata[1] = AddressMSB1;
  txdata[2] = AddressMSB2;
  txdata[3] = AddressMSB3;
  HAL_GPIO_WritePin(nss_GPIO_Port, nss_Pin, GPIO_PIN_RESET);
  HAL_SPI_TransmitReceive_IT(&hspi1, txdata, RxData, noByte);
}

void flashWrite(uint8_t AddressMSB1, uint8_t AddressMSB2, uint8_t AddressMSB3, char *data){
	//1-256 byte
  int noByte = 4;
  uint8_t txdata[] = {0, 0, 0, 0, 0, 0, 0, 0};
  int i = 4;
  txdata[0] = 0x2;
  txdata[1] = AddressMSB1;
  txdata[2] = AddressMSB2;
  txdata[3] = AddressMSB3;
  int getNum = 0;
  flashSetWriteEnableFlash();
  while(*data != '\n'){
	  getNum = getNumber(&data);
	  if(getNum == -1 || getNum == -2){
	    break;
	  }
	  else{
	    txdata[i] = (uint8_t)getNum;
	    i++;
	  }
	  noByte = i;
    }

  HAL_GPIO_WritePin(nss_GPIO_Port, nss_Pin, GPIO_PIN_RESET);
  HAL_SPI_TransmitReceive_IT(&hspi1, txdata, RxData, noByte);

}
void flashRead(uint8_t AddressMSB1, uint8_t AddressMSB2, uint8_t AddressMSB3, int size){
	  int noByte = 4;
	  noByte+= size;
	  uint8_t txdata[] = {0, 0, 0 , 0 , 0, 0, 0, 0};
	  txdata[0] = 0x3;
	  txdata[1] = AddressMSB1;
	  txdata[2] = AddressMSB2;
	  txdata[3] = AddressMSB3;

	  HAL_GPIO_WritePin(nss_GPIO_Port, nss_Pin, GPIO_PIN_RESET);
	  HAL_SPI_TransmitReceive_IT(&hspi1, txdata, RxData, noByte);

}
void flashSetWriteEnableFlash(){
	  int noByte = 1;
	  uint8_t txdata[] = {0 , 0, 0};
	  txdata[0] = 0x6;
	  HAL_GPIO_WritePin(nss_GPIO_Port, nss_Pin, GPIO_PIN_RESET);
	  HAL_SPI_TransmitReceive(&hspi1, txdata, RxData, noByte, 60);
	  HAL_GPIO_WritePin(nss_GPIO_Port, nss_Pin, GPIO_PIN_SET);
}


void flashReadInterpreter (char *string){
	uint8_t address1 = 0;
	uint8_t address2 = 0;
	uint8_t address3 = 0;
	int size =0;


    while(*string == ' ' || *string == '\t'){
  	  string++;
	 }
    if (isdigit((unsigned char)*string)){
	  address1 = (uint8_t)getNumber(&string);
	}
    else
	  HAL_UART_Transmit_IT(&huart1, messageErrorFlashRead, sizeof(messageErrorFlashRead));

	while(*string == ' ' || *string == '\t'){
	  string++;
	}
	if (isdigit((unsigned char)*string)){
	  address2 = (uint8_t)getNumber(&string);
	}
    else
	  HAL_UART_Transmit_IT(&huart1, messageErrorFlashRead, sizeof(messageErrorFlashRead));

	while(*string == ' ' || *string == '\t'){
	  string++;
	}
	if (isdigit((unsigned char)*string)){
	  address3 = (uint8_t)getNumber(&string);
	}
    else
	  HAL_UART_Transmit_IT(&huart1, messageErrorFlashRead, sizeof(messageErrorFlashRead));

	while(*string == ' ' || *string == '\t'){
	  string++;
	}
	if (isdigit((unsigned char)*string)){
	  size = getNumber(&string);
	  flashRead(address1, address2, address3, size);
	}
    else
	  HAL_UART_Transmit_IT(&huart1, messageErrorFlashRead, sizeof(messageErrorFlashRead));
}

void flashWriteInterpreter(char *string){
	uint8_t address1 = 0;
	uint8_t address2 = 0;
	uint8_t address3 = 0;

	while(*string == ' ' || *string == '\t'){
		string++;
	}

	if (isdigit((unsigned char)*string)){
	  address1 = (uint8_t)getNumber(&string);
	}
    else
	  HAL_UART_Transmit_IT(&huart1, messageErrorFlashWrite, sizeof(messageErrorFlashWrite));

	while(*string == ' ' || *string == '\t'){
		string++;
	}
	if (isdigit((unsigned char)*string)){
	  address2 = (uint8_t)getNumber(&string);
	}
    else
	  HAL_UART_Transmit_IT(&huart1, messageErrorFlashWrite, sizeof(messageErrorFlashWrite));

	while(*string == ' ' || *string == '\t'){
		string++;
	}
	if (isdigit((unsigned char)*string)){
      address3 = (uint8_t)getNumber(&string);
	}
    else
	  HAL_UART_Transmit_IT(&huart1, messageErrorFlashWrite, sizeof(messageErrorFlashWrite));

	while(*string == ' ' || *string == '\t'){
		string++;
	}
	if (isdigit((unsigned char)*string)){
		flashWrite(address1, address2, address3, string);
	}
    else
	  HAL_UART_Transmit_IT(&huart1, messageErrorFlashWrite, sizeof(messageErrorFlashWrite));
}

void flashEraseInterpreter(char *string){
	uint8_t address1 = 0;
	uint8_t address2 = 0;
	uint8_t address3 = 0;
    while(*string == ' ' || *string == '\t'){
  	string++;
    }
    if (isdigit((unsigned char)*string)){
  	  address1 = (uint8_t)getNumber(&string);
    }
    else
	  HAL_UART_Transmit_IT(&huart1, messageErrorFlashErase, sizeof(messageErrorFlashErase));

  	while(*string == ' ' || *string == '\t'){
  		string++;
  	}
    if (isdigit((unsigned char)*string)){
  	  address2 = (uint8_t)getNumber(&string);
    }
    else
	  HAL_UART_Transmit_IT(&huart1, messageErrorFlashErase, sizeof(messageErrorFlashErase));

  	while(*string == ' ' || *string == '\t'){
  		string++;
  	}
    if (isdigit((unsigned char)*string)){
  	  address3 = (uint8_t)getNumber(&string);
  	flashSectorErase(address1, address2, address3);
    }
    else
	  HAL_UART_Transmit_IT(&huart1, messageErrorFlashErase, sizeof(messageErrorFlashErase));


}


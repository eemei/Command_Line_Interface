/*
 * executeVariousCommand.h
 *
 *  Created on: Aug 22, 2017
 *      Author: liewe
 */

#ifndef EXECUTEVARIOUSCOMMAND_H_
#define EXECUTEVARIOUSCOMMAND_H_

void executeCMD(UART_HandleTypeDef *huart);
extern void initialise_monitor_handles(void);
void communicateUsingSpi(SPI_HandleTypeDef *hspi, uint8_t TXSPI[], uint8_t RXSPI[]);
void flashSectorErase(uint8_t AddressMSB1, uint8_t AddressMSB2, uint8_t AddressMSB3);
void flashWrite(uint8_t AddressMSB1, uint8_t AddressMSB2, uint8_t AddressMSB3, char *data);
void flashRead(uint8_t AddressMSB1, uint8_t AddressMSB2, uint8_t AddressMSB3, int size);
void flashSetWriteEnableFlash();
void flashReadInterpreter (char *string);
void flashWriteInterpreter(char *string);
void flashEraseInterpreter(char *string);
#endif /* EXECUTEVARIOUSCOMMAND_H_ */

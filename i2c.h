#ifndef __I2C1_H
#define __I2C1_H
#include <stm32f10x.h>
#include <stdint.h>

void I2C1_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_EV6_1(void);
void I2C_EV7_1(void);
void I2C_Address_Send(uint8_t addr);
void I2C_Read_Started(uint8_t addr, uint8_t *buff, uint8_t size);
void I2C_Read(uint8_t addr, uint8_t reg, uint8_t *buff, uint8_t size);
void I2C_Write_Started(uint8_t data);
void I2C_Write_To_Reg(uint8_t addr, uint8_t data, uint8_t reg);
void I2C_Write(uint8_t address, uint8_t data);

#endif

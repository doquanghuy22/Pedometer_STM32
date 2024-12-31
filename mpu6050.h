#ifndef __MPU6050_H
#define __MPU6050_H
#include <stm32f10x.h>

/*------------MPU ADDRESS-----------------*/
#define MPU6050_ADDR 0xD0
/*------------MPU sensitivity-------------*/
#define MPU6050_ASENS 16384.0
/*------------Define Register-------------*/
#define WHO_AM_I 0x75
#define PWR_MGMT_1 0x6B
#define SMPLRT_DIV 0x19
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C

#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40
/*------------Define functions------------*/

extern int16_t MPU6050_accX;
extern int16_t MPU6050_accY;
extern int16_t MPU6050_accZ;
int16_t MPU_read_accX(void);
int16_t MPU_read_accY(void);
int16_t MPU_read_accZ(void);
double MPU_read_Acc_total(void);
void MPU_Read(uint8_t addr, uint8_t reg, uint8_t *buff, uint8_t size);
void MPU_Write(uint8_t addr, uint8_t reg, uint8_t data);
void MPU6050_init(void);
#endif

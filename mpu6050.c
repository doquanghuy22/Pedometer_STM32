#include "mpu6050.h"
#include "i2c.h"
#include <math.h>
#include <stdint.h>


int16_t MPU6050_accX, MPU6050_accY, MPU6050_accZ;
int16_t MPU6050_prev_accX = 0, MPU6050_prev_accY = 0, MPU6050_prev_accZ = 0;

int16_t MPU_read_accX(void) {
    uint8_t data[2];
    int16_t Accel_X_RAW;
    I2C_Read(MPU6050_ADDR, ACCEL_XOUT_H, data, 2);

    Accel_X_RAW = (int16_t)(data[0] << 8 | data[1]);
    return Accel_X_RAW;
}

int16_t MPU_read_accY(void) {
    uint8_t data[2];
    int16_t Accel_Y_RAW;
    I2C_Read(MPU6050_ADDR, ACCEL_YOUT_H, data, 2);

    Accel_Y_RAW = (int16_t)(data[0] << 8 | data[1]);
    return Accel_Y_RAW;
}

int16_t MPU_read_accZ(void) {
    uint8_t data[2];
    int16_t Accel_Z_RAW;
    I2C_Read(MPU6050_ADDR, ACCEL_ZOUT_H, data, 2);

    Accel_Z_RAW = (int16_t)(data[0] << 8 | data[1]);
    return Accel_Z_RAW;
}

double MPU_read_Acc_total(void) {
    uint8_t data[6];
    double total_acc;

    /* Ð?c d? li?u gia t?c cho 3 tr?c */
    I2C_Read(MPU6050_ADDR, ACCEL_XOUT_H, data, 6);

    /* Luu tr? gia t?c tru?c dó */
    MPU6050_prev_accX = MPU6050_accX;
    MPU6050_prev_accY = MPU6050_accY;
    MPU6050_prev_accZ = MPU6050_accZ;

    /* C?p nh?t gia t?c hi?n t?i */
    MPU6050_accX = (int16_t)(data[0] << 8 | data[1]);
    MPU6050_accY = (int16_t)(data[2] << 8 | data[3]);
    MPU6050_accZ = (int16_t)(data[4] << 8 | data[5]);

    /* Tính toán t?ng gia t?c theo s? thay d?i */
    total_acc = pow(MPU6050_accX - MPU6050_prev_accX, 2) + 
                pow(MPU6050_accY - MPU6050_prev_accY, 2) + 
                pow(MPU6050_accZ - MPU6050_prev_accZ, 2);

    total_acc = sqrt(total_acc) / MPU6050_ASENS;

    return total_acc;
}

void MPU_Read(uint8_t addr, uint8_t reg, uint8_t *buff, uint8_t size) {
    I2C_Read(addr, reg, buff, size);
}

void MPU_Write(uint8_t addr, uint8_t reg, uint8_t data) {
    I2C_Write_To_Reg(addr, reg, data);
}

void MPU6050_init(void) {
    uint8_t check;
    uint8_t Data;

    /* Ki?m tra k?t n?i MPU6050 */
    MPU_Read(MPU6050_ADDR, WHO_AM_I, &check, 1);
    if (check == 0x68)  /* 0x68 dúng khi MPU6050 k?t n?i thành công */
    {
        Data = 0;
        MPU_Write(MPU6050_ADDR, PWR_MGMT_1, Data);

        /* Cài d?t t?c d? m?u */
        Data = 79;
        MPU_Write(MPU6050_ADDR, SMPLRT_DIV, Data);

        Data = 0x00;
        MPU_Write(MPU6050_ADDR, ACCEL_CONFIG, Data);
        MPU_Write(MPU6050_ADDR, GYRO_CONFIG, Data);
    }
}

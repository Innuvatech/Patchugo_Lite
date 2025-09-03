/**
* File: i2c_manager.cpp
* Created on: 2025-09-02 at 16:06
* Author: Andrea Rantin
* Description: Implementation file for i2c_manager.h
*/

#include "internal/i2c_manager/i2c_manager.h"

extern I2C_HandleTypeDef hi2c3;

PatchugoStatusCode I2C_Manager::Init(I2CConfigStruct configStruct) {
    PatchugoStatusCode checkError = I2C_HAL_Init(configStruct);
    if(checkError != OK) return checkError;
    return OK;
}

PatchugoStatusCode I2C_Manager::I2C_Write(uint8_t addr, uint8_t *data, uint16_t len, uint32_t timeout) {
    if(HAL_I2C_Master_Transmit(&hi2c3, addr, data, len, timeout) != HAL_OK) return ERROR_I2C_WRITE;
    return OK;
}

PatchugoStatusCode I2C_Manager::I2C_Read(uint8_t addr, uint8_t *readData, uint16_t len, uint32_t timeout) {
    if(HAL_I2C_Master_Receive(&hi2c3,addr,readData,len,timeout) != HAL_OK) return ERROR_I2C_READ;
    return OK;
}

PatchugoStatusCode I2C_Manager::I2C_WriteReg(uint8_t addr, uint16_t regAddr, uint16_t regAddrSize, uint8_t *writeData, uint16_t len, uint32_t timeout) {
    if(HAL_I2C_Mem_Write(&hi2c3, addr, regAddr, regAddrSize, writeData, len, timeout) != HAL_OK) return ERROR_I2C_WRITE_REG;
    return OK;
}

PatchugoStatusCode I2C_Manager::I2C_ReadReg(uint8_t addr, uint16_t regAddr, uint16_t regAddrSize, uint8_t *readData, uint16_t len, uint32_t timeout) {
    if(HAL_I2C_Mem_Read(&hi2c3, addr, regAddr, regAddrSize, readData, len, timeout) != HAL_OK) return ERROR_I2C_READ_REG;
    return OK;
}


/**
* File: flash_manager.cpp
* Created on: 2025-09-04 at 11:15
* Author: Andrea Rantin
* Description: Implementation file for flash_manager.h
*/

#include "internal/flash_manager/flash_manager.h"

extern SPI_HandleTypeDef hspi3;

PatchugoStatusCode Flash_Manager::Flash_Init(void) {
    pinMode(FLASH_CS_PIN, OUTPUT);

    return Flash_SPI_HAL_Init();
}

PatchugoStatusCode Flash_Manager::Flash_Read_Register(uint8_t reg, uint8_t *readValue) {
        digitalWrite(FLASH_CS_PIN, LOW);
        delay(10);
        if(HAL_SPI_Transmit(&hspi3, &reg, 1, 0xFF) != HAL_OK){
            digitalWrite(FLASH_CS_PIN, HIGH);
            return ERROR_FLASH_READ_REG;
        } 
    	if(HAL_SPI_Receive(&hspi3, readValue, 1, 0xFF) != HAL_OK){
            digitalWrite(FLASH_CS_PIN, HIGH);
            return ERROR_FLASH_READ_REG;
        }
        delay(10);
        digitalWrite(FLASH_CS_PIN, HIGH);
        return OK;
}

PatchugoStatusCode Flash_Manager::Flash_Write_Instruction(uint8_t instruction) {

    digitalWrite(FLASH_CS_PIN, LOW);
    delay(10);
    if(HAL_SPI_Transmit(&hspi3, &instruction, 1, 0xFF) != HAL_OK){
        digitalWrite(FLASH_CS_PIN, LOW);
        return ERROR_FLASH_WRITE_INSTRUCTION;
    } 
    delay(10);
    digitalWrite(FLASH_CS_PIN, HIGH);
    return OK;
}

PatchugoStatusCode Flash_Manager::Flash_Check_Status1(void) {
    uint8_t reg1 = 0;
	uint8_t reg = 0;

    uint32_t startMillis = millis();

    do{
        if(Flash_Read_Register(FLASH_STATUS_REG_1, &reg1) != OK) return ERROR_FLASH_STATUS;
        reg = reg1 & 0x01;
        int32_t currentMillis = millis();
        if((currentMillis - startMillis) > 20000){
            return ERROR_FLASH_STATUS;
        } 
    }while(reg == 0x01);

    return OK;
}

PatchugoStatusCode Flash_Manager::Flash_Reset(void) {
    PatchugoStatusCode checkError = Flash_Write_Instruction(FLASH_CMD_ENABLE_RESET);
    if(checkError != OK) return checkError;
    delay(2000);
    checkError = Flash_Write_Instruction(FLASH_CMD_RESET);
    if(checkError != OK) return checkError;

    return Flash_Check_Status1();
}

PatchugoStatusCode Flash_Manager::Flash_Erase(void) {
    PatchugoStatusCode checkError =  Flash_Write_Instruction(FLASH_CMD_WRITE_ENB);
    if(checkError != OK) return checkError;
    delay(10);
    checkError = Flash_Write_Instruction(FLASH_CMD_ERASE_CHIP);
    if(checkError != OK) return checkError;

    return Flash_Check_Status1();
}

PatchugoStatusCode Flash_Manager::Flash_Erase_Sector(Flash_Sector sector) {
    uint32_t sectorAddr = static_cast<uint32_t>(sector);
    uint32_t convertedAddr = sectorAddr & 0xFFFFFF;

    PatchugoStatusCode checkError = Flash_Write_Instruction(FLASH_CMD_WRITE_ENB);
    if(checkError != OK) return checkError;
    delay(10);

    uint8_t cmdBuf[FLASH_CMD_LEN] = {0};

    cmdBuf[0] = FLASH_CMD_ERASE_SECTOR;
    cmdBuf[1] = (convertedAddr >> 16) & 0xFF;
    cmdBuf[2] = (convertedAddr >> 8) & 0xFF;
    cmdBuf[3] = convertedAddr & 0xFF;

    digitalWrite(FLASH_CS_PIN, LOW);
    delay(10);

    if(HAL_SPI_Transmit(&hspi3, cmdBuf, FLASH_CMD_LEN, 0xFF) != HAL_OK){
        digitalWrite(FLASH_CS_PIN, HIGH);
        return ERROR_FLASH_SECTOR_ERASE;
    } 
    delay(10);
    digitalWrite(FLASH_CS_PIN, HIGH);

    return Flash_Check_Status1();
}

PatchugoStatusCode Flash_Manager::Flash_Read_Data(Flash_Sector sector, Flash_Page page, uint8_t *readData, uint32_t len) {

    uint32_t sectorAddr = static_cast<uint32_t>(sector);
    uint32_t pageAddr = static_cast<uint32_t>(page);
    uint32_t writeAddr = sectorAddr + pageAddr;
    uint32_t convertedAddr = writeAddr & 0xFFFFFF;

    uint8_t cmdBuf[FLASH_CMD_LEN] = {0};
    cmdBuf[0] = FLASH_CMD_READ_DATA;
    cmdBuf[1] = (convertedAddr >> 16) & 0xFF;
    cmdBuf[2] = (convertedAddr >> 8) & 0xFF;
    cmdBuf[3] = convertedAddr & 0xFF;

    digitalWrite(FLASH_CS_PIN, LOW);
    delay(10);

    if(HAL_SPI_Transmit(&hspi3, cmdBuf, FLASH_CMD_LEN, 0xFF) != HAL_OK) {
        digitalWrite(FLASH_CS_PIN, HIGH);
        return ERROR_FLASH_READ_DATA;
    }

    if(HAL_SPI_Receive(&hspi3, readData, len, 0xFF) != HAL_OK) {
        digitalWrite(FLASH_CS_PIN, HIGH);
        return ERROR_FLASH_READ_DATA;
    }

    delay(10);
    digitalWrite(FLASH_CS_PIN, HIGH);
    return OK;
}

PatchugoStatusCode Flash_Manager::Flash_Write_Data(Flash_Sector sector, Flash_Page page, uint8_t *writeData, uint8_t len) {

    uint32_t sectorAddr = static_cast<uint32_t>(sector);
    uint32_t pageAddr = static_cast<uint32_t>(page);
    uint32_t writeAddr = sectorAddr + pageAddr;
    uint32_t convertedAddr = writeAddr & 0xFFFFFF;

    PatchugoStatusCode checkError =  Flash_Write_Instruction(FLASH_CMD_WRITE_ENB);
    if(checkError != OK) return checkError;

    uint8_t dataTx[FLASH_PAGE_SIZE+4] = {0}; //+4 PERCHE' 1 BYTE DI CMD E 3 DI ADDRESS
    dataTx[0] = FLASH_CMD_WRITE_PAGE;
    dataTx[1] = (convertedAddr >> 16) & 0xFF;
    dataTx[2] = (convertedAddr >> 8) & 0xFF;
    dataTx[3] = convertedAddr & 0xFF;

    memcpy(dataTx+4,writeData,len);

    digitalWrite(FLASH_CS_PIN, LOW);
    delay(10);

    if(HAL_SPI_Transmit(&hspi3, dataTx, len+4, 0x00FF) != HAL_OK) {
        digitalWrite(FLASH_CS_PIN, HIGH);
        return ERROR_FLASH_WRITE_DATA;
    }

    delay(10);
    digitalWrite(FLASH_CS_PIN, HIGH);

    return OK;
}
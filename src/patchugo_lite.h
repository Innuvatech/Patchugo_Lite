/**
* File: patchugo_lite.h
* Created on: 2025-09-01 at 21:35
* Author: Andrea Rantin
* Description: //TODO
*/

#pragma once

#include "internal/io_manager/io_manager.h"
#include "internal/bt_manager/bt_manager.h"
#include "internal/serial_manager/serial_manager.h"
#include "internal/i2c_manager/i2c_manager.h"
#include "internal/spi_manager/spi_manager.h"
#include "internal/flash_manager/flash_manager.h"

class PatchugoLite {
    private:
        IO_Manager ioManager;
        BT_Manager btManager;
        Serial_Manager serialManager;
        I2C_Manager i2cManager;
        SPI_Manager spiManager;
        Flash_Manager flashManager;
    public:
        //TODO
        PatchugoStatusCode Init(void);

        void ISO_IO_Write(ISO_OutputPin_Typedef pin, FlagStatus state);
        uint8_t ISO_IO_Read(ISO_InputPin_Typedef pin);
        
        PatchugoStatusCode BT_Change_Name(const char *name);
        PatchugoStatusCode BT_Set_MTU(uint16_t mtu);
        PatchugoStatusCode BT_Set_Mode(BTMode mode);
        PatchugoStatusCode BT_Send_AT(uint8_t *cmdData,uint8_t len, DMA_CALLBACK_PTR callback);
        PatchugoStatusCode BT_Async_RX_Set_Callback(DMA_CALLBACK_PTR ptr, PatchugoStatusCode* result);
        void BT_Start_Async_Listen(void);

        PatchugoStatusCode RS485_Serial_Init(SerialBaudRate baudRate, SerialAdvConfStruct advConfStruct = SERIAL_DEFAULT_ADV_CONF_STRUCT);
        PatchugoStatusCode RS485_Serial_Write(uint8_t* buf, uint16_t len);
        PatchugoStatusCode RS485_Serial_Read(uint8_t* buf, uint16_t len, uint32_t timeout);
        PatchugoStatusCode USB_Serial_Init(SerialBaudRate baudRate, SerialAdvConfStruct advConfStruct = SERIAL_DEFAULT_ADV_CONF_STRUCT);
        PatchugoStatusCode USB_Serial_Write(uint8_t* buf, uint16_t len);
        PatchugoStatusCode USB_Serial_Read(uint8_t* buf, uint16_t len, uint32_t timeout);
        PatchugoStatusCode RS485_Async_RX_Set_Callback(DMA_CALLBACK_PTR ptr, PatchugoStatusCode* result);
        void RS485_Start_Async_Listen(void);

        PatchugoStatusCode SPI_Write(SPI_CS cs, uint8_t *writeData, uint16_t len, uint32_t timeout);
        PatchugoStatusCode SPI_Read(SPI_CS cs, uint8_t *readData, uint16_t len, uint32_t timeout);

        PatchugoStatusCode I2C_Init(I2CConfigStruct configStruct = DEFAULT_I2C_CONFIG_STRUCT);
        PatchugoStatusCode I2C_Write(uint8_t addr, uint8_t *data, uint16_t len, uint32_t timeout);
        PatchugoStatusCode I2C_Read(uint8_t addr, uint8_t *readData, uint16_t len, uint32_t timeout);
        PatchugoStatusCode I2C_WriteReg(uint8_t addr, uint16_t regAddr, uint16_t regAddrSize, uint8_t *writeData, uint16_t len, uint32_t timeout);
        PatchugoStatusCode I2C_ReadReg(uint8_t addr, uint16_t regAddr, uint16_t regAddrSize, uint8_t *readData, uint16_t len, uint32_t timeout);

        PatchugoStatusCode Flash_Read_Register(uint8_t reg, uint8_t *readValue);
        PatchugoStatusCode Flash_Write_Instruction(uint8_t instruction);
        PatchugoStatusCode Flash_Reset(void);
        PatchugoStatusCode Flash_Erase(void);
        PatchugoStatusCode Flash_Erase_Sector(Flash_Sector sector);
        PatchugoStatusCode Flash_Read_Data(Flash_Sector sector, Flash_Page page, uint8_t *readData, uint32_t len);
        PatchugoStatusCode Flash_Write_Data(Flash_Sector sector, Flash_Page page, uint8_t *writeData, uint8_t len);

};
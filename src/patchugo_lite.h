/**
* File: patchugo_lite.h
* Created on: 2025-09-01 at 21:35
* Author: Andrea Rantin
* Description: This file contains the definition of the PatchugoLite class and its members/functions. The class is 
* the main component of the library and the one the user interacts with to control all peripherals of the board. The class
* contains a private class member for each peripherals. The private class members of PatchugoLite are:
* - IO_Manager: Allows controlling the 24V isolated I/O pins. It provides the following functionalities:
    - Initializing all isolated 24V I/O pins(done automatically inside the Init method of PatchugoLite)
    - Writing one of the OUTPUT pins
    - Reading one of the INPUT pins
* - BT_Manager: Allows controlling the bluetooth module of the board. It provides the following functionalities:
    - Initializing the bluetooth with some default values(done automatically inside the Init method of PatchugoLite)
    - Sending an AT command to turn echo off(done automatically inside the Init method of BT_Manager)
    - Sending an AT command to change bluetooth name
    - Sending an AT command to change MTU
    - Changing mode to COMMAND or TRANSPARENT mode
    - Sending any AT with the BT_Send_AT function
    - Setting a user provided asyncrhonous callback
* - Serial_Manager: Allows controlling both the RS485 and the USB serial peripherals of the board. It provides the following functionalities:
    - Initializing RS485 Serial (done automatically inside the Init method of BT_Manager)
    - Initializing USB Serial (done automatically inside the Init method of BT_Manager)
    - Writing trough RS485 Serial
    - Reading from RS485 Serial
    - Setting an asyncrhonous callback for RS485 Serial
    - Writing trough USB Serial
    - Reading from USB Serial
* - I2C_Manager: Allows controlling the I2C of the board. It provides the following functionalities:
    - Initializing I2C (done automatically inside the Init method of PatchugoLite)
    - Writing to a connected I2C device
    - Reading from a connected I2C device
    - Writing to a specific register of a connected I2C device
    - Reading from a specific register of a connected I2C device
* - SPI_Manager: Allows controlling the SPI of the board. It provides the following functionalities:
    - Initializing SPI (done automatically inside the Init method of BT_Manager)
    - Writing to a connected SPI device
    - Reading from a connected SPI device
* - Flash_Manager: Allows controlling the external flash chip of the board. It provides the following functionalities:
    - Erasing the flash
    - Erasing a sector of the flash
    - Resetting the flash
    - Writing to the flash
    - Reading from the flash
    - Reading a register of the flash
    - Writing a single byte instruction to the flash
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
        /**
        * @brief Initializes all the peripherals of the PatchugoLite boards with their configuration values. 
        * The order of initialization is as follows:
        * - The Isolated 24V I/O pins are initialized with their respective mode
        * - The RS485 Serial is initialized with a baudrate of 115200
        * - The USB Serial is initialized with a baudrate of 115200
        * - The I2C is initialized
        * - The SPI is initialized with low clock polarity and 2edge detection
        * - The bluetooth is initilized with a default name of "PatchugoLite"
        * - The external flash chip is initialized
        * 
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: The initialization was completed successfully
        * - ERROR_RS485_SERIAL_HAL_INIT: The low level initialization of the RS485 Serial failed
        * - ERROR_USB_SERIAL_HAL_INIT: The low level intialization of the USB Serial failed
        * - ERROR_I2C_HAL_INIT: The low level initialization of the I2C failed
        * - ERROR_SPI_HAL_INIT: The low level initialization of the SPI failed
        * - ERROR_BT_SERIAL_HAL_INIT: The low level initialization of the Serial for the bluetooth failed
        * - ERROR_BT_MODE: There was an error while setting the bluetooth in COMMAND mode during initialization
        * - ERROR_BT_ECHO_OFF_SEND_CMD: There was an error while sending the command to turn off the bluetooth echo during initialization
        * - ERROR_BT_ECHO_OFF: There was an error while turning bluetooth echo off during initialization
        * - ERROR_BT_NAME_LEN: There was an error while setting the default bluetooth name during initialization
        * - ERROR_BT_NAME_SEND_CMD: There was an error while sending the command to change the bluetooh name during initialization
        * - ERROR_BT_CHANGE_NAME: There was an error while changing the bluetooth name during initialization
        * - ERROR_DMA_CALLBACK_NULL: There was an error while setting an internal asyncrhonous callback during initialization
        * - ERROR_DMA_RESULT_NULL: There was an error while setting an internal asyncrhonous callback during initialization
        */
        PatchugoStatusCode Init(void);

        /**
        * @brief Writes to a 24V isolated OUTPUT pin
        * 
        * @param pin Pin to write, this is a value of @ref ISO_OutputPin_Typedef
        * @param state Value to write to the pin(can be RESET or SET)
        */
        void ISO_IO_Write(ISO_OutputPin_Typedef pin, FlagStatus state);

         /**
        * @brief Reads a 24V isolated INPUT pin
        * 
        * @param pin Pin to read, this is a value of @ref ISO_InputPin_Typedef
        * @return uint8_t Value read from the pin(0 or 1)
        */
        uint8_t ISO_IO_Read(ISO_InputPin_Typedef pin);
        
        /**
        * @brief Turns the echo from AT commands OFF
        * 
        * @return PatchugoStatusCode 
        */
        PatchugoStatusCode BT_Echo_Off(void);

        /**
        * @brief Changes the bluetooth name to the given one
        * 
        * @param name Name to give the bluetooth
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: The bluetooth name was changed correctly
        * - ERROR_BT_NAME_LEN: The gievn name exceeded the max possible length of 20 characters
        * - ERROR_BT_CHANGE_NAME: The name could not be changed
        * - ERROR_BT_NAME_SEND_CMD: The change name command could not be sent to the bluetooth
        * @note: The given name MUST NOT exceed 20 characters of length, otherwise this function will return an error!
        */
        PatchugoStatusCode BT_Change_Name(const char *name);

        /**
        * @brief Sets the bluetooth MTU to the given value
        * 
        * @param mtu MTU to set
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: The MTU was changed successfully
        * - ERROR_BT_SET_MTU: The MTU could not be changed
        * - ERROR_BT_MTU_SEND_CMD: The AT command to change MTU could not be sent to the bluetooth
        */
        PatchugoStatusCode BT_Set_MTU(uint16_t mtu);

        /**
        * @brief Changes bluetooth operating mode
        * 
        * @param mode Mode to switch to
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: The operating mode was changed correctly
        * - ERROR_BT_MODE: The mode could not be changed
        * @note: To switch to transparent mode, the bluetooth must be connected!
        */
        PatchugoStatusCode BT_Set_Mode(BTMode mode);

        /**
        * @brief Sends an user provided AT command to the bluetooth
        * 
        * @param cmdData Buffer of the AT command to send
        * @param len Length of the buffer
        * @param callback Callback to trigger on AT command response
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: The AT command was executed correctly(note that this depends on the implementation of the user provided callback)
        * - ERROR_BT_SEND_AT: The AT command could not be sent
        * - ERROR_BT_AT: This is returned if the implementation of the callback given by the user is empty and does not return OK
        */
        PatchugoStatusCode BT_Send_AT(uint8_t *cmdData,uint8_t len, DMA_CALLBACK_PTR callback);

        /**
        * @brief Sets the callback to be used when the next "DMA" rx is completed
        * 
        * @param ptr Function pointer to be called as callback
        * @param result Result of the elaboration inside the callback
        * @return PatchugoStatusCode This function can return the following values
        * - OK: The callback was set successfuly
        * - ERROR_DMA_CALLBACK_NULL: The funcion pointer provided to be used as callback is NULL
        * - ERROR_DMA_RESULT_NULL: The pointer to be filled with the result of the elaboration is NULL
        */
        PatchugoStatusCode BT_Async_RX_Set_Callback(DMA_CALLBACK_PTR ptr, PatchugoStatusCode* result);

        /**
        * @brief Resets the "DMA" count to 0 and starts listening again.
        * This can be considered a sort of rearm of bluetooth "DMA"
        */
        void BT_Start_Async_Listen(void);

        /**
        * @brief Initializes the RS485 serial with the given baudrate
        * 
        * @param baudRate Baudrate to set
        * @param advConfStruct Optional advanced configuration structure with advanced parameters. If not provided this
        * defaults to a default structure of the library.
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: The serial was initialized correctly
        * - ERROR_RS485_SERIAL_HAL_INIT: Low level initialization of RS485 peripherals failed
        * @note: It is HIGHLY RECOMMENDED not to override the default value of advConfStruct
        */
        PatchugoStatusCode RS485_Serial_Init(SerialBaudRate baudRate, SerialAdvConfStruct advConfStruct = SERIAL_DEFAULT_ADV_CONF_STRUCT);

        /**
        * @brief Performs a serial write trough RS485 serial
        * 
        * @param buf Buffer to write
        * @param len Length of the buffer to write
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: The buffer was transmitter
        * - ERROR_RS485_SERIAL_WRITE: The serial could not write
        */
        PatchugoStatusCode RS485_Serial_Write(uint8_t* buf, uint16_t len);

        /**
        * @brief Performs a blocking read with the RS485 serial
        * 
        * @param buf Buffer where the read data will be put
        * @param len Length of the data to read
        * @param timeout Timeout of the read
        * @return PatchugoStatusCode This funcion can return the following values:
        * - OK: The read was completed successfully
        * - ERROR_RS485_SERIAL_READ: The read went into an error or timed out
        */
        PatchugoStatusCode RS485_Serial_Read(uint8_t* buf, uint16_t len, uint32_t timeout);

         /**
        * @brief Initializes the RS485 serial with the given baudrate
        * 
        * @param baudRate Baudrate to set
        * @param advConfStruct Optional advanced configuration structure with advanced parameters. If not provided this
        * defaults to a default structure of the library.
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: The serial was initialized correctly
        * - ERROR_USB_SERIAL_HAL_INIT: Low level initialization of USB peripherals failed
        * @note: It is HIGHLY RECOMMENDED not to override the default value of advConfStruct
        */
        PatchugoStatusCode USB_Serial_Init(SerialBaudRate baudRate, SerialAdvConfStruct advConfStruct = SERIAL_DEFAULT_ADV_CONF_STRUCT);

        /**
        * @brief Performs a serial write trough USB serial
        * 
        * @param buf Buffer to write
        * @param len Length of the buffer to write
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: The buffer was transmitter
        * - ERROR_USB_SERIAL_WRITE: The serial could not write
        */
        PatchugoStatusCode USB_Serial_Write(uint8_t* buf, uint16_t len);

        /**
        * @brief Performs a blocking read with the USB serial
        * 
        * @param buf Buffer where the read data will be put
        * @param len Length of the data to read
        * @param timeout Timeout of the read
        * @return PatchugoStatusCode This funcion can return the following values:
        * - OK: The read was completed successfully
        * - ERROR_USB_SERIAL_READ: The read went into an error or timed out
        */
        PatchugoStatusCode USB_Serial_Read(uint8_t* buf, uint16_t len, uint32_t timeout);

        /**
        * @brief Sets the callback to be used when the next "DMA" rx is completed
        * 
        * @param ptr Function pointer to be called as callback
        * @param result Result of the elaboration inside the callback
        * @return PatchugoStatusCode This function can return the following values
        * - OK: The callback was set successfuly
        * - ERROR_DMA_CALLBACK_NULL: The funcion pointer provided to be used as callback is NULL
        * - ERROR_DMA_RESULT_NULL: The pointer to be filled with the result of the elaboration is NULL
        */
        PatchugoStatusCode RS485_Async_RX_Set_Callback(DMA_CALLBACK_PTR ptr, PatchugoStatusCode* result);

        /**
        * @brief Resets the "DMA" count to 0 and starts listening again.
        * This can be considered a sort of rearm of RS485 "DMA"
        */
        void RS485_Start_Async_Listen(void);


        /**
        * @brief Writes a buffer trough SPI
        * 
        * @param cs Chip select to use
        * @param writeData Buffer to write
        * @param len Length of data to write
        * @param timeout Timeout in milliseconds
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: The SPI write was successful
        * - ERROR_SPI_WRITE: There was an error or timeout during the SPI write
        */
        PatchugoStatusCode SPI_Write(SPI_CS cs, uint8_t *writeData, uint16_t len, uint32_t timeout);

        /**
        * @brief Reads a buffer trough SPI
        * 
        * @param cs Chip select to use
        * @param readData Buffer to write
        * @param len Length of data to write
        * @param timeout Timeout in milliseconds
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: The SPI read was successful
        * - ERROR_SPI_READ: There was an error or timeout during the SPI read
        */
        PatchugoStatusCode SPI_Read(SPI_CS cs, uint8_t *readData, uint16_t len, uint32_t timeout);


        /**
        * @brief Initialized the I2C peripheral of the board
        * 
        * @param configStruct Optional configuration structure to provide with I2C configuration parameters. If not provided this has default values
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: The I2C was initialized correctly
        * - ERROR_I2C_HAL_INIT: An error occurred during low level I2C initialization
        */
        PatchugoStatusCode I2C_Init(I2CConfigStruct configStruct = DEFAULT_I2C_CONFIG_STRUCT);

        /**
        * @brief Performs a write on the I2C
        * 
        * @param addr Address of the I2C device to write to
        * @param data Data to write
        * @param len Length of the data to write
        * @param timeout Timeout in milliseconds
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: I2C write was successful
        * - ERROR_I2C_WRITE: There was an error during I2C write
        */
        PatchugoStatusCode I2C_Write(uint8_t addr, uint8_t *data, uint16_t len, uint32_t timeout);

        /**
        * @brief Performs a read from the I2C device with the address specified
        * 
        * @param addr Address of the I2C device to read from
        * @param readData Buffer that will be filled with data read
        * @param len Length of the data to read
        * @param timeout Timeout in milliseconds
        * @return PathugoStatusCode This function can return the following values:
        * - OK: I2C read was successful, data is in readData
        * - ERROR_I2C_READ: There was an error during I2C read
        */
        PatchugoStatusCode I2C_Read(uint8_t addr, uint8_t *readData, uint16_t len, uint32_t timeout);

        /**
        * @brief Writes a register of the I2C device with the given address
        * 
        * @param addr I2C address of the device
        * @param regAddr Address of the register
        * @param regAddrSize Size of the register
        * @param writeData Buffer of data to write
        * @param len Length of data to write
        * @param timeout Timeout
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: The I2C register write was successful
        * - ERROR_I2C_WRITE_REG: An error occurred during the I2C write of the register.
        */
        PatchugoStatusCode I2C_WriteReg(uint8_t addr, uint16_t regAddr, uint16_t regAddrSize, uint8_t *writeData, uint16_t len, uint32_t timeout);

        /**
        * @brief Reads a register of the I2C device with the given address
        * 
        * @param addr I2C address of the device
        * @param regAddr Address of the register
        * @param regAddrSize Size of the register
        * @param readData Buffer where read data will be put
        * @param len Length of data to read
        * @param timeout Timeout
        * @return PatchugoStatusCode PatchugoStatusCode This function can return the following values:
        * - OK: The I2C register write was successful
        * - ERROR_I2C_READ_REG: An error occurred during the I2C read of the register.
        */
        PatchugoStatusCode I2C_ReadReg(uint8_t addr, uint16_t regAddr, uint16_t regAddrSize, uint8_t *readData, uint16_t len, uint32_t timeout);

        /**
        * @brief Reads a register of the external flash chip
        * 
        * @param reg Register to read
        * @param readValue Value read from the register
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: The read was completed successfuly
        * - ERROR_FLASH_READ_REG: There was a SPI error while reading the register
        */
        PatchugoStatusCode Flash_Read_Register(uint8_t reg, uint8_t *readValue);

        /**
        * @brief Writes a signle byte instruction to the external flash chip
        * 
        * @param instruction Instruction to write
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: The instruction was written successfully
        * - ERROR_FLASH_WRITE_INSTRUCTION: There was an error with SPI communication with the flash chip
        */
        PatchugoStatusCode Flash_Write_Instruction(uint8_t instruction);

        /**
        * @brief Resets the external flash chip
        * 
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: The flash was reset successfully
        * - ERROR_FLASH_WRITE_INSTRUCTION: There was an error while writing instructions to reset the flash
        * - ERROR_FLASH_STATUS: The flash status register did not signal ok
        */
        PatchugoStatusCode Flash_Reset(void);

        /**
        * @brief Completely clears the external flash chip
        * 
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: The flash was cleared successfully
        * - ERROR_FLASH_WRITE_INSTRUCTION: There was an error while writing instructions to clear the flash
        * - ERROR_FLASH_STATUS: The flash status register did not signal ok
        */
        PatchugoStatusCode Flash_Erase(void);

        /**
        * @brief Completely clears a sector of the external flash chip
        * 
        * @param sector Sector to clear
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: The sector was cleared correctly
        * - ERROR_FLASH_WRITE_INSTRUCTION: There was an error while writing instructions to clear the sector
        * - ERROR_FLASH_SECTOR_ERASE: There was an error while erasing the sector
        * - ERROR_FLASH_STATUS: The flash status register did not signal ok
        */
        PatchugoStatusCode Flash_Erase_Sector(FlashSector sector);

        /**
        * @brief Reads data stored on the external flash chip given the sector and page to start from
        * 
        * @param sector Sector
        * @param page Page
        * @param readData Read data
        * @param len Length to read
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: The data was read successfully
        * - ERROR_FLASH_READ_DATA: There was an error while reading the data 
        */
        PatchugoStatusCode Flash_Read_Data(FlashSector sector, FlashPage page, FlashPageOffset offset, uint8_t *readData, uint32_t len);

        /**
        * @brief Writes data to the external flash chip
        * 
        * @param sector Sector
        * @param page Page
        * @param writeData Data to write 
        * @param len Length of the data to write
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: The data was written successfully
        * - ERROR_FLASH_WRITE_INSTRUCTION: There was an error while writing instruction to enable the write
        * - ERROR_FLASH_WRITE_DATA: There was an error while writing the data
        */
        PatchugoStatusCode Flash_Write_Data(FlashSector sector, FlashPage page, FlashPageOffset offset,  uint8_t *writeData, uint8_t len);

};
/**
* File: flash_manager.h
* Created on: 2025-09-04 at 10:23
* Author: Andrea Rantin
* Description: //TODO
*/

#pragma once

#include "internal/flash_manager/flash_types.h"
#include "internal/flash_manager/flash_helpers.h"

class Flash_Manager {
    private:
        static constexpr uint8_t FLASH_CMD_ENABLE_RESET = 0x66;
        static constexpr uint8_t FLASH_CMD_RESET = 0x99;
        static constexpr uint8_t FLASH_CMD_WRITE_ENB = 0x06;
        static constexpr uint8_t FLASH_CMD_ERASE_CHIP = 0xC7;
        static constexpr uint8_t FLASH_CMD_ERASE_SECTOR = 0x20;
        static constexpr uint8_t FLASH_CMD_READ_DATA = 0x03;
        static constexpr uint8_t FLASH_CMD_WRITE_PAGE = 0x02;
        static constexpr uint8_t FLASH_STATUS_REG_1 = 0x05;
        static constexpr uint8_t FLASH_CMD_LEN = 4;
        static constexpr uint32_t FLASH_CS_PIN = PA15;
        //TODO
        PatchugoStatusCode Flash_Check_Status1(void);
    public:
        /**
        * @brief Initializes the external flash chip
        * 
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: The external flash chip was initialized correctly
        * - ERROR_SPI_HAL_INIT: There was an error during low level initialization of peripherals for the flash
        */
        PatchugoStatusCode Flash_Init(void);

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
        PatchugoStatusCode Flash_Erase_Sector(Flash_Sector sector);

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
        PatchugoStatusCode Flash_Read_Data(Flash_Sector sector, Flash_Page page, uint8_t *readData, uint32_t len);

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
        PatchugoStatusCode Flash_Write_Data(Flash_Sector sector, Flash_Page page, uint8_t *writeData, uint8_t len);
};


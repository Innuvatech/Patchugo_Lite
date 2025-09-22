# Patchugo_Lite
Arduino library for PatchugoLite board

## Prerequisites
To use this library the Innuvatech PatchugoBoards board manager is necessary. To do that add the following line to Arduino preferences **https://github.com/Innuvatech/BoardManagerFiles/raw/main/package_innuvatech_index.json**. To find arduino preferences simply go in the top left corner and select **File < Preferences** Once that is done, an installation of the Patchugo boards platform must be done. To do that you can go in the Arduino boards manager and install it from there, look for a platform called **Patchugo Boards** by Innuvatech as shown in the image below

![Boards manager image](https://github.com/Innuvatech/PatchugoLite_Arduino_Manager/blob/main/docs/images/Patchugo_Boards.png)



## Library installation
To install this library into Arduino simply go in the library manager and look for a library called **Patchugo_Lite**. Once installed you can include it in your sketches from the sketches section>Include Library.
**IMPORTANT** This library cannot be used in conjuction with Arduino libraries like Wire or SPI! Including them when the PatchugoLite library header file is also included will result in undefined behaviour!!!

![Library image](https://github.com/Innuvatech/PatchugoLite_Arduino_Manager/blob/main/docs/images/Patchugo_Library.png)

## Basic Usage
Everything on the board can be controlled with this library by using the PatchugoLite class. The class provide an initialization function that initializes all peripherals of the PatchugoLite board as well as peripheral specific functionalities such as bluetooth functions, SPI, I2C and Serial management functions. In order for the library to work a Serial instance must be initialized before any call to the PatchugoLite class functions. The Init function of the PatchugoLite class automatically initializes everything with default values but if manual initialization of peripherals is needed, the library provides per-peripheral initialization 
functions like I2C_Init or SPI_Init that can be called with custom configuration parameters. **IT IS STRONGLY RECOMMENDED TO USE THE PatchugoLite Init function
INSTEAD OF MANUAL INITIALIZATION TO AVOID CONFLICTS**. A code example for peripherals initialization can be found below:
```
  void setup() {
  // put your setup code here, to run once:

  //VERY IMPORTANT!!!! CALL THIS BEFORE CALLING ANYTHING FROM PatchugoLite!!!
  Serial.begin(115200);
  /*
    Initializes the PatchugoLite board
  */
  PatchugoStatusCode checkError = patchugoLite.Init();
  if(checkError != OK) {
    Serial.println("ERROR DURING INIT");
  }

}
```
As you can see Initialization is very simple and straightforward. It is important to notice that the Init function(much like most of the functions from the library)
returns a **PatchugoStatusCode**, that is an enum value that represent status codes in all Patchugo libraries. The full list of status codes can be found in the [Patchugo_Core](https://github.com/Innuvatech/Patchugo_Core) library. In case of need status codes from all the Patchugo libraries can be converted to an interger with the **PatchugoStatusCode_ToUint** function. An example is provided below:
```
  //This will convert a PatcuhgoStatusCode to an integer(in case of OK it's 105)
  PatchugoStatusCode myCode = OK;
  uint8_t convertedCode = PatchugoStatusCode_ToUint(myCode);
  Serial.println(convertedCode);
```

## IO Pins
The PatchugoLite board has 8 24V isolated INPUT pins(U7 connector) and 8 24V isolated OUTPUT pins(U24 connector) that can be easily controlled from the library.
The pins are automatically initialized in the Init function of the library. Input pins are mapped in the **ISO_InputPin** enum class while Output pins are mapped in the **ISO_OutputPin** class. The library provide functions to read Input pins and write Output pins.

### Write output pin example

```
  //Sets OUT3 to 1
  patchugoLite.ISO_IO_Write(ISO_OUT3, SET);
```

### Read input pin example
```
  //Read IN5 and put result in readPin
  uint8_t readPin = patchugoLite.ISO_IO_Read(ISO_IN5);
```

## Serial communication
The PatchugoLite board has 2 serials that can be used to communicate:
  - RS485 Serial(U30 connector)
  - USB Serial(U16 USB connector)

Both serials are automatically initialized in the Init function of PatchugoLite with a baudrate of 115200 but each have their own initialization method that can be
called if the user wants to customize their parameters.

### RS485
This RS485 serial as specified above is automatically initialized inside the Init function of PatchugoLite but it can also be initialized by calling the **RS485_Serial_Init** function in case there's the need of a different baudrate or different configuration parameters. An example of custom initialization is provided below:

#### Basic initialization
```
  //Initializes RS485 Serial with a baudrate of 38400
  PatchugoStatusCode checkError =  patchugoLite.RS485_Serial_Init(BAUDRATE_38400);
  if(checkError != OK) {
    Serial.println("RS485 INIT ERROR");
  }
```

#### Advanced initialization(Advanced users only)
The RS485 can be initialized by providing custom advanced configuration parameters such as word length, parity, stop bits etc. **ONLY DO THIS IF YOU KNOW WHAT YOU
ARE DOING** 

```
   //Initialize RS485 Serial with a baudrate of 57600 and the provided configuration parameters
  SerialAdvConfStruct confStruct = {0};
  confStruct.wordLength = UART_WORDLENGTH_8B;
  confStruct.oversampling = UART_OVERSAMPLING_8;
  confStruct.parity = UART_PARITY_ODD;
  confStruct.stopBits = UART_STOPBITS_2;
  confStruct.mode = UART_MODE_TX_RX;

  PatchugoStatusCode checkError = patchugoLite.RS485_Serial_Init(SerialBaudRate::BAUDRATE_57600,confStruct);
  if(checkError != OK) {
    Serial.println("ERROR INIT RS485");
  }
```

#### Writing with RS485

The library provides a function that allows writing trough RS485. An example is provided below:

```
  //Writes 3 bytes trough RS485
  uint8_t myBuf[3] = {0x41, 0x42, 0x43};
  PatchugoStatusCode checkError = patchugoLite.RS485_Serial_Write(myBuf, 3);
  if(checkError != OK) {
    Serial.println("ERROR RS485 WRITE");
  }
```

#### Reading from RS485

The libraru provides a function that allows reading from RS485. An example is provided below:

```
  //Reads 3 byte in polling
  uint8_t myRead[3] = {0};

  PatchugoStatusCode checkError = patchugoLite.RS485_Serial_Read(myRead, 3, 2000);
  if(checkError != OK) {
    Serial.println("ERROR READ");
  }

  for(uint8_t i = 0; i < 3; i++) {
    Serial.println(myRead[i]);
  }
```

## I2C
The PatchugoLite has an I2C that can be used for communication with other I2C devices. The library provides a really simple API to read/write to devices in order to control them. The I2C is initialized automatically in the library Init function but can be initialized manually by providing custom
configuration parameters if necessary. 

### Writing with I2C
In order to write to a device with I2C the **I2C_Write** function must be called. The function takes the following parameters:
  - addr: The 7 bit address of the I2C device to write to
  - data: Pointer to the data to write
  - len: Length of the data to write
  - timeout: Timeout value in milliseconds after which the write request will timeout

An example of an I2C write is provided below:
```
//Define 7 bit I2C address of slave device
#define DEVICE_ADDR (0x23 << 1)

 //Write the byte 0x01 to the device
uint8_t powerOn = 0x01;
if(patchugoLite.I2C_Write(DEVICE_ADDR, &powerOn, 1, 1000) != OK) {
  Serial.println("ERROR I2C WRITE");
}
```

### Reading with I2C
In ordder to read from a device with I2C the **I2C_Read** function must be called. The function takes the following parameters:
  - addr: The 7 bit address of the I2C device to read from
  - readData: Pointer to the data that will be read
  - len: Length of the data to read
  - timeout: Timeout value in milliseconds after which the write request will timeout

  An example of an I2C read is provided below:

  ```
    //Define 7 bit I2C address of slave device
    #define DEVICE_ADDR (0x23 << 1)

    //Read 2 bytes from the device and put them into readB
    uint8_t readB[2] = {0};
    if(patchugoLite.I2C_Read(DEVICE_ADDR, readB, 2, 1000) != OK) {
      Serial.println("ERROR READ I2C");
    }

  ```

### Writing to a specific register with I2C
The library allows writing to a specific register of a given I2C slave device. In order to do that, the function **I2C_WriteReg** must be called. The funcion takes the following parameters:
  - addr: The 7 bit address of the I2C device to write to
  - regAddr: The address of the register to write
  - regAddrSize: The size in bytes of the register to write
  - writeData: Pointer to the data to write to the register
  - len: Length of the data to write
  - timeout: Timeout value in milliseconds after which the write request will timeout

An example of an I2C write to a specific register is provided below:

 ```
  //Define address of a register of slave device
  #define REG_ADDR  0x10

   //Writes 0x08 to the register
  uint8_t myValue = 0x08;
  if(patchugoLite.I2C_WriteReg(DEVICE_ADDR, REG_ADDR, 1, &myValue, 1, 1000) != OK) {
    Serial.println("ERROR I2C WRITE REG");
  }
 ```

### Reading from a specific register with I2C
The library allows reading from a specific register of a given I2C slave device. In order to do that, the function **I2C_ReadReg** must be called. The function takes the following parameters:
  - addr: The 7 bit address of the I2C device to read from
  - regAddr: The address of the register to read
  - regAddrSize: The size in bytes of the register to read
  - readData: Pointer to the data to read
  - len: Length of the data to read
  - timeout: Timeout value in milliseconds after which the write request will timeout

An example of an I2C read from a specific register is provided below:

 ```
  //Define address of a register of slave device
  #define REG_ADDR  0x10

  //Read a byte from the register and puts it in myRead
  uint8_t myRead = 0;
  if(patchugoLite.I2C_ReadReg(DEVICE_ADDR, REG_ADDR, 1, &myRead, 1, 1000) != OK) {
    Serial.println("ERROR I2C READ REG");
  }
 ```

## SPI
The PatchugoLite has a SPI that can be used to communicate with other SPI devices. The library provides a simple and clean API to read/write to other SPI devices. The SPI is initialized automatically inside the Init function of PatchugoLite with the following configuration:
  - LOW clock polarity
  - 2 EDGE clock phase
  - default advanced configuration parameters
In case different parameters are needed the **SPI_Init** function from PatchugoLite must be called. The function takes the following parameters:
  - cpol: Clock polarity
  - cpha: Clock phase
  - cfgStruct(optional): Advanced configuration parameters structure

An example of SPI init is provided below:

```
  //Initialize SPI with HIGH clock polarity and 1 EDGE detection
  if(patchugoLite.SPI_Init(SPI_CPOL_HIGH, SPI_CPHA_1EDGE) != OK) {
    Serial.println("ERROR SPI INIT");
  }
```

### CS Initializaion
In order to read/write to other SPI devices a Chip Select pin is needed. The library provides an initialization method for CS pins called **SPI_CS_Init**. 2 pins are usable as CS on the PatchugoLite, D8(CS1) and D10(CS0). An example of CS pin initialization is provided below:

```
  //Initializes CS0
  patchugoLite.SPI_CS_Init(SPI_N_CS_0);
```

### Writing with SPI
In order to write to a device with SPI the **SPI_Write** function must be called. It takes the following parameters:
  - cs: The chip select pin to use(This can either be SPI_N_CS_0 or SPI_N_CS_1)
  - writeData: Pointer to the data to write
  - len: Length of the data to write
  - Timeout value in milliseconds after which the write request will timeout

An example of SPI write is provided below:

```
//Writes 3 bytes to SPI device connected to CS0
uint8_t myWrite[3] = {0x41, 0x42, 0x43};
if(patchugoLite.SPI_Write(SPI_N_CS_0, myWrite, 3, 3000) != OK) {
  Serial.println("ERROR SPI WRITE");
}
```

### Reading with SPI
In order to read from a device with SPI the **SPI_Read** function must be called. It takes the following parameters:
 - cs: The chip select pin to use(This can either be SPI_N_CS_0 or SPI_N_CS_1)
 - readData: Pointer to the data that will be read
 - len: Length of the data to read
 - Timeout value in milliseconds after which the write request will timeout

 An example of SPI read is provided below:

 ```
//Reads 3 bytes to SPI device connected to CS0 and put them in readBuf
uint8_t readBuf[3] = {0};
if(patchugoLite.SPI_Read(SPI_N_CS_0, readBuf, 3, 3000) != OK) {
  Serial.println("ERROR SPI WRITE");
}
 ```

# Patchugo_Lite
Arduino library for PatchugoLite board

## Prerequisites
To use this library the Innuvatech PatchugoBoards board manager is necessary. To do that add the following line to Arduino preferences **https://github.com/Innuvatech/BoardManagerFiles/raw/main/package_innuvatech_index.json**. Once that is done, an installation of the Patchugo boards platform must be done. To do that you can go in the Arduino boards manager and install it from there, look for a platform called **Patchugo Boards** by Innuvatech as shown in the image below

![Boards manager image](https://github.com/Innuvatech/PatchugoLite_Arduino_Manager/blob/main/docs/images/Patchugo_Boards.png)



## Library installation
To install this library into Arduino simply go in the library manager and look for a library called **PatchugoLite_Arduino_Manager**. Once installed you can include it in your sketches from the sketches section>Include Library

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

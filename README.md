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

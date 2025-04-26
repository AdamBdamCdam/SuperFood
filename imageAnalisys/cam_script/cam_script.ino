/*
Circuit:
    - Arduino Nano 33 BLE board
    - OV7670 camera module:
      - 3.3 connected to 3.3
      - GND connected GND
      - SIOC connected to A5
      - SIOD connected to A4
      - VSYNC connected to 8
      - HREF connected to A1
      - PCLK connected to A0
      - XCLK connected to 9
      - D7 connected to 4
      - D6 connected to 6
      - D5 connected to 5
      - D4 connected to 3
      - D3 connected to 2
      - D2 connected to 0 / RX
      - D1 connected to 1 / TX
      - D0 connected to 10
*/

#include <Arduino_OV767X.h>
#include <ArduinoLowPower.h>  

long bytesPerFrame; 
long numPixels;

//data array to hold the image
byte data[320 * 240 * 2]; 

void setup() {  
  // connect to camera
  // Initialize the cam (OV7670) with res:QVGA(320x240), pixels:RGB565(2 byte rgb), fps:1
  if (!Camera.begin(QVGA, RGB565, 1)) {
    //some error handeling
    while (1);
  }
  bytesPerFrame = Camera.width() * Camera.height() * Camera.bytesPerPixel();
  numPixels = Camera.width() * Camera.height();

  //connect to output device (probably just an LED that lights when it needs harvest)
  harvestableSignalPin = LED_BUILTIN
  pinMode(harvestableSignalPin, OUTPUT)

  // initiate timings
  sleepTimerInMilliSec = 1000/*s*/*60/*m*/*60/*h*/  
}

void loop() {
  // Read frame into byte array
  Camera.readFrame(data);
  

  harvestable?(data) ? digitalWrite(harvestableSignalPin, HIGH) : digitalWrite(harvestableSignalPin, LOW) 
  if (harvestable?(data)){
    // trigger some effect on output
  }
    
  //sleep for the given time
  LowPower.sleep(sleepTimerInMilliSec);
}



bool harvestable?() {
  return false
}

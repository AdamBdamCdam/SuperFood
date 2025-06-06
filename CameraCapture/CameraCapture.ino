#include <itu-student-avad-project-1_inferencing.h>

/*
  OV767X - Camera Test Pattern

  This sketch waits for the letter 'c' on the Serial Monitor,
  it then reads a frame from the OmniVision OV7670 camera and 
  prints the data to the Serial Monitor as a hex string.

  The website https://rawpixels.net - can be used the visualize the data:
    width: 176
    height: 144
    RGB565
    Little Endian

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

  This example code is in the public domain.
*/

#include <Arduino_OV767X.h>

unsigned short pixels[176 * 144]; // QCIF: 176x144 X 2 bytes per pixel (RGB565)
int numPixels;
int T;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  T = 64;
  
  if (!Camera.begin(QCIF, RGB565, 1)) {
    Serial.println("Failed to initialize camera!");
    while (1);
  }
  numPixels = Camera.width() * Camera.height();
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);                    
  digitalWrite(LED_BUILTIN, LOW); 

  delay(2000);
//    Serial.println("Reading frame");
//    Serial.println();
    Camera.readFrame(pixels);
    //output_img(pixels);

    for (int i = 0; i < numPixels; i++) {
      unsigned short p = pixels[i];
      pixels[i] = how_green(p);
    }
    
    //output_img(pixels);
    
    for (int i = 0; i < numPixels; i++) {
      unsigned short p = pixels[i];
      pixels[i] = p > T ? 65535 : 0;
    }

    
    output_img(pixels);
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW); 
  }
}

unsigned short how_green(unsigned short pixel){
  uint8_t r = ((pixel >> 10) & 0x3E); // the same as ((pixel >> 11) & 0x1F)*2
  uint8_t g = (pixel >> 5) & 0x3F;
  uint8_t b = (pixel & 0x1F) << 1;

  uint8_t c = b < r ? b : r;
  return g > c ? g-c : 0;
}

void output_img(unsigned short pixels[]){
  for (int i = 0; i < numPixels; i++) {
    unsigned short p = pixels[i];
    Serial.print("0x");
    Serial.print(p, HEX);
    Serial.print(", ");
  }
  Serial.println();
  Serial.print("done");
}

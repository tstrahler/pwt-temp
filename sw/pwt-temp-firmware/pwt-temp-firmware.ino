#include <SparkFun_GridEYE_Arduino_Library.h>

float pixelTable[64];

GridEYE grideye;

void setup() {
  Wire.setSDA(4);
  Wire.setSCL(5);
  Wire.begin();
  
  grideye.begin(0x68);
  
  Serial.begin(115200);
}

void loop() {
  for(int i = 0; i < 64; i++){
    pixelTable[i] = 0.0;
    for(int iter = 0; iter < 8; iter++)
      pixelTable[i] += grideye.getPixelTemperature(i);
      
    pixelTable[i] /= 8.0;
  }

  
  
  for(int i = 0; i < 64; i++){
    Serial.printf("%.2f;", pixelTable[i]);
  }
  
  Serial.println();
  
  delay(50);
}

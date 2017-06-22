#include "AMG8833.h"

AMG8833 amg;
float temp[64];

void setup() {
  Serial.begin(115200);
  delay(500);
  amg.initialize();
  Serial.println("initialized");

}

void loop() {
  Serial.println("running");
  //Serial.println(amg.readThermistor());
  delay(500);
  amg.readGrid(temp);
  Serial.println("New data");
//  for(int i = 0; i<64; i++){
//    Serial.println(temp[i]);
//  }
  threshold_printer(temp, 29.0);
}

void threshold_printer(float* data, float threshold){
  char message[200];
  uint8_t count = 0;
  uint8_t element_count = 0;
  for (uint8_t x=0; x<8; x++){
    for (uint8_t y=0; y<8; y++){
      //Serial.println(data[count]);
      //Serial.println(count);
      if (data[x*8+y]>threshold) message[count] = '*';
      else message[count] = ' ';
      count ++;
      message[count]=' ';
      count++;
    }
    message[count]='\n';
    count++; 
  }
  message[count] = '\0';
  Serial.println(message);
}


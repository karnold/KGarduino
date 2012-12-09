#include <Wire.h>
#include "TSL2561.h"

TSL2561 tsl(TSL2561_ADDR_FLOAT);

int tempPin = 3;

void setup() {
  Serial.begin(9600);
  
  if (tsl.begin()) {
    Serial.println("Sensor Found");
  } else {
    Serial.println("No sensor");
    while(1);
  }
  
  tsl.setGain(TSL2561_GAIN_16X);
  tsl.setTiming(TSL2561_INTEGRATIONTIME_13MS);
}

void loop() {
  takeReadings();
  delay(3000);
  /*
  if (Serial.available() > 0) {
    int incomingByte = Serial.read();

    Serial.println(incomingByte);
    
    if (incomingByte == 49) {
      delay(100);
      takeReadings(); 
    }
  } 
  */ 
}

void takeReadings() {
  // Get luminosity reading
  uint32_t lum = tsl.getFullLuminosity();
  uint16_t ir, full;
  ir = lum >> 16;
  full = lum & 0xFFFF; 

  // Get temperature reading
  int reading = analogRead(tempPin);
  
  // Convert to voltage
  float voltage = reading * 5;
  voltage /= 1024;
  
  // Convert to celcius
  float temperatureC = (voltage - 0.5) * 100;
  
  // Convert to Fahrenheit
  float temperatureF = (temperatureC * 9 / 5) + 32;
  
  // Convert lux value
  float lux = tsl.calculateLux(full, ir);
  
  Serial.print(temperatureF);
  Serial.print(":");
  Serial.println(lux);
  
}

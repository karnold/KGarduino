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
  
  tsl.setGain(TSL2561_GAIN_0X);
  tsl.setTiming(TSL2561_INTEGRATIONTIME_13MS);
}

void loop() {
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
  
  Serial.print("Tempurature F: ");
  Serial.println(temperatureF);
  Serial.print("Lux: ");
  Serial.println(tsl.calculateLux(full, ir));
  
  delay(1000);
  
}

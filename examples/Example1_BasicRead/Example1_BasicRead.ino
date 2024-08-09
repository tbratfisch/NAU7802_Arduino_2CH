/*
 * Author: Kenneract
 * Date: Aug.9.2024
 * Sketch: Example1_BasicRead.ino
 * Source: https://github.com/Kenneract/NAU7802_Arduino_2CH
 * 
 * A simple example of how to configure the
 * NAU7802 and sample its first channel
 */

#include <Wire.h>
#include <NAU7802_2CH.h> //https://github.com/Kenneract/NAU7802_Arduino_2CH

NAU7802 nau; //Create instance of the NAU7802 class

void setup() {
  // Begin serial debugging
  Serial.begin(115200);

  // Configure the I2C bus
  Wire.begin();

  // Initialize to NAU7802
  if (!nau.begin(Wire, true)) {
    Serial.println("NAU7802 not detected; freezing.");
    while (1);
  }//if
  Serial.println("NAU7802 detected!");

  // Ensure correct settings are being used
  nau.setChannel(NAU7802_CHANNEL_1);
  nau.setPGACapEnable(false);
  nau.setBypassPGA(true);
  nau.setLDO(NAU7802_LDO_3V3);
  nau.setSampleRate(NAU7802_SPS_20);

  // Calibrate Analog Front End (AFE) after major changes
  nau.calibrateAFE();  
  
}//setup()

void loop() {
  // Print out all readings
  if (nau.available()) {
    Serial.print("NAU7802 CH1: ");
    Serial.println(nau.getReading());
  }//if
}//loop()

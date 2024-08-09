/*
 * Author: Kenneract
 * Date: Aug.9.2024
 * Sketch: Example2_DualChannelReadings.ino
 * Source: https://github.com/Kenneract/NAU7802_Arduino_2CH
 * 
 * An example of how to read data from both
 * channels on the NAU7802. Note that, for
 * best results, you should re-calibrate the
 * AFE before taking a reading once you switch
 * channels.
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
  nau.setSampleRate(NAU7802_SPS_40);

  // Calibrate Analog Front End (AFE) after major changes
  nau.calibrateAFE();
  
}//setup()

void loop() {
  
  // Select and read Channel 1
  nau.setChannel(NAU7802_CHANNEL_1);
  while (!nau.available()) {}
  Serial.print("NAU7802 CH1: ");
  Serial.print(nau.getReading());

  // Select and read Channel 2
  nau.setChannel(NAU7802_CHANNEL_2);
  while (!nau.available()) {}
  Serial.print(", CH2: ");
  Serial.print(nau.getReading());
  Serial.println();

}//loop()

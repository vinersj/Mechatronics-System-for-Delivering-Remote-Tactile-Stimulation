/*
 * Version one for simplified model of wearable sensor system sketch
 * Author: Sophia Viner
 * Date: 5/15/2020
 * 
 * Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
 */

 #include <SPI.h>
 #include <nRF24L01.h>
 #include <RF24.h>

 RF24 radio(7,8); // CNS, CE
 
 const byte address[6] = "00001";
 const int sensorPin = A0;
 const float baselineTemp = 27.0;
 

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN); // set to max and use capacitor for long distances
  radio.stopListening();

  Serial.begin(9600); // for temperature sensor
}

void loop() {
  int sensorVal = analogRead(sensorPin); // to read from temperature sensor

  Serial.print("Sensor Value: ");
  Serial.print(sensorVal);

  float voltage = (sensorVal/1024.0)*5.0;
  Serial.print(", Volts: ");
  Serial.print(voltage);

  float temperature = (voltage - 0.5)*100;
  Serial.print(", degrees C: ");
  Serial.println(temperature);

  bool vibrate = false;
  if(temperature > baselineTemp){
    vibrate = true;
  }

  radio.write(&vibrate, sizeof(vibrate)); // send yes or no to reciever device
  delay(1000);
}

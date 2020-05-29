/*
 * Version one for reciever/tactile stimulation device sketch
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

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0,address);
  radio.setPALevel(RF24_PA_MIN); // set to max and use capacitor for long distances
  radio.startListening();

  pinMode(3, OUTPUT); //set motor pins
  pinMode(5, OUTPUT);
}

void loop() {
  bool vibrate = false;
  if(radio.available()){
    radio.read(&vibrate, sizeof(vibrate));
    Serial.println(vibrate);
  } else {
    Serial.println("No radio signal");
  }
  if(vibrate){
    digitalWrite(3,HIGH);
    digitalWrite(5,HIGH);
    delay(1000);
    digitalWrite(3,LOW);
    digitalWrite(5,LOW);
    delay(500);
    digitalWrite(3,HIGH);
    delay(250);
    digitalWrite(3,LOW);
    delay(250);
    digitalWrite(3,HIGH);
    delay(250);
    digitalWrite(3,LOW);
    delay(250);
  }
  else{
    digitalWrite(3,LOW);
    digitalWrite(5,LOW);
  }
  delay(1000);
}

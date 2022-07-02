#include <SoftwareSerial.h>

//SoftwareSerial mySerial(19, 18); // RX, TX  
// Connect HM10      Arduino Uno
//     TXD          Pin 7
//     RXD          Pin 8

void setup() {  
  Serial.begin(9600);
    pinMode(7, OUTPUT); // onboard LED
  digitalWrite(7, HIGH); 
  // If the baudrate of the HM-10 module has been updated,
  // you may need to change 9600 by another value
  // Once you have found the correct baudrate,
  // you can update it using AT+BAUDx command 
  // e.g. AT+BAUD0 for 9600 bauds
  Serial1.begin(9600);
}

void loop() {  
  String c;
  if (Serial.available()) {
    Serial.print("shit");
    delay(500);
    c = Serial.read();
    Serial1.print(c);
  }
  if (Serial1.available()) {
    Serial.print("Fuck");
    
    delay(500);
 
    c = Serial1.read();
    if (c=="Slow"){    digitalWrite(7, LOW); 
    delay(1000);
    digitalWrite(7, HIGH);}
    Serial.print(c);    
  }
}

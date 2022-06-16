#include <SoftwareSerial.h>
SoftwareSerial HM10(19, 18); // RX = 19, TX = 18
int ledpin=13;
int ACrun=2;
int ACslow=3;
int ACfast=4;

char appData;
int unlock=5;
int ACstatus=0;
String inData = "";
void setup(){
  pinMode(ACrun, OUTPUT);
  pinMode(ACslow, OUTPUT);
  pinMode(ACfast, OUTPUT);
  pinMode(unlock, OUTPUT);
  digitalWrite(ACrun,HIGH);
  digitalWrite(ACslow,HIGH);
  digitalWrite(ACfast,HIGH);
  digitalWrite(unlock,HIGH);
  
  Serial1.begin(9600);
  Serial.begin(3600);
  Serial.println("HM10 serial started at 9600");
  HM10.begin(9600); 
  delay(100);
  
  pinMode(ledpin,OUTPUT);
 // Serial.print("init");
//  Serial1.print("AT+RENEW");
  ACstatus=0;
}
void loop(){
//  digitalWrite(ACrun,HIGH);
//  delay(2000);
//  digitalWrite(ACrun,LOW);
//  delay(2000);
//  digitalWrite(ACrun,);
  //delay(2000);

 // Serial.println("DATA RECEIVED:"); 
  HM10.listen();  // listen the HM10 port
  while (HM10.available() > 0) {   // if HM10 sends something then read
    appData = HM10.read();
    inData = String(appData);  // save the data in string format
    Serial.write(appData);
  }
    if (Serial.available()) {           // Read user input if available.

    delay(10);

    HM10.write(Serial.read());

  }
    //Serial.print((char)Serial1.read());  
    //Serial1.println("DATA RECEIVED:");

    if(inData=="SLOW"){
     
      if(ACstatus==0){
        
        digitalWrite(ACrun,1);
        digitalWrite(ACslow,1);
        ACstatus=2;
      }
      if(ACstatus==1){
       digitalWrite(ACslow,1);
       ACstatus=2;
      }
      if(ACstatus==3){
       digitalWrite(ACfast,0);
       ACstatus=2;
      }
    }
     if(inData=='FAST'){
      
      if(ACstatus==0){
        digitalWrite(ACrun,1);
        digitalWrite(ACslow,1);
        digitalWrite(ACfast,1);
        ACstatus=1;
      }
      if(ACstatus==1){
        digitalWrite(ACslow,1);
        digitalWrite(ACfast,1);
      }
      if(ACstatus==2){
        digitalWrite(ACfast,1);
      }
  
    }
//    if(i=="ACoff"){
//      digitalWrite(ACrun,0);
//      digitalWrite(ACslow,0);
//      digitalWrite(ACfast,0);
//      ACstatus=0;
//    }
    if(inData=='N')
    {
      
      digitalWrite(ledpin,1);
      Serial.println("led on");
    }
    if(inData=='F')
    {
      digitalWrite(ledpin,0);
      Serial.println("led off");
    }
  }

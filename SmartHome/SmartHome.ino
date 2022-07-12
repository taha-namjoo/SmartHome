#include <SoftwareSerial.h>

///////////////////////////////////////////////////////////////////////////Initialize/////////////////////////////////////
int ledpin=13;
int ACrun=2;
int ACslow=3;
int ACfast=4;
int fpot=5;
int lamp=6;
int lock=7;
int Humid_Temp=23;
char appData;
char appData2;
int ACstatus=0;
String inData = "";
String wifi_Text="";
String wifiTemp="";


//////////////////////////////////////////////////////////                                 Descision  WIFI

  void decisionWiFi(String Topic,String Value){
      Serial.println("Topic: "+Topic);
      Serial.println("Value: "+Value);
      
     if(Topic=="AC"&&Value=="0"){   
    digitalWrite(ACrun,1);
  
    digitalWrite(ACslow,1);
    digitalWrite(ACfast,1);
    ACstatus=0;
    Serial.print("temp=");
    Serial.print(Humid_Temp);
  }
  if(Topic=="ACpump"&&Value=="0"){   
    digitalWrite(ACrun,1);
  
    digitalWrite(ACslow,1);
    digitalWrite(ACfast,1);
    ACstatus=0;
    Serial.print("temp=");
    Serial.print(Humid_Temp);
  }
  if(Topic=="ACpump"&&Value=="1"){
      
  
        digitalWrite(ACrun,0);
        digitalWrite(ACslow,1);
        digitalWrite(ACfast,1);

     if(Topic=="ACmotor"&&Value=="0"){
      
  
        digitalWrite(ACrun,0);
        digitalWrite(ACslow,1);
        digitalWrite(ACfast,1);

    if(Topic=="ACmotor"&&Value=="1"){
     
        digitalWrite(ACslow,0);
        Serial.print("temp=");
        Serial.print(Humid_Temp);     
    } 
    if(Topic=="ACspeed"&&Value=="0"){
      
      digitalWrite(ACfast,1);
      Serial.print("temp=");
      Serial.print(Humid_Temp); 
    }
    if(Topic=="ACspeed"&&Value=="1"){
      
      digitalWrite(ACfast,0);
      Serial.print("temp=");
      Serial.print(Humid_Temp); 
    }
    if(Topic=="doorLock"&&Value=="L")
    {
      digitalWrite(lock,0);
      delay(1500);
      digitalWrite(lock,1);
      
    }
     if(Topic=="lamp"&&Value=="0"){

      digitalWrite(lamp,1);
     
    }
    if(Topic=="lamp"&&Value=="1"){

      digitalWrite(lamp,0);
    }
    
    
}

////////////////////////////////////////////////////////////////                 Decision BlueTooth

  void decisionBlu(){

      
      if(appData=='A' ){   
    digitalWrite(ACrun,1);
  
    digitalWrite(ACslow,1);
    digitalWrite(ACfast,1);
    ACstatus=0;
    Serial.print("temp=");
    Serial.print(Humid_Temp);
  }
  if(appData=='P' ){
      
      if(ACstatus==0){
        digitalWrite(ACrun,0);
        digitalWrite(ACslow,1);
        digitalWrite(ACfast,1);
        ACstatus=1;
      }
      if(ACstatus==1){
        digitalWrite(ACrun,0);
        digitalWrite(ACslow,1);
        digitalWrite(ACfast,1);
        ACstatus=1;
      }
      if(ACstatus==2){
        digitalWrite(ACrun,0);
        digitalWrite(ACslow,1);
        digitalWrite(ACfast,1);
        ACstatus=1;
      }
      if(ACstatus==3){
        digitalWrite(ACrun,0);
        digitalWrite(ACslow,1);
        digitalWrite(ACfast,1);
        ACstatus=1;
      }
        Serial.print("temp=");
        Serial.print(Humid_Temp);
  
    }
    if(appData=='S'){
     
      if(ACstatus==0){
        digitalWrite(ACrun,0);
        delay(1000);
        digitalWrite(ACslow,0);
        digitalWrite(ACfast,1);
        ACstatus=2;
      }
      if(ACstatus==1){
        digitalWrite(ACrun,0);
        digitalWrite(ACslow,0);
        digitalWrite(ACfast,1);
        ACstatus=2;
      }
      if(ACstatus==2){
        digitalWrite(ACrun,0);
        digitalWrite(ACslow,0);
        digitalWrite(ACfast,1);
        ACstatus=2;
      }
      if(ACstatus==3){
        digitalWrite(ACrun,0);
        digitalWrite(ACslow,0);
        digitalWrite(ACfast,1);
        ACstatus=2;
      }
        Serial.print("temp=");
        Serial.print(Humid_Temp);      
    }
    if(appData=='F'){
      
      if(ACstatus==0){
        digitalWrite(ACrun,0);
        delay(1000);
        digitalWrite(ACslow,0);
        delay(500);
        digitalWrite(ACfast,0);
        ACstatus=3;
      }
      if(ACstatus==1){
        digitalWrite(ACrun,0);
        digitalWrite(ACslow,0);
        delay(500);
        digitalWrite(ACfast,0);
        ACstatus=3;
      }
      if(ACstatus==2){
        digitalWrite(ACrun,0);
        digitalWrite(ACslow,0);
        digitalWrite(ACfast,0);
        ACstatus=3;
      }
      if(ACstatus==3){
        digitalWrite(ACrun,0);
        digitalWrite(ACslow,0);
        digitalWrite(ACfast,0);
        ACstatus=3;
      }
      Serial.print("temp=");
      Serial.print(Humid_Temp); 
    }
    if(appData=='D')
    {
      digitalWrite(lock,0);
      delay(1500);
      digitalWrite(lock,1);
      appData="";
      
    }
     if(appData=='N'){
      digitalWrite(lamp,0);
      appData="";
    }
    if(appData=='O'){
     
      digitalWrite(lamp,1);
      appData="";
    }
    
    
    
}

////////////////////////////////////////////////////// Serial Get
void serialGet(){
 // Serial.println("get");
  if(Serial2.available()){
  char c=Serial2.read();
//  Serial.print(c);
    if(c=='<' || wifiTemp!=""){
      wifiTemp+=c;
       
      
      
      }
      if(wifiTemp!="" && c!='>'){
        wifi_Text+=c;
      }

        
        decision(wifi_Text.substring(0,wifi_Text.indexOf(':')),wifi_Text.substring(wifi_Text.indexOf(':'),wifi_Text.length()-1));
        wifiTemp="";
        wifi_Text="";
       }
    }
  
  
//////////////////////////////////////////   SETUP

void setup(){
  pinMode(ACrun, OUTPUT);
  pinMode(ACslow, OUTPUT);
  pinMode(ACfast, OUTPUT);
  pinMode(fpot, OUTPUT);
  pinMode(lamp, OUTPUT);
  pinMode(lock, OUTPUT);
  
  digitalWrite(ACrun,HIGH);
  digitalWrite(ACslow,HIGH);
  digitalWrite(ACfast,HIGH);
  digitalWrite(fpot,HIGH);
  digitalWrite(lamp,HIGH);
  digitalWrite(lock,HIGH);
  
  Serial1.begin(9600);
  Serial.begin(9600);
  Serial2.begin(115200);
  Serial.println("HM10 serial started at 9600");
  delay(100);
  
  pinMode(ledpin,OUTPUT);
  ACstatus=0;
}

///////////////////////////////////////////   LOOP
void loop(){
  delay(500);
  int soil_moisture=analogRead(A0); 
  Serial.print("analog value: ");
  Serial.println(soil_moisture);
////////////////////////////////////////////// Flower Pot pump
  if(soil_moisture<30) {

    Serial.println("Dry soil");

  }

  if((soil_moisture>300)&&(soil_moisture<700)) {

    Serial.println("Humid soil");

  }

  if((soil_moisture>700)&&(soil_moisture<950)){
    Serial.println("water");
    digitalWrite(6,LOW);
  }

/////////////////////////////////////////////////////////////           BlueTooth and Wifi Read

  if (Serial1.available()) {           // Read user input if available  from Bluetooth
    delay(100);

    
    delay(100);
    appData=Serial1.read();
    //Serial.write(appData);
    decisionBlu();

  }

  serialGet();
  
}

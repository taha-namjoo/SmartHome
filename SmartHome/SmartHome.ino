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
      if(c=='>'){
//        char** d=strtok(wifi_Text.c_str(),':');
//        Serial.println("d[0]: " + d[0]);
//        Serial.println("d[1]: " + d[1]);
        
        decision(wifi_Text.substring(0,wifi_Text.indexOf(':')),wifi_Text.substring(wifi_Text.indexOf(':'),wifi_Text.length()-1));
        wifiTemp="";
        wifi_Text="";
       }
    }
  
  }

//////////////////////////////////////////////////////////                                 Descision

  void decision(String Topic,String Value){
      Serial.println("Topic: "+Topic);
      Serial.println("Value: "+Value);
      
      if(appData=='N' || appData2=="AcOff"){   
    digitalWrite(ACrun,1);
  
    digitalWrite(ACslow,1);
    digitalWrite(ACfast,1);
    ACstatus=0;
    Serial.print("temp=");
    Serial.print(Humid_Temp);
  }
  if(appData=='R' || appData2=="AcRun"){
      
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
    if(appData=='S'|| appData2=="AcSlow"){
     
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
    if(appData=='F' || appData2=="AcFast"){
      
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
    //if(appData=='O' || appData2=="LockOpen")
    if(Topic=="doorLock" && Value=="L"){
      digitalWrite(lock,0);
      delay(1500);
      digitalWrite(lock,1);
      appData="";
      
    }
     if(appData=='L' || appData2=="LampOn"){
      digitalWrite(lamp,0);
      delay(1500);
      digitalWrite(lamp,1);
      appData="";
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
//  Serial.print("analog value: ");
//  Serial.println(soil_moisture);

  if(soil_moisture<30) {

//    Serial.println("Dry soil");

  }

  if((soil_moisture>300)&&(soil_moisture<700)) {

//    Serial.println("Humid soil");

  }

  if((soil_moisture>700)&&(soil_moisture<950)){
    Serial.println("water");
    digitalWrite(6,LOW);
  }

/////////////////////////////////////////////////////////////

  if (Serial1.available()) {           // Read user input if available  from Bluetooth
    delay(100);

    
   // delay(100);
    appData=Serial1.read();
    Serial.write(appData);

  }

  serialGet();
  
}

////
//#include <AltSoftSerial.h>
//
//AltSoftSerial bluetoothSerial;
//
//boolean NL = true;
//
//void setup() {
//
//Serial.begin(9600);
//
//while (!Serial) ;
//
//bluetoothSerial.begin(9600);
//
//}
//
//
//
//
//void loop() {
//
//char Serialdata;
//
//
//
//
//if (Serial.available()) {
//
//Serialdata = Serial.read();
//
//bluetoothSerial.print(Serialdata);
//
//
//
//
//if (Serialdata!=10 & Serialdata!=13 )
//
//{
//
//bluetoothSerial.write(Serialdata);
//
//}
//
//if (NL) { Serial.print("\r\n>"); NL = false; }
//
//Serial.write(Serialdata);
//
//if (Serialdata==10) { NL = true; }
//
//}
//
//if (bluetoothSerial.available()) {
//
//Serialdata = bluetoothSerial.read();
//
//Serial.print(Serialdata);
//
//}
//
//}
//////////////////////////////////////////////////////////////
#include <SoftwareSerial.h>

SoftwareSerial HM10(2, 3); // RX = 2, TX = 3

char appData;  

String inData = "";

void setup()

{

  Serial.begin(9600);

  Serial.println("HM10 serial started at 9600");

  HM10.begin(9600); // set HM10 serial at 9600 baud rate

  pinMode(13, OUTPUT); // onboard LED

  digitalWrite(13, LOW); // switch OFF LED


}


void loop()

{

  HM10.listen();  // listen the HM10 port

  while (HM10.available() > 0) {   // if HM10 sends something then read

    appData = HM10.read();

    inData = String(appData);  // save the data in string format

    Serial.write(appData);

  }
//
//
// 
//
  if (Serial.available()) {           // Read user input if available.

    delay(10);

    HM10.write(Serial.read());

  }

  if ( inData == "0") {

    Serial.println("LED OFF");

    digitalWrite(13, LOW); // switch OFF LED

    delay(500);

  }

  if ( inData == " ") {

    Serial.println("LED ON");

    digitalWrite(13, HIGH); // switch OFF LED

    delay(500);

    digitalWrite(13, LOW); // switch OFF LED

    delay(500);

  }

}
//void setup(){
//  Serial.begin(9600);
//  
//  Serial3.begin(9600); // default baud rate
//
//  pinMode(LED_BUILTIN,OUTPUT);
//  
//  delay(250);
//  
//  Serial.println("AT commands: ");
//
//  delay(250);
//      
//}
//
//void loop(){
//  //read from the HM-10 and print in the Serial
//  if(Serial3.available())
//    Serial.write(Serial3.read());
//   
//  //read from the Serial and print to the HM-10
//  if(Serial.available())
//    Serial3.write(Serial.read());
//
//
////use AT+LADDR to read address
//
//}
//void setup(){
//
//Serial.begin(9600);
//pinMode(6, OUTPUT);
//}
//
//void loop(){
//delay(500);
//digitalWrite(6, LOW);
//int soil_moisture=analogRead(A0);  // read from analog pin A3
//
//Serial.print("analog value: ");
//Serial.println(soil_moisture);
//
//if(soil_moisture<30) {
//
//Serial.println("Dry soil");
//
//}
//
//if((soil_moisture>300)&&(soil_moisture<700)) {
//
//Serial.println("Humid soil");
//
//}
//
//if((soil_moisture>700)&&(soil_moisture<950)){
//  Serial.println("water");
//  digitalWrite(6, HIGH);
//  }
//
//}
/*
USB(mega2560)-to-BLE sketch
Apploader project
http://www.apploader.info
Anton Smirnov
2015
Note:
  HM-10 applies baud rate set in 'AT+BAUD' after switch off and on
////*/
////
//#include <SoftwareSerial.h>
//
//SoftwareSerial HM10(2, 3); // RX = 2, TX = 3
//int led = 13;
//int ledHIGH = 0;
//
//long bauds[] = {
//    // major 
//    9600, 57600, 115200,
//    
//    // others
//    19200, 38400, 4800, 2400, 1200, 230400
//  };
//
//bool detectBleBaudRate() {
//  Serial.println("Detecting BLE baud rate:");
//  for (int i=0; i<(sizeof(bauds)/sizeof(long)); i++) {
//    Serial.write("Checking ");
//    long cur_baud = bauds[i];
//    Serial.println(cur_baud, DEC);
//    
//    HM10.begin(cur_baud);
//    HM10.write("AT");
//    HM10.flush();
//    delay(50);
//    String response = HM10.readString();
//    if (response == "OK") {
//      Serial.println("Detected");
//      return true;
//    } else {
//      HM10.end();
//    }
//  }
//  return false;
//}
//
//void setup() {
//  // init
//  Serial.begin(115200);  // USB (choose 115200 in terminal)
//  
//  if (detectBleBaudRate())
//    Serial.write("Ready, type AT commands\n\n");
//  else
//    Serial.write("Not ready. Halt");
//  
//  pinMode(led, OUTPUT);
//}
//
//void loop() {
//  // read from BLE (HM-10)
//  if (HM10.available()) {
//    Serial.write("ble: ");
//    String str = HM10.readString();
//    Serial.print(str);
//    Serial.write('\n');
//  }
//
//  // read from USB (Arduino Terminal)
//  if (Serial.available()) {
//    Serial.write("usb: ");
//    String str = Serial.readString();
//    HM10.print(str);
//    Serial.print(str);
//    Serial.write('\n');
//  }
//}

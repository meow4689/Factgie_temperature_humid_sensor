#include <SoftwareSerial.h>
// read command
byte message[8] ={0x01,0x03,0x00,0x00,0x00,0x02,0xC4,0x0B};
byte incomingStream[8];
//Software Serial Port 
const byte rxPin = 2;
const byte txPin = 3;
const int enPin = 4;
byte temp[2];
byte humid[2];
float f_temp;
float f_humid;

SoftwareSerial mySerial (rxPin, txPin);

void setup() {
  // put your setup code here, to run once:
      pinMode(rxPin, INPUT);
    pinMode(txPin, OUTPUT);
    pinMode(enPin,OUTPUT);
    
  Serial.begin(9600);
  mySerial.begin(4800);
  delay(500);

}

void loop() {
  //enable TX 
    digitalWrite(enPin,HIGH);
  for (int i = 0; i <8; i++) {
      Serial.print(message[i],HEX);
      mySerial.write(message[i]);
  }
  //enable RX
    digitalWrite(enPin,LOW);
    Serial.println();
    int i = 0;
    while(mySerial.available()>0){
      incomingStream[i] =mySerial.read();
      if(i==3){
          humid[0] = incomingStream[i];


      }
      if(i==4){
          humid[1] = incomingStream[i];
 
      }
            if(i==5){
          temp[0] = incomingStream[i];

      }
            if(i==6){
          temp[1] = incomingStream[i];
           
      }
      Serial.print(incomingStream[i],HEX);
      i++;
  }

  // HEX conversion
      f_humid = (humid[0]*(16^2)+humid[1]);
      f_temp = (temp[0]*(16^2)+temp[1]);
      /*
        Serial.println();
        Serial.print(humid[0]);
        Serial.print(humid[1]);
        Serial.println();
        Serial.print(temp[0]);
        Serial.print(temp[1]);
        
        Serial.println();
        */
        //data /10 = result
        Serial.println(f_humid/10);
        Serial.println(f_temp/10);
        Serial.println();
        
   delay(500);


  // put your main code here, to run repeatedly:

}

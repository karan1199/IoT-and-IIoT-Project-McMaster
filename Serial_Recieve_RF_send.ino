#include <SPI.h>
#include "RF24.h"
RF24 radio(9, 10);   
String nom = "Arduino";
String msg;
const byte addresses[6] = "Free1";
int dataWrite[8];               
void setup() {
  Serial.begin(9600);
  Serial.setTimeout(1);
 radio.begin();                      // initialize RF24
  radio.setPALevel(RF24_PA_MAX);      // set power amplifier (PA) level
  radio.setDataRate(RF24_1MBPS);      // set data rate through the air
  radio.setRetries(0, 15);            // set the number and delay of retries
  radio.openWritingPipe(addresses);   // open a pipe for writing
  radio.openReadingPipe(1, addresses);// open a pipe for reading
  radio.stopListening();       
}

void loop() {
  readSerialPort();

  if (msg != "") {
    sendData();
  }
  delay(500);
}

void readSerialPort() {
  msg = "";
  if (Serial.available()) {
    delay(10);
    while (Serial.available() > 0) {
      msg += (char)Serial.read();
    }
    Serial.flush();
  }
}

void sendData() {
  //write data
  Serial.print(nom);
  Serial.print(" received : ");
  int a = msg.toInt();
  int ind1 = msg.indexOf(' '); 
     dataWrite[0] = msg.substring(0, ind1).toInt();
   int   ind2 = msg.indexOf(' ', ind1+1 ); 
      dataWrite[1] = msg.substring(ind1+1, ind2+1).toInt();  
    int  ind3 = msg.indexOf(' ', ind2+1 );
       dataWrite[2] = msg.substring(ind2+1, ind3+1).toInt();
   int ind4 = msg.indexOf(' ', ind3+1 );
     dataWrite[3] = msg.substring(ind3+1,ind4+1).toInt();
    int   ind5 = msg.indexOf(' ', ind4+1 );
      dataWrite[4] = msg.substring(ind4+1).toInt();
  //Serial.print(light);
  radio.writeFast(&dataWrite, sizeof(dataWrite));
}

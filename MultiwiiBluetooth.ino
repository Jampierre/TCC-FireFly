#include <SoftwareSerial.h>

#define Reset 4
#define LED 13
SoftwareSerial BTserial(2,3);

int count=0;     // counter for buffer  array
String buffer; // buffer array for data recieve over serial port

void setup() {
  // initialize the digital pin as an output.
  pinMode(LED, OUTPUT);
  pinMode(Reset, OUTPUT);
  Serial.begin(9600);
  BTserial.begin(9600);
  digitalWrite(Reset, LOW);
  digitalWrite(LED, LOW);

}

// the loop routine runs over and over again forever:
void loop() {

  readBT();
  count = 0;                       // set counter of while loop to zero
  buffer = "";  // clear all index of array with command NULL
  writeBT();

}

void readBT(){

  int i = 0;
  while (BTserial.available()) // if date from softwareserial Bt module
  {
    if(BTserial.available() >0) // reading data into char array 
    {
      count++;
      char c = BTserial.read();
      buffer += c;
    }
  }
  Serial.print(buffer);
}

void writeBT(){

  if (Serial.available())  // if data on hardwareserial port PC or notebook

    BTserial.write(Serial.read());  // write it to the BT module
}

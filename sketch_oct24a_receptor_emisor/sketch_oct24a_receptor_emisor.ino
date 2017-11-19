#include <SoftwareSerial.h>
#include <VirtualWire.h>

SoftwareSerial mySerial(8, 9); // RX, TX

const int dataPin=7;
const int ledPin=13;
uint8_t data;
uint8_t dataLength=1;

void setup() {

  vw_setup(2000);
  vw_set_rx_pin(dataPin);
  vw_rx_start();
  
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,false);
  Serial.begin(9600);

  mySerial.begin(9600);
  
}

void loop() {
  
  if (vw_get_message(&data, &dataLength)) {

    mySerial.print((char)data);
    
    digitalWrite(ledPin, true);
    delay(125);
    digitalWrite(ledPin, false);

    Serial.println((char)data);
  
  }

}

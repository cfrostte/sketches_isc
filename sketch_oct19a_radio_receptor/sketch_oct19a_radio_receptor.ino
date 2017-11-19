#include <SoftwareSerial.h>
#include <VirtualWire.h>

SoftwareSerial mySerial(2, 3); // RX, TX

const int dataPin=9;
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

  mySerial.begin(4800);
  
}

void loop() {

  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }

  float analogo = analogRead(A0);
  float voltaje = (analogo*5)/1023;
  
//  Serial.println(voltaje);

  if (vw_get_message(&data, &dataLength)) {
    
    if ((char)data == 'a') {      
      digitalWrite(ledPin, true);
    } else if ((char)data == 'b') {
      digitalWrite(ledPin,false);
    }
  
  }

}

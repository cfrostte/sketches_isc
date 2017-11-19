/* 
 *  ENVIAR pulsos recibidos por la PC, hacia otra Arduino 
*/

#include <SoftwareSerial.h>
#include <VirtualWire.h>

SoftwareSerial mySerial(3, 4); // RX, TX

void setup() {
  Serial.begin(9600); // Recibo de la PC
  mySerial.begin(9600); // Envio a la Arduino
}

void loop() {

  if (Serial.available()>0) {
      char para_nodo1 = Serial.read();
      mySerial.print(para_nodo1);
  }
  
  if (mySerial.available()>0) {
      char para_nodo = mySerial.read();
      Serial.print(para_nodo);
  }
  
}

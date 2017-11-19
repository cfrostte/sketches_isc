#include <SoftwareSerial.h>

SoftwareSerial mySerial(7, 5);

int led = 2;

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  
  if (mySerial.available()>0) {
    char dato = mySerial.read();
    Serial.println(dato);
    if (dato=='a') digitalWrite(led, HIGH);
    if (dato=='b') digitalWrite(led, LOW); 
  }

}

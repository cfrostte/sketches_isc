/* 
 *  Mover servomotores en funcion del estado de los leds
 *  que a su vez son controlados por interruptores
*/

// Estado de pines:
int estado1;
int estado2;

// Pines comunes:
int rojo = 5;
int verde = 7;

#include <Servo.h>

Servo miservo1;
Servo miservo2;

// Pines especiales:
int nro_pin_pwn_1 = 3;
int nro_pin_pwn_2 = 10;

int pot1;
int pot2;

void setup() {
  
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(rojo, OUTPUT);
  pinMode(verde, OUTPUT);
  
  miservo1.attach(nro_pin_pwn_1);
  miservo2.attach(nro_pin_pwn_2);
  
  Serial.begin(9600);
  
}

void loop() {
  
  estado1 = digitalRead(0);
  estado2 = digitalRead(1);
  
  Serial.println(estado2);
  
  if (estado1==0) {
    digitalWrite(verde, LOW);
    digitalWrite(rojo, HIGH);
    delay(1000);
    digitalWrite(rojo, LOW);
    delay(1000);
  }
  
  if (estado1==1) {
    
    digitalWrite(verde, HIGH);
    digitalWrite(rojo, LOW);
    
    if (estado2==0) {
      
      pot1 = analogRead(A0); 
      pot2 = analogRead(A5);
      
      miservo1.write(map(pot1,0,1023,0,180));
      miservo2.write(map(pot2,0,1023,0,180));
    
    } else {
      
      // Girar los 180 grados del servo:
      for (int i=0; i<=180; i++) {
        miservo1.write(i);
        delay(50);
      }
    
    }
    
  }
  
}

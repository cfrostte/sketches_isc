/* 
 *  Manejar servomotores con un potenciometro 
*/

#include <Servo.h>

// Servomotores:
Servo miservo1;
Servo miservo2;

// Pines con la marca "~"
int nro_pin_pwn_1 = 3;
int nro_pin_pwn_2 = 10;

// Potenciometros:
int pot1;
int pot2;

void setup() {
  
  // Adjuntar servos a pines:  
  miservo1.attach(nro_pin_pwn_1);
  miservo2.attach(nro_pin_pwn_2);
  
  Serial.begin(9600);

}

void loop() {

  // Valores de potenciometros:
  pot1 = analogRead(A0); 
  pot2 = analogRead(A5);

  // Mover servos segun valores mapeados:
  miservo1.write(map(pot1, 0, 1023, 0, 180));
  miservo2.write(map(pot2, 0, 1023, 0, 180));
  
  Serial.print("pot1=");
  Serial.print(pot1);
  
  Serial.println();
  
  Serial.print("pot2=");
  Serial.print(pot2);
  Serial.println();

}


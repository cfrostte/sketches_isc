/* 
 *  Hacer un semaforo con 3 leds 
*/

// Numeros de pines a utilizar:
int rojo = 1;
int amarillo = 2;
int verde = 3;

void setup() {

  // Los pines emitiran pulsos:
  pinMode(rojo, OUTPUT);
  pinMode(amarillo, OUTPUT);
  pinMode(verde, OUTPUT);

}

void loop() {

  // Se encendera uno a la vez:    
  
  digitalWrite(rojo, HIGH);
  delay(3000);
  digitalWrite(rojo, LOW);
  
  digitalWrite(amarillo, HIGH);
  delay(1000);
  digitalWrite(amarillo, LOW);
  
  digitalWrite(verde, HIGH);
  delay(2000);
  digitalWrite(verde, LOW);

}

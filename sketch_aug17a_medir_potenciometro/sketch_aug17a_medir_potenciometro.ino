/* 
 *  Medir valores discretizados de un potenciometro 
*/

int pines[3];
int valorPotenciometro;

void setup() {
  
  pines[0] = 5;
  pines[1] = 6;
  pines[2] = 7;
  
  pinMode(pines[0], OUTPUT);
  pinMode(pines[1], OUTPUT);
  pinMode(pines[2], OUTPUT);
  
  Serial.begin(9600); 
  
}

void loop() {

  // Leer valores del potenciometro:
  valorPotenciometro = analogRead(A0);
  Serial.println(valorPotenciometro);
  
  encender(pines[0], valorPotenciometro);
  encender(pines[1], valorPotenciometro);
  encender(pines[2], valorPotenciometro);
  
}

// Pulsar un pin en funcion de un delay:
void encender(int pin, int retraso) {
  digitalWrite(pin, HIGH);
  delay(retraso);
  digitalWrite(pin, LOW);
}


/* 
 *  RECIBIR pulsos enviados desde otra Arduino 
*/

int pines[3];
bool encendido = false;
bool enviado = false;

void setup() {
  
  pines[0] = 2;
  pines[1] = 3;
  pines[2] = 4;
  
  pinMode(pines[0], OUTPUT);
  pinMode(pines[1], OUTPUT);
  pinMode(pines[2], OUTPUT);  

  Serial1.begin(9600);

}

void loop() {
  
  if (encendido) {
    
    digitalWrite(pines[0], HIGH);
    delay(500);
    digitalWrite(pines[0], LOW);
    
    digitalWrite(pines[1], HIGH);
    delay(500);
    digitalWrite(pines[1], LOW);

    digitalWrite(pines[2], HIGH);
    delay(500);
    digitalWrite(pines[2], LOW);
    
    if (enviado) {
      Serial1.println("Semaforo en estado ENCENDIDO");
      enviado = false;
    }
    
  } else {
    
    digitalWrite(pines[0], HIGH);
    digitalWrite(pines[1], HIGH);
    digitalWrite(pines[2], HIGH);
    
    delay(250);
    
    digitalWrite(pines[0], LOW);
    digitalWrite(pines[1], LOW);
    digitalWrite(pines[2], LOW);

    if (!enviado) {
      Serial1.println("Semaforo en estado APAGADO");
      enviado = true;
    }

    delay(250);
            
  }

  if (Serial1.available()>0) {
    
    char dato = Serial1.read();
    
    if (dato=='p') encendido = true;
    if (dato=='a') encendido = false;
  
  }
  
}

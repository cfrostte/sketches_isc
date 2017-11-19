/* 
 *  Controlar encendido de semaforo mediante la PC 
*/

int pines[3]; // Pines a utilizar
bool encendido = false;
int velocidad = 9600; // baudios
bool enviado = false;

void setup() {
  
  pines[0] = 1;
  pines[1] = 2;
  pines[2] = 3;
  
  pinMode(pines[0], OUTPUT);
  pinMode(pines[1], OUTPUT);
  pinMode(pines[2], OUTPUT);  

  // Inicializa el puerto  
  Serial.begin(velocidad);

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
      // Aparece en la pantalla del PC:      
      Serial.println("Semaforo en estado ENCENDIDO");
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
      // Aparece en la pantalla del PC:
      Serial.println("Semaforo en estado APAGADO");
      enviado = true;
    }

    delay(250);
            
  }

  // Si el puerto esta disponible...  
  if (Serial.available()>0) {

    // ... se lee un solo caracter enviado por la PC:
    char dato = Serial.read();

    // Enciende o apaga el semaforo segun la orden:
    if (dato=='p') encendido = true;
    if (dato=='a') encendido = false;
  
  }
  
}

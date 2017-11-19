/*
 * 
*/

int led = 7;
int in = 10;
int velocidad = 9600;
bool encender = false;
bool encendido = false;
bool correcto = false;

void setup() {
  
  // Puerto en modo salida
  pinMode(led, OUTPUT);

  // Puerto en modo entrada
  pinMode(in, INPUT);
  
   // Inicializa el puerto  
  Serial.begin(velocidad);  

}

void loop() {

  if (encender) {
    
    digitalWrite(led, HIGH);
    correcto = digitalRead(in);

    if (!correcto) {
      Serial.println("Led ROBADO");
    }
    
    if (encendido) {
      Serial.println("Led ENCENDIDO");
      encendido = false;
    }
    
    delay(500);
  
  } else {

    digitalWrite(led, LOW);

    if (!encendido) {
      Serial.println("Led APAGADO");
      encendido = true;
    }

    delay(500);
  
  }
  
  // Si el puerto esta disponible...  
  if (Serial.available()>0) {

    // ... se lee un solo caracter enviado por la PC:
    char dato = Serial.read();

    // Enciende o apaga el semaforo segun la orden:
    if (dato=='p') encender = true;
    if (dato=='a') encender = false;
  
  }

}

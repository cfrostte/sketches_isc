/*
 * 
*/

int primero = 2;
int segundo = 4;
int tercero = 7;
int cuarto = 8;

int a = 9;
int b = 10;

int velocidad = 9600;
int estado = 0;

void setup() {
  
  pinMode(primero, OUTPUT);
  pinMode(segundo, OUTPUT);
  pinMode(tercero, OUTPUT);
  pinMode(cuarto, OUTPUT);

  pinMode(a, INPUT);
  pinMode(b, INPUT);
  
  Serial.begin(velocidad);  

}

void loop() {
  
  int mueve_a = digitalRead(a);
  int mueve_b = digitalRead(b);

  if (estado<0){
    
    analogWrite(primero, 0);
    analogWrite(segundo, 800);
    analogWrite(tercero, 0);
    analogWrite(cuarto, 800);

    if (mueve_a) {
      analogWrite(primero, 0);
      analogWrite(segundo, 0);
      analogWrite(tercero, 800);
      analogWrite(cuarto, 0);
    }
    
    if (mueve_b) {
      analogWrite(primero, 800);
      analogWrite(segundo, 0);
      analogWrite(tercero, 0);
      analogWrite(cuarto, 800);
    }
    
    delay(1000);
  
  }

  if (estado==0){
    analogWrite(primero, 0);
    analogWrite(segundo, 0);
    analogWrite(tercero, 0);
    analogWrite(cuarto, 0);
    delay(1000);
  }

  if (estado>0) {
    analogWrite(primero, 800);
    analogWrite(segundo, 0);
    analogWrite(tercero, 800);
    analogWrite(cuarto, 0);
    delay(1000);
  }

  if (Serial.available()>0) {

    char dato = Serial.read();

    if (dato=='q') estado = -1;
    if (dato=='w') estado = 0;
    if (dato=='e') estado = 1;
  
  }

}

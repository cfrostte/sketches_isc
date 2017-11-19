/*
 * 
 */

 #include <Servo.h>

int pin_a = 2;
int pin_b = 3;
int pin_c = 4;
int grados = 115;

Servo volante; 

void setup() {
  pinMode(pin_a, OUTPUT);
  pinMode(pin_b, OUTPUT);
  volante.attach(pin_c);
  frenar();
  centro();
  Serial.begin(9600);
}

void loop() {
  
  if (Serial.available()>0) {

    char dato = Serial.read();

    if (dato=='w') acelerar();
    if (dato=='s') retroceder();
    if (dato==' ') frenar();
    if (dato=='a') izquierda();
    if (dato=='d') derecha();
    if (dato=='c') centro();
  
  }

  Serial.println(volante.read());
  
  delay(1);

}

void acelerar() {
  digitalWrite(pin_a, HIGH);
  digitalWrite(pin_b, LOW);
}

void retroceder() {
  digitalWrite(pin_a, LOW);
  digitalWrite(pin_b, HIGH);  
}

void frenar() {
  digitalWrite(pin_a, LOW);
  digitalWrite(pin_b, LOW);  
}

void izquierda() {
    volante.write(grados);
    grados+=20;
}

void derecha() {
    volante.write(grados);
    grados-=20;
}

void centro() {
  volante.write(115);
}


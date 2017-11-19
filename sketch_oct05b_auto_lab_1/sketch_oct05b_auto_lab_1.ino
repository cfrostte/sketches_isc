/*
 * Laboratorio 1
 */

#include <Servo.h>

#include <SoftwareSerial.h>

SoftwareSerial mySerial(7, 5);

long tiempo;
int disparador = 3; // = triger
int entrada = 4;    // = echo
float distancia;

// Motores:
int pin_a = 12;
int pin_b = 11;
int pin_c = 10;
int pin_d = 9;

Servo volante; 

int pin_e = 8;
int grados = 90;
int cuanto = 20;

// Botones:
//int pin_f = 7;
//int pin_g = 5;

// Estado
bool encendido;

// LEDs
int estado = 2;

void setup() {

  encendido = false;

  mySerial.begin(9600);

  pinMode(estado, OUTPUT);
  
  pinMode(pin_a, OUTPUT);
  pinMode(pin_b, OUTPUT);
  pinMode(pin_c, OUTPUT);
  pinMode(pin_d, OUTPUT);
  
  volante.attach(pin_e);

//  pinMode(pin_f, INPUT);
//  pinMode(pin_g, INPUT);

  pinMode(disparador, OUTPUT);
  pinMode(entrada, INPUT);
  
  frenar();
  centro();
  
  Serial.begin(9600);

}

void loop() {

  Serial.println(mySerial.read());
  
  distanciar();

//  joystick(); // Control fisico
  /*
  if (Serial.available()>0) {
    char dato = Serial.read();
    leer_comandos(dato);
  }*/

  if (mySerial.available()>0) {
    char dato = mySerial.read();
    Serial.println((char)dato);
    leer_comandos((char)dato);
  }
  
  delay(1);

}

//void joystick() {
//
//  int potenciometro = analogRead(A1);
//    
//  volante.write(map(potenciometro,0,1023,10,170));
//
//  int btn_retroceder = digitalRead(pin_f);
//  int btn_acelerar = digitalRead(pin_g);
//  
//  if (btn_retroceder) {
//    retroceder();
//    btn_acelerar = 0;
//  } else if (btn_acelerar) {
//    acelerar();
//    btn_retroceder = 0;
//  } else frenar();  
//
//}

void prender() {
  digitalWrite(estado, HIGH);
  encendido = true;
}

void apagar() {
  frenar();
  digitalWrite(estado, LOW);
  encendido = false;
}

void acelerar() {
  digitalWrite(pin_a, HIGH);
  digitalWrite(pin_b, LOW);
  digitalWrite(pin_c, LOW);
  digitalWrite(pin_d, HIGH);
}

void retroceder() {
  digitalWrite(pin_a, LOW);
  digitalWrite(pin_b, HIGH);
  digitalWrite(pin_c, HIGH);
  digitalWrite(pin_d, LOW);  
}

void frenar() {
  digitalWrite(pin_a, LOW);
  digitalWrite(pin_b, LOW);
  digitalWrite(pin_c, LOW);
  digitalWrite(pin_d, LOW);  
}

void izquierda() {
    
    if ((grados + cuanto) <= 170) grados += cuanto;
    else grados = 170;

    volante.write(grados);
    
}

void derecha() {
    
    if ((grados - cuanto) >= 10) grados -= cuanto;
    else grados = 10;

    volante.write(grados);

}

void centro() {
  grados = 90;
  volante.write(grados);
}

void seguir() {
  acelerar();
  if (analogRead(A2)>600) izquierda();
  if (analogRead(A3)>550) derecha();
}

void distanciar() {
  
  digitalWrite(disparador, HIGH);
  delayMicroseconds(10);
  digitalWrite(disparador, LOW);
  
  tiempo = (pulseIn(entrada, HIGH)/2); 
  distancia = float(tiempo * 0.0343);

  if (distancia<=20) frenar();
  
}

void leer_comandos(char dato) {
    
    if (dato=='1') prender();
    if (dato=='0') apagar();
 
    if (encendido) {
    
      if (dato=='w') acelerar();
      if (dato=='s') retroceder();
      
      if (dato==' ') frenar();
      
      if (dato=='a') izquierda();
      if (dato=='d') derecha();
      
      if (dato=='c') centro();

      if (dato=='l') seguir();
      if (dato=='k') frenar();

      if (dato=='k') frenar();
     
    }
    
}


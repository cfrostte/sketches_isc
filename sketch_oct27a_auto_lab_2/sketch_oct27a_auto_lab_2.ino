#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial mySerial(7, 6); // RX, TX

// Motores
int motor_izq_adelante = 12;
int motor_izq_atras = 11;
int motor_der_adelante = 10;
int motor_der_atras = 9;

Servo volante;
int datos_volante = 8;
int grados_volante = 90;
int cuantos_grados = 18;

// Proximidad
long tiempo;
int disparador = 3; // = triger
int entrada = 4;    // = echo
float distancia;
float cm = 20.0;
bool riesgo = false;
bool retrocediendo = false;

// Seguir linea
int seguir = false;

int linea_izq = 13;
int linea_der = 5;

void setup() {
  
  Serial.begin(9600);
  mySerial.begin(9600);
  
  pinMode(motor_izq_adelante, OUTPUT);
  pinMode(motor_izq_atras, OUTPUT);
  pinMode(motor_der_adelante, OUTPUT);
  pinMode(motor_der_atras, OUTPUT);

  volante.attach(datos_volante);

  pinMode(disparador, OUTPUT);
  pinMode(entrada, INPUT);

  pinMode(linea_izq, INPUT);
  pinMode(linea_der, INPUT);
  
  frenar();
  centro();

}

void loop() {

  distanciar();

//  Serial.println(volante.read());
  
//  if (mySerial.available()>0) {
//    char dato = mySerial.read();
//    Serial.println(dato);
//    leer_comandos(dato);
//  }

  if (Serial.available()>0) {
    char dato = Serial.read();
    leer_comandos(dato);
  }

  delay(1);

  if (seguir) seguidor();

}

void acelerar() {  
  digitalWrite(motor_izq_adelante, HIGH);
  digitalWrite(motor_izq_atras, LOW);
  digitalWrite(motor_der_adelante, LOW);
  digitalWrite(motor_der_atras, HIGH);
}

void retroceder() {

  retrocediendo = true;
  
  digitalWrite(motor_izq_adelante, LOW);
  digitalWrite(motor_izq_atras, HIGH);
  digitalWrite(motor_der_adelante, HIGH);
  digitalWrite(motor_der_atras, LOW);
   
}

void frenar() {
  digitalWrite(motor_izq_adelante, LOW);
  digitalWrite(motor_izq_atras, LOW);
  digitalWrite(motor_der_adelante, LOW);
  digitalWrite(motor_der_atras, LOW);  
}

void izquierda() {
  
  if ((grados_volante + cuantos_grados) <= 162) {
    grados_volante += cuantos_grados;
  } else {
    grados_volante = 162;
  }

  volante.write(grados_volante);
    
}

void derecha() {
    
    if ((grados_volante - cuantos_grados) >= 18) {
      grados_volante -= cuantos_grados;
    } else {
      grados_volante = 18;
    }

    volante.write(grados_volante);

}

void centro() {
  grados_volante = 90;
  volante.write(grados_volante);
}

void seguidor() {
  acelerar();
  if (digitalRead(linea_izq)) izquierda();
  if (digitalRead(linea_der)) derecha();
}

void distanciar() {

  float min_cm = 1.0;
  
//  Serial.println("riesgo");
//  Serial.println(riesgo);
  
  digitalWrite(disparador, HIGH);
  delayMicroseconds(10);
  digitalWrite(disparador, LOW);
  
  tiempo = (pulseIn(entrada, HIGH)/2); 
  distancia = float(tiempo * 0.0343);

  riesgo = ((distancia>=min_cm) && (distancia<=cm));

  if (riesgo && !retrocediendo) frenar();
  
//  Serial.println(distancia);
  
}

void leer_comandos(char dato) {

//  if (dato=='1') prender();
//  if (dato=='0') apagar();
  
//  if (encendido) {
  
    if (dato=='w' && !riesgo) acelerar();
    
    if (dato=='s') retroceder();
    else retrocediendo = false;
    
    if (dato==' ') frenar();
    
    if (dato=='a') izquierda();
    if (dato=='d') derecha();
    
    if (dato=='c') centro();
    
    if (dato=='l') seguir = true;
    if (dato=='k') seguir = false;
  
//  }

}

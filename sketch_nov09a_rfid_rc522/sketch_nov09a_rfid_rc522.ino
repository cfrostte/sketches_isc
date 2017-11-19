/*
 * La tarjeta de autenticacion es DA 17 73 74
 * que en hexadecimal es {0xDA, 0x17, 0x73, 0x74} 
*/

#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9 // Pin 9 para el reset del RC522
#define SS_PIN 10 // Pin 10 para el SS (SDA) del RC522

MFRC522 mfrc522(SS_PIN, RST_PIN); // Crear el objeto para el RC522

byte nueva[4]; // Almacenará el código del tag leído
byte legitima[4] = {0xDA, 0x17, 0x73, 0x74}; // Código del usuario 1

bool llave = false;

// Motores
int motor_adelante = 2;
int motor_atras = 7;

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

int linea_izq = 0;
int linea_der = 0;

bool esta_leyendo = false;
bool es_una_nueva = false;

void setup() {
  
  Serial.begin(9600); // Iniciar la comunicacion serial
  SPI.begin();        // Iniciar el Bus SPI
  mfrc522.PCD_Init(); // Iniciar el MFRC522

  pinMode(motor_adelante, OUTPUT);
  pinMode(motor_atras, OUTPUT);

  volante.attach(datos_volante);

  pinMode(disparador, OUTPUT);
  pinMode(entrada, INPUT);

  // pinMode(linea_izq, INPUT);
  // pinMode(linea_der, INPUT);
  
  frenar();
  centro();

}

void loop () {

  es_una_nueva = false;
  esta_leyendo = false;

  if (mfrc522.PICC_IsNewCardPresent()) {

    es_una_nueva = true;
  
    if (mfrc522.PICC_ReadCardSerial()) {

      esta_leyendo = true;
    
      for (byte i=0; i<mfrc522.uid.size; i++) {
        nueva[i] = mfrc522.uid.uidByte[i];          
      }
      
      llave = sonIguales(nueva, legitima);

      if (llave) {
        
        Serial.println("ok, funcionando");

        if (Serial.available()>0) {
          char dato = Serial.read();
          leer_comandos(dato);
        }

        delay(1);

        if (seguir) seguidor();
        
      } 
          
    } 
  
  }

  if (!llave || !esta_leyendo) frenar();

}

boolean sonIguales(byte array1[], byte array2[]) {
  
  if (array1[0]!=array2[0]) return false;
  if (array1[1]!=array2[1]) return false;
  if (array1[2]!=array2[2]) return false;
  if (array1[3]!=array2[3]) return false;
  
  return true;

}

void acelerar() {  
  digitalWrite(motor_adelante, HIGH);
  digitalWrite(motor_atras, LOW);
}

void retroceder() {

  retrocediendo = true;
  
  digitalWrite(motor_adelante, LOW);
  digitalWrite(motor_atras, HIGH);
   
}

void frenar() {
  digitalWrite(motor_adelante, LOW);
  digitalWrite(motor_atras, LOW);
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

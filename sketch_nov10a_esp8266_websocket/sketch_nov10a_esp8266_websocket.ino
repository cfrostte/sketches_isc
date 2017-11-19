/* 
 *  Placa a seleccionar:
 *  NodeMCU 1.0 (ESP-12E Module)
*/

/*
 * D7 => Encender/Apagar/LED
 * D6 => Motor adelante
 * D5 => Motor Atras
 * D4 => Servomotor
 * D3 => Senialero izquierda
 * D2 => Senialero derecha
*/

#include <Servo.h>

Servo volante;
int grados_volante = 90;
int cuantos_grados = 18;

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsClient.h>
#include <Hash.h>

ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;

#define USE_SERIAL Serial

#define MESSAGE_INTERVAL 30000
#define HEARTBEAT_INTERVAL 25000

uint64_t messageTimestamp = 0;
uint64_t heartbeatTimestamp = 0;
bool isConnected = false;

// Servidor
const char* servidor = "192.168.10.199";
int puerto = 3000;

// Red
const char* red = "TIP_ESTUDIANTES2";
const char* pass = "ESTUDIANTES";

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  
  switch (type) {
    
    case WStype_DISCONNECTED:
      USE_SERIAL.printf("[WSc] Disconnected!\n");
      isConnected = false;
    break;
    
    case WStype_CONNECTED: {
      USE_SERIAL.printf("[WSc] Connected to url: %s\n",  payload);
      isConnected = true;
      webSocket.sendTXT("5");
    }
    
    break;
    
    case WStype_TEXT: USE_SERIAL.printf("%s\n", payload);
      
      int i = 2;
      uint8_t b = payload[i];
      char c;
      String txt = "";
      String parametro = "";
      bool delimitador = false;
    
      while (b != NULL) {
        
        b = payload[i];
        c = (char)b;
        
        if (c == '[') { 
          // ToDo
        }
        if (c == ']') { 
          // ToDo
        }
        if (c == '"') { 
          // ToDo
        }
        
        else {
          
          if (c == ',') {
            
            delimitador = true;
            
          } else {
            
            if (delimitador && c!=']' && b != 0) {
              parametro = String(parametro + c);                          
            }
            
            if (!delimitador && c!='[') {
              txt = String(txt + c);
            }
            
          }
          
        }
        
        i++;
        
      }
      
      if (txt == "enviarDatosalMCU" && parametro == "encenderLED") {
        digitalWrite(D7, HIGH);
      }
      
      if (txt == "enviarDatosalMCU" && parametro == "apagarLED") {
        digitalWrite(D7, LOW);
      }

      if (txt == "enviarDatosalMCU" && parametro == "acelerarDron") {
        acelerar();
      }

      if (txt == "enviarDatosalMCU" && parametro == "retrocederDron") {
        retroceder();
      }

      if (txt == "enviarDatosalMCU" && parametro == "izquierdaDron") {
        izquierda();
      }

      if (txt == "enviarDatosalMCU" && parametro == "derechaDron") {
        derecha();
      }

      if (txt == "enviarDatosalMCU" && parametro == "frenarDron") {
        frenar();
      }
    
    break;
    
  }
  
}

String aux = "";

void setup() {

  USE_SERIAL.begin(115200);

  pinMode(D7, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D2, OUTPUT);

  volante.attach(D4);
  
  USE_SERIAL.setDebugOutput(true);
  
  USE_SERIAL.println();
  USE_SERIAL.println();
  USE_SERIAL.println();
  
  for (uint8_t t = 4; t > 0; t--) {
    USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
    USE_SERIAL.flush();
    delay(1000);
  }
  
  WiFiMulti.addAP(red, pass);
  
  while (WiFiMulti.run() != WL_CONNECTED) {
    delay(100);
  }
  
  webSocket.beginSocketIO(servidor, puerto);
  webSocket.onEvent(webSocketEvent);

  frenar();
  centro();

}

void loop() {
  
  webSocket.loop();
  
  if (isConnected) { 
    // ToDo
  }
  
}

void acelerar() {  
  digitalWrite(D6, HIGH);
  digitalWrite(D5, LOW);
 
}

void retroceder() {

  
  digitalWrite(D6, LOW);
  digitalWrite(D5, HIGH);

   
}

void frenar() {
  digitalWrite(D6, LOW);
  digitalWrite(D5, LOW);
}

void izquierda() {
  
  if ((grados_volante + cuantos_grados) <= 162) {
    grados_volante += cuantos_grados;
    delay(10);
  digitalWrite(D3, HIGH);
  delay(10);
  digitalWrite(D3, LOW);
  } else {
    grados_volante = 162;
  }

  volante.write(grados_volante);

  
}

void derecha() {
    
    if ((grados_volante - cuantos_grados) >= 18) {
      grados_volante -= cuantos_grados;
 delay(10);
  digitalWrite(D2, HIGH);
  delay(10);
  digitalWrite(D2, LOW);      
    } else {
      grados_volante = 18;
    }
 
    volante.write(grados_volante);

}

void centro() {
  grados_volante = 90;
  volante.write(grados_volante);
}

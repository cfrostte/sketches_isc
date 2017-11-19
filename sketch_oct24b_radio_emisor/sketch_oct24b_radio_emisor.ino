#include <VirtualWire.h>

// Direcciones:
int pin_w = 1;
int pin_s = 2;
int pin_a = 3;
int pin_d = 4;

const int dataPin = 9;

void setup() {
  
  Serial.begin(9600);
  
  vw_setup(2000);
  vw_set_tx_pin(dataPin);
  
  pinMode(pin_w, INPUT);
  pinMode(pin_s, INPUT);
  pinMode(pin_a, INPUT);
  pinMode(pin_d, INPUT);

}

void loop() {

  leer_botones();
  
  while (Serial.available()>0) {
    
    char data[1];
    
    data[0] = Serial.read();
      
    vw_send((uint8_t*)data,sizeof(data));
    
    vw_wait_tx();
  
  }

}

void leer_botones() {
  
  char data[1];
  
  bool valor_w = digitalRead(pin_w);
  bool valor_s = digitalRead(pin_s);
  bool valor_a = digitalRead(pin_a);
  bool valor_d = digitalRead(pin_d);
  
  if (valor_w || valor_s ||valor_a || valor_d) {
    
    if (valor_w) data[0]='w';
    if (valor_s) data[0]='s';
    if (valor_a) data[0]='a';
    if (valor_d) data[0]='d';
  
  } else {
  
    data[0]=' '; // Frenar
  
  }
  
  vw_send((uint8_t*)data,sizeof(data));
  vw_wait_tx();  

}


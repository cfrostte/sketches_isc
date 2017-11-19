int led1 = 10;
int btn1 = 9; 
bool status_btn1 = false;
char dato;
bool enviado = false;

void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(btn1, INPUT);
}

void loop() {
  
  status_btn1 = digitalRead(btn1);
  
  if (status_btn1) Serial.print("btn1_apretado");
  else Serial.print("btn1_liberado");
  
  if (Serial.available()>0) {
    
    dato = Serial.read();
    
    if (dato == 'a') digitalWrite(led1, LOW);
    if (dato == 'p') digitalWrite(led1, HIGH);
  }
  
  delay(100);

}


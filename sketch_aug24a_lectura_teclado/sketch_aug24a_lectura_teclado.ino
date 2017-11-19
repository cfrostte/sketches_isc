/* 
 *  Lectura de teclado matricial
*/

int pines[6];

void setup() {
  
  pines[0] = 2;
  pines[1] = 3;
  pines[2] = 4;
  pines[3] = 5;
  pines[4] = 7;
  pines[5] = 8;
  
  pinMode(pines[0], INPUT);
  pinMode(pines[1], INPUT);
  pinMode(pines[2], INPUT);
  pinMode(pines[3], INPUT);
  pinMode(pines[4], INPUT);
  pinMode(pines[5], INPUT);

  Serial.begin(9600);

}

void loop() {

  if (Serial.available()>0) {
    bool estado = digitalRead(pines[5]);
    Serial.println(estado);
  }
 
//  for (int i=0; i<5; i++) {
//
//    bool estado = digitalRead(pines[i]);
//
//    if (Serial.available()>0) {
//
//      
//      
//      if (estado) {
//        if (i==3) Serial.println("Estas apretando 1");
//        if (i==2) Serial.println("Estas apretando 2");
//        if (i==1) Serial.println("Estas apretando 3");
//        if (i==0) Serial.println("Estas apretando A");
//      }
//
//      if (i==4) {
//          
//          if (estado) {
//            Serial.println("Esta detectando blanco");
//          } else {
//            Serial.println("Esta detectando negro");
//          }
//          
//       }
//      
//    }
//  
//  }
  
  delay(1000);

}

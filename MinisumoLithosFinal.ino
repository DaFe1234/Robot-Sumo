/* 
 * By Daniel Romero
 * Codigo para minisumo (Runibot 2022)
*/
#include <NHCSR04.h>
int baudrate = 9600;

//----------Variables Sensores---------------------------------------------------------
//----------Ultrasonido Izquierda-----------(Visto de frente)
int triggerPinIzq = A0;
int echoPinIzq = A1;

SR04 sensorIzq(triggerPinIzq, echoPinIzq);

double MedidaIzq;
//----------Ultrasonido Derecha-----------(Visto de frente)
int triggerPinDer = A2;
int echoPinDer = A3;

SR04 sensorDer(triggerPinDer, echoPinDer);

double MedidaDer;
//-------------De piso----------(Visto de frente)
int pisoIzq = A4;
int lecIzq = 0;
int pisoDer = A5;
int lecDer = 0;
//-----------Variables Motores----------------------------------------------------------
int In1 = 8;
int In2 = 7;
int In3 = 6;
int In4 = 5;
//----------Variables Algoritmo--------------------------------------------------------
int ultraActual [2];

unsigned long tiempoAct = millis();
unsigned long tiempoAnt = 0;


//Este flag se crea con el fin de saber cual fue el ultimo caso antes de entrar en caso 4, 5 o 6 (presente en el primer while)
int flag = 0;
int flag2 = 0;

void setup()
{
  delay(5000);
  Serial.begin(baudrate);
//----------Pin Mode Sensores------------
  pinMode(pisoIzq, INPUT);
  pinMode(pisoDer, INPUT);
//----------Pin Mode Motores-------------
  pinMode(In1,OUTPUT);
  pinMode(In2,OUTPUT);
  pinMode(In3,OUTPUT);
  pinMode(In4,OUTPUT);
//----------Cosas algoritmo--------------
 
}

void loop(){
  Lectura();
while(lecIzq == 1 && lecDer == 1){
  //Serial.println(MedidaIzq);
  Lectura();
//Caso 1, 2 y 3 respectivamente
    if(ultraActual[0] == 1 && ultraActual[1] == 1){
      movAdelante();
      flag = 0;
    }
    else if(ultraActual[0] == 0 && ultraActual [1] == 1){
      girIzq();
      flag = 2;
    }
    else if(ultraActual[1] == 0 && ultraActual [0] == 1){
      girDer();
      flag = 1;
    }
//Caso 4, 5 y 6 respectivamente
    if(ultraActual[0] == 0 && ultraActual [1] == 0){
      if(flag == 2){
        girIzq();
      }
      else if(flag == 1){
        girDer();
      }
      else if(flag == 0){
        girDer(); 
      }
    }
  }
  while(ultraActual[0] == 0 && ultraActual[1] == 0){
    Lectura();
  if(lecIzq == 0 && lecDer == 0){
    flag2 = 1;
  }
  while(flag2 == 1){
    Lectura();
    if(!espera(600)){
      movAtras();
    }
    else if(!espera(200)){
      girDer();
    }else{
      flag2 = 0;
    }
  }
  if(lecIzq == 0 && lecDer == 1){
    flag2 = 2;
  }
  while(flag2 == 2){
    Lectura();
    if(!espera(600)){
      girIzq();
    }    
    if(!espera(300)){
      movAdelante();
    }else{
      flag2 = 0;
    }
  }
  if(lecIzq == 1 && lecDer == 0){
    flag2 = 3;
  }
  while(flag2 == 3){
    Lectura();
    if(!espera(600)){
      girDer();
    }
    if(!espera(300)){
      movAdelante();
    }else{
      flag2 = 0;
    }
  }
 }
}
//------------Variable datos algoritmo------------
void Lectura(){
  LecturaUltra();
  LecturaPiso();
      if(MedidaIzq <= 65){
      ultraActual[0] = 1;
    }
    else if(MedidaIzq > 65){
      ultraActual[0] = 0;
    }
    if(MedidaDer <= 65){
      ultraActual[1] = 1;
    }
    else if(MedidaDer > 65){
      ultraActual[1] = 0;
    }
}
//------------Variables Sensores-----------
void LecturaUltra(){
    MedidaIzq = sensorIzq.centimeters();
    MedidaDer = sensorDer.centimeters();
    /*Serial.print("cm: ");
    Serial.print(MedidaIzq);
    Serial.print("        cm: ");
    Serial.println(MedidaDer);*/
}
void LecturaPiso(){
  lecIzq = digitalRead(pisoIzq);
  lecDer = digitalRead(pisoDer);
  /*Serial.print(lecIzq);
  Serial.print("  ");
  Serial.println(lecDer);*/
}
//------------Variables Motores------------
void movAdelante(){
  Serial.println("movAdelante");
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
}
void movAtras(){
  Serial.println("movAtras");
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
}
void girDer(){
  Serial.println("girDer");
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
}
void girIzq(){
  Serial.println("girIzq");
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
}
bool espera (long tiempo){
  tiempoAct = millis();
  if(tiempoAct - tiempoAnt >= tiempo){
    tiempoAnt = tiempoAct;
    return true;
  }else{
    return false;
  }
}

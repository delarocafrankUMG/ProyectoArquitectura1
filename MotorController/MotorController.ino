#include <Stepper.h>

const int spr = 50;
const int speed = 5;
const int pasos = 1;
int TalanqueraIN = 12;
int CarPassIN = 13;
int TalanqueraOUT = 4;
int CarPassOUT = 5;
int a = 0; // startup variable
int statusTalanqueraIN = 0;
int statusTalanqueraOUT = 0;
/*
Status Talanquera
0: Cerrada
1: Abierta
*/
Stepper motorOUT(spr, 0, 1, 2, 3);
Stepper motorIN(spr, 8, 9, 10, 11);

void setup() {
  motorIN.setSpeed(speed);
  motorOUT.setSpeed(speed);
  pinMode(TalanqueraIN, INPUT);
}

void loop() {
if(a == 0){
  motorIN.step(3);
  motorOUT.step(3);
  motorIN.step(-3);
  motorOUT.step(-3);
  a= 1;
}
if(digitalRead(TalanqueraIN) == 1 && statusTalanqueraIN == 0){
motorIN.step(3);
statusTalanqueraIN = 1;
}

if(digitalRead(CarPassIN) == 1 && statusTalanqueraIN == 1){
motorIN.step(-3);
statusTalanqueraIN = 0;
}

if(digitalRead(TalanqueraOUT) == 1 && statusTalanqueraOUT == 0){
motorOUT.step(3);
statusTalanqueraOUT = 1;
}

if(digitalRead(CarPassOUT) == 1 && statusTalanqueraOUT == 1){
motorOUT.step(-3);
statusTalanqueraOUT = 0;
}

}

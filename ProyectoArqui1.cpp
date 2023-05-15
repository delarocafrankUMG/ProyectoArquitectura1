int clockPin = 0; // Pin de reloj
int dataPin = 1; // Pin de datos
int select1Pin = 2;
int select2Pin = 3;
int statePin = 4;
int clockFFPin = 5;
int MY_BUTTON = 11;
int read1Pin = 13;
int read2Pin = 12;
int output1, output2;

/*
State 
0: Ocupado
1: Disponible
2: Reservado
*/
class ParkingSpot {
   private:
   int state; 
   int code;
   int priority;
   public:
   ParkingSpot(int State, int Code){
    state = State;
    code = Code;
   }

   void setState(int State){
    state = State;
   }
   
    setPriority(int Priority){
        priority = Priority;
    }

    int getPriority(){
        return priority;
    }

   void showState(){
    
     digitalWrite(clockFFPin, 0);

    if(state == 1)
    {
      digitalWrite(statePin, 1);
    }
    else
    {
      digitalWrite(statePin, 0);
    }

    digitalWrite(clockFFPin, 1);
   }

   void showCode(){
  switch (code) {
  case 0:
  shiftOut(dataPin, clockPin, MSBFIRST, B01111111); 
  break;
  case 1:
  shiftOut(dataPin, clockPin, MSBFIRST, B00001100);
  break;
  case 2:
  shiftOut(dataPin, clockPin, MSBFIRST, B10110110);
  break;
  case 3:
  shiftOut(dataPin, clockPin, MSBFIRST, B10011110);
  break;
  case 4:
  shiftOut(dataPin, clockPin, MSBFIRST, B11001100); 
  break;
  case 5:
  shiftOut(dataPin, clockPin, MSBFIRST, B11011010);
  break;
  case 6:
  shiftOut(dataPin, clockPin, MSBFIRST, B11111000);
  break;
  case 7:
  shiftOut(dataPin, clockPin, MSBFIRST, B00001110); 
  break;
  case 8:
  shiftOut(dataPin, clockPin, MSBFIRST, B11111110);
  break;
  case 9:
  shiftOut(dataPin, clockPin, MSBFIRST, B11001110);
  break;
  default:
    // hacer algo si el valor no coincide con ningún caso
    break;
}
   }
};
ParkingSpot parkingSpots[2][4] = {
     {
        ParkingSpot(0,1),
        ParkingSpot(0,2),
        ParkingSpot(0,3),
        ParkingSpot(0,4)
     },
     {
        ParkingSpot(0,5),
        ParkingSpot(0,6),
        ParkingSpot(0,7),
        ParkingSpot(0,8)
     }

};

void setup() {
  pinMode(clockPin, OUTPUT); 
  pinMode(dataPin, OUTPUT); 
  pinMode(clockFFPin, OUTPUT); 
  pinMode(select1Pin, OUTPUT);
  pinMode(select2Pin, OUTPUT);
  pinMode(statePin, OUTPUT);
  //Serial.begin(9600); // Velocidad de transmisión serial
}

void loop() {
    int counter = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            digitalWrite(select1Pin, i);
            digitalWrite(select2Pin, j);

            output1 = digitalRead(read1Pin);
            output2 = digitalRead(read2Pin);
            
            //parkingSpots[0][counter].showCode();
            parkingSpots[0][counter].setState(output1);
            parkingSpots[0][counter].showState();

            //parkingSpots[1][counter].showCode();
            parkingSpots[1][counter].setState(output2);
            parkingSpots[1][counter].showState();
            counter++;
        }
  }
/*
  if (digitalRead(MY_BUTTON) == 1) {
    digitalWrite(statePin, 0);
    parkingSpots[0][0].showState();
  }
  */
}


/*
 for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      digitalWrite(pin1, i);
      digitalWrite(pin2, j);
      delay(1000); // Espera 1 segundo
      output1 = digitalRead(12);
      output2 = digitalRead(13);
      Serial.print(i);
      Serial.print(j);
      Serial.print(" -> ");
      Serial.print(output1);
      Serial.print(output2);
      Serial.println();
    }
  }
*/

/*
  // Enviamos el valor binario de un número decimal al integrado 74LS164
  shiftOut(dataPin, clockPin, MSBFIRST, B01111111); // Enviamos el número 0
  delay(1000); // Esperamos un segundo antes de enviar el siguiente número
  shiftOut(dataPin, clockPin, MSBFIRST, B00001100); // Enviamos el número 1
  delay(1000); // Esperamos un segundo antes de enviar el siguiente número
  shiftOut(dataPin, clockPin, MSBFIRST, B10110110); // Enviamos el número 2
  delay(1000); // Esperamos un segundo antes de enviar el siguiente número
  shiftOut(dataPin, clockPin, MSBFIRST, B10011110); // Enviamos el número 3
  delay(1000); // Esperamos un segundo antes de enviar el siguiente número
  shiftOut(dataPin, clockPin, MSBFIRST, B11001100); // Enviamos el número 4
  delay(1000); // Esperamos un segundo antes de enviar el siguiente número
  shiftOut(dataPin, clockPin, MSBFIRST, B11011010); // Enviamos el número 5
  delay(1000); // Esperamos un segundo antes de enviar el siguiente número
  shiftOut(dataPin, clockPin, MSBFIRST, B11111000); // Enviamos el número 6
  delay(1000); // Esperamos un segundo antes de enviar el siguiente número
  shiftOut(dataPin, clockPin, MSBFIRST, B00001110); // Enviamos el número 7
  delay(1000); // Esperamos un segundo antes de enviar el siguiente número
  shiftOut(dataPin, clockPin, MSBFIRST, B11111110); // Enviamos el número 8
  delay(1000); // Esperamos un segundo antes de enviar el siguiente número
  shiftOut(dataPin, clockPin, MSBFIRST, B11001110); // Enviamos el número 9
  delay(1000); // Esperamos un segundo antes de enviar el siguiente número
*/
int clockPin = 0; // Pin de reloj
int dataPin = 1; // Pin de datos
int select1Pin = 2;
int select2Pin = 3;
int statePin = 4;
int clockFFPin = 5;
int TalanqueraIN = 6;
int CarPassIN = 7;
int TalanqueraOUT = 8;
int CarPassOUT = 9;
int BUTTON_OUT = 10;
int MY_BUTTON = 11;
int read1Pin = 12;
int read2Pin = 13;
int output1, output2;
int clockPinSalida = 15;
int dataPinSalida = 16;
int EspaciosDisponibles = 0;
int StartUpFlag = 0;
/*
Status Talanquera
0: Cerrada
1: Abierta
*/
int statusTalanqueraIN = 0;
int statusTalanqueraOUT = 0;

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
   ParkingSpot(int State, int Code, int Priority){
    state = State;
    code = Code;
    priority = Priority;
   }

   void setState(int State){
     if(state == 1 && State == 2){
        state = State;
     }
     else if (state == 2 && State == 1){
        
     }
     else
     {
       state = State;
     }
    
   }

    int getState(){
        return state;
    }
    setPriority(int Priority){
        priority = Priority;
    }

    int getPriority(){
        return priority;
    }



   void showState(){
    
    if(state == 0)
    {
      //status bit1
      digitalWrite(clockFFPin, 0);
      digitalWrite(statePin, 0);
      digitalWrite(clockFFPin, 1);
      //status bit2
      digitalWrite(clockFFPin, 0);
      digitalWrite(statePin, 0);
      digitalWrite(clockFFPin, 1);
    }
    else if(state == 1)
    {
      //status bit1
      digitalWrite(clockFFPin, 0);
      digitalWrite(statePin, 0);
      digitalWrite(clockFFPin, 1);

      //status bit2
      digitalWrite(clockFFPin, 0);
      digitalWrite(statePin, 1);
      digitalWrite(clockFFPin, 1);
    }
    else if (state == 2)
    {
      //status bit1
      digitalWrite(clockFFPin, 0);
      digitalWrite(statePin, 1);
      digitalWrite(clockFFPin, 1);

      //status bit2
      digitalWrite(clockFFPin, 0);
      digitalWrite(statePin, 0);
      digitalWrite(clockFFPin, 1);

    }

    
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
        ParkingSpot(1,1,8),
        ParkingSpot(1,2,9),
        ParkingSpot(1,3,7),
        ParkingSpot(1,4,6)
     },
     {
        ParkingSpot(1,5,5),
        ParkingSpot(1,6,4),
        ParkingSpot(1,7,3),
        ParkingSpot(1,8,12)
     }

};

void setup() {
  pinMode(clockPin, OUTPUT); 
  pinMode(dataPin, OUTPUT); 
  pinMode(clockFFPin, OUTPUT); 
  pinMode(select1Pin, OUTPUT);
  pinMode(select2Pin, OUTPUT);
  pinMode(statePin, OUTPUT);
  pinMode(clockPinSalida, OUTPUT);
  pinMode(dataPinSalida, OUTPUT);
  pinMode(TalanqueraIN, OUTPUT);
  pinMode(TalanqueraOUT, OUTPUT);
  //Serial.begin(9600); // Velocidad de transmisión serial
}

void AbrirTalanquera(int TalanqueraID) {
  digitalWrite(TalanqueraID, 1);
  delay(100);
  digitalWrite(TalanqueraID, 0);
}

void DisplayEspacios(int Numero){
  switch (Numero) {
  case 0:
  shiftOut(dataPinSalida, clockPinSalida, MSBFIRST, B01111111); 
  break;
  case 1:
  shiftOut(dataPinSalida, clockPinSalida, MSBFIRST, B00001100);
  break;
  case 2:
  shiftOut(dataPinSalida, clockPinSalida, MSBFIRST, B10110110);
  break;
  case 3:
  shiftOut(dataPinSalida, clockPinSalida, MSBFIRST, B10011110);
  break;
  case 4:
  shiftOut(dataPinSalida, clockPinSalida, MSBFIRST, B11001100); 
  break;
  case 5:
  shiftOut(dataPinSalida, clockPinSalida, MSBFIRST, B11011010);
  break;
  case 6:
  shiftOut(dataPinSalida, clockPinSalida, MSBFIRST, B11111000);
  break;
  case 7:
  shiftOut(dataPinSalida, clockPinSalida, MSBFIRST, B00001110); 
  break;
  case 8:
  shiftOut(dataPinSalida, clockPinSalida, MSBFIRST, B11111110);
  break;
  case 9:
  shiftOut(dataPinSalida, clockPinSalida, MSBFIRST, B11001110);
  break;
  default:
    // hacer algo si el valor no coincide con ningún caso
    break;
}
}
void VehiculoCount(int numero){
  EspaciosDisponibles = EspaciosDisponibles + numero;
  DisplayEspacios(EspaciosDisponibles);
}

void loop() {
    int counter = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            digitalWrite(select1Pin, i);
            digitalWrite(select2Pin, j);

            output1 = digitalRead(read1Pin);
            output2 = digitalRead(read2Pin);
            
            parkingSpots[0][counter].setState(output1);

            parkingSpots[1][counter].setState(output2);

            if(StartUpFlag == 0){
                VehiculoCount(output1);
                VehiculoCount(output2);
            }
            counter++;
        }
  }
StartUpFlag = 1;
for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {
        parkingSpots[i][j].showState();
    }
}


  if (digitalRead(MY_BUTTON) == 1 && statusTalanqueraIN == 0) {
        ParkingSpot* maxPrioritySpot = nullptr;

        for (int i = 0; i < 2; i++) {
          for (int j = 0; j < 4; j++) {
            ParkingSpot* currentSpot = &parkingSpots[i][j];
            
            if(maxPrioritySpot != nullptr){
                if (currentSpot->getPriority() > maxPrioritySpot->getPriority() && currentSpot->getState() == 1) {
                  maxPrioritySpot = currentSpot;
                }
            }
            else if (currentSpot->getState() == 1)
            {
              maxPrioritySpot = currentSpot;
              
            }
            
          }
        }
        if(maxPrioritySpot != nullptr){
        maxPrioritySpot->showCode();
        maxPrioritySpot->setState(2);
        AbrirTalanquera(TalanqueraIN);
        VehiculoCount(-1);
        statusTalanqueraIN = 1;
        }
        else
        {
        shiftOut(dataPin, clockPin, MSBFIRST, B11110011); // Enviamos la letra E
        }
  }

  if(digitalRead(CarPassIN) == 1 && statusTalanqueraIN == 1){
    statusTalanqueraIN = 0;
    shiftOut(dataPin, clockPin, MSBFIRST, B00000000); // Apagamos el display
  }

  if(digitalRead(BUTTON_OUT) == 1 && statusTalanqueraOUT == 0){
      AbrirTalanquera(TalanqueraOUT);
      statusTalanqueraOUT = 1;
  }

    if(digitalRead(CarPassOUT) == 1 && statusTalanqueraOUT == 1){
    statusTalanqueraOUT = 0;
    VehiculoCount(1);
  }
  
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
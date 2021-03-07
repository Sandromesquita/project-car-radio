/*
   PROJETO CARRO COM MARCHA
   Inicio: 05/03/2021
   Atualizado: 05/03/2021
   Aula 01: Lógica das marchas

   Materiais:
   01 - 1 x Arduino UNO
   02 - 3 x Botões
   03 - 1 x Display LCD 16x2 (No Joystic)
   04 - 1 x Arduino Nano
   05 - Cabos jumper
   06 - 2 x Motores com Roda
   07 - 1 x Ponte H L208
   08 - 1 x Chassi
   09 - 1 x Roda Boba
   10 - 2 x Radio nrf2401
   11 - 2 x Adaptador para nrf2401
   12 - 1 x Ultrassonico
   13 - 4 x Bateria de 18650
   14 - 2 x Suporte para bateria 18650
   15 - 2 x Conector macho p4
   16 - 2 x Chaves On/Off
   17 - 1 x Led verde
   18 - 1 x Resistor 330Ohm
*/

//Pins H bridge
//Left engine
byte ENA = 3, N1 = 2, N2 = 4;
//Right engine
byte ENB = 5, N3 = 7, N4 = 8;

//pin button
byte forwardBtn = A0, leftBtn = A1, rightBtn = A2, backBtn = A3, gearBtn = 13;

//pin light
byte ledGear = 6, numGear = 0;

#define backSpeed 100 //Speed of the back
#define speedTurn 150 //Speed of the turn

bool changerGear = false, y = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Inicializando");
  for (byte pin = 2; pin < 9; pin++) {
    pinMode(pin, OUTPUT);
  }
  for (byte pin = 13; pin < 18; pin++) {
    pinMode(pin, INPUT_PULLUP);
  }
  digitalWrite(ledGear, LOW);
}

void loop() {

  if (!digitalRead(gearBtn)) {
    changerGear = true;
    gear();
  }

  if (!digitalRead(forwardBtn)) {
    if (numGear > 0) {
      forwardCar(numGear);
    }
    else {
      changerGear = true;
      gear();
    }
  }

  else if (!digitalRead(leftBtn)) leftCar();

  else if (!digitalRead(rightBtn)) rightCar();

  else if (!digitalRead(backBtn)) backCar();

  else stopCar();
}

//Function for change the march
void gear() {
  while (changerGear) {
    Serial.println("Acts Gear: " + String(numGear));
    if (!digitalRead(gearBtn)) {
      digitalWrite(ledGear, HIGH);
      numGear++;
      Serial.println("Changer for March: " + String(numGear));
      if (numGear > 4) {
        if (!y) {
          y = true;
          numGear = 4;
        }
        else{
          y = false;
          numGear = 0;
        }
      }
      changerGear = false;
      delay(250);
      digitalWrite(ledGear, LOW);
    }
  }
}

void forwardCar(byte numGear) {
  byte speedMax;

  switch (numGear) {
    case 1:
      speedMax = 70;
      break;

    case 2:
      speedMax = 120;
      break;

    case 3:
      speedMax = 180;
      break;

    case 4:
      speedMax = 255;
      break;
  }
  analogWrite(ENA, speedMax);
  digitalWrite(N1, HIGH);
  digitalWrite(N2, LOW);

  analogWrite(ENB, speedMax);
  digitalWrite(N3, HIGH);
  digitalWrite(N4, LOW);

  Serial.println("Speed: " + String(speedMax));
}

void leftCar() {
  analogWrite(ENA, speedTurn);
  digitalWrite(N1, LOW);
  digitalWrite(N2, HIGH);

  analogWrite(ENB, speedTurn);
  digitalWrite(N3, HIGH);
  digitalWrite(N4, LOW);
}

void rightCar() {
  analogWrite(ENA, speedTurn);
  digitalWrite(N1, HIGH);
  digitalWrite(N2, LOW);

  analogWrite(ENB, speedTurn);
  digitalWrite(N3, LOW);
  digitalWrite(N4, HIGH);
}

void backCar() {
  analogWrite(ENA, backSpeed);
  digitalWrite(N1, LOW);
  digitalWrite(N2, HIGH);

  analogWrite(ENB, backSpeed);
  digitalWrite(N3, LOW);
  digitalWrite(N4, HIGH);
}

void stopCar(){
  analogWrite(ENA, 0);
  digitalWrite(N1, HIGH);
  digitalWrite(N2, LOW);

  analogWrite(ENB, 0);
  digitalWrite(N3, HIGH);
  digitalWrite(N4, LOW);
}

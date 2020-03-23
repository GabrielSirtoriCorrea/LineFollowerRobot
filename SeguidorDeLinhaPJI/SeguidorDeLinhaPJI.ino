#include <SoftwareSerial.h>

#define sensorEsquerda 13
#define sensorCentral 12
#define sensorDireita 2
#define IN1 7
#define IN2 6
#define IN3 5
#define IN4 4
#define VelA 3
#define VelB 9
#define rx 10
#define tx 11

SoftwareSerial bluetooth(rx, tx);

int ValorBluetooth;
int vel;
int valEsquerda;
int valCentral;
int valDireita;

void frente();
void tras();
void direita();
void esquerda();
void parado();
void SeguirLinha();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  bluetooth.begin(9600);
  
  delay(100);
    
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(VelA, OUTPUT);
  pinMode(VelB, OUTPUT);
  pinMode(sensorEsquerda, INPUT);
  pinMode(sensorCentral, INPUT);
  pinMode(sensorDireita, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:  
  if (bluetooth.available()){
    ValorBluetooth = bluetooth.read();
    Serial.println(ValorBluetooth);
    switch(ValorBluetooth){
      case 70:
        frente();
        analogWrite(VelA, vel);
        analogWrite(VelB, vel);
        break;
      case 66:
        tras();
        analogWrite(VelA, vel);
        analogWrite(VelB, vel);
        break;
      case 82:
        direita();
        analogWrite(VelA, vel);
        analogWrite(VelB, vel);
        break;
      case 76:
        esquerda();
        analogWrite(VelA, vel);
        analogWrite(VelB, vel);
        break;
      case 71:
        esquerda();
        analogWrite(VelA, vel);
        analogWrite(VelB, vel);
        break;
      case 73:
        direita();
        analogWrite(VelA, vel);
        analogWrite(VelB, vel);
        break;

      case 88:
        SeguirLinha();
        vel = 10;
        analogWrite(VelA, vel);
        analogWrite(VelB, vel);
        break;
      case 50:
        vel = 0;
        break;
    
      case 51:
        vel = 50;
        break;

      case 52:
        vel = 70;
        break;

      case 53:
        vel = 90;
        break;

      case 54:
        vel = 110;
        break;

      case 55:
        vel = 150;
        break;

      case 56:
        vel = 180;
        break;

      case 57:
        vel = 210;
        break;

      case 58:
        vel = 240;
        break;

      case 59:
        vel = 255;
        break;
        
      default:
        parado();
        break;
    }
    
    /*if(ValorBluetooth == 70){
      frente();
    }else{
      tras();
    }*/
  }
}

void frente(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void parado(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}

void tras(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void direita(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void esquerda(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);  
}

void SeguirLinha(){
  while(true){
    if (bluetooth.available()){
      ValorBluetooth = bluetooth.read();
      Serial.println(ValorBluetooth);
      Serial.println("SEGUINDO LINHA...");

       if(ValorBluetooth == 120){
          break;
       }else{
          valEsquerda = digitalRead(sensorEsquerda);
          valCentral = digitalRead(sensorCentral);
          valDireita = digitalRead(sensorDireita);

          Serial.println(valEsquerda);
          Serial.println(valCentral);
          Serial.println(valDireita);
          
          if(valEsquerda == 0 && valCentral == 0 && valDireita == 0){
            parado();
          }else if(valEsquerda == 0 && valCentral == 0 && valDireita == 1){
            direita();
          }else if(valEsquerda == 0 && valCentral == 1 && valDireita == 0){
            frente();
          } else if(valEsquerda == 0 && valCentral == 1 && valDireita == 1){
            direita();
          }else if(valEsquerda == 1 && valCentral == 0 && valDireita == 0){
            esquerda();
          }else if(valEsquerda == 1 && valCentral == 0 && valDireita == 1){
            parado();
          }else if(valEsquerda == 1 && valCentral == 1 && valDireita == 0){
            esquerda();
          }else if(valEsquerda == 1 && valCentral == 1 && valDireita == 1){
            parado();
          }

          //delay(1000);
       }
      
    }
  }
}

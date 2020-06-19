#include <Servo.h>

//PINES DE ULTRASONIDO
#define echoo 32
#define trig 33

//PINES DE LOS SERVOS Y LED
Servo miniservo1;
Servo miniservo2;
int led = 34;

//VARIABLES
long duracion, distancia; 

void setup() {
  // CONFIGURACIÓN
  Serial.begin(9600);
  
  //PINES DE LOS SERVOS
  miniservo1.attach (35);
  miniservo2.attach (36);
  
  //LOS SERVOS SE MOVERÁN 90º
  miniservo1.write(90);
  miniservo2.write(90);
  pinMode(led, OUTPUT);//led será de salida
  
  //ULTRASONIDO
  pinMode (echoo, INPUT);
  pinMode (trig, OUTPUT);


}

void loop() {
  //CODIGO PRINCIPAL 
    digitalWrite(trig, LOW);
    digitalWrite(trig, HIGH);
    digitalWrite(trig, LOW);
    duracion = pulseIn(echoo, HIGH);
    distancia = (duracion/2)/29;
    Serial.print(distancia);
    Serial.println("cm");

    if(distancia <= 20){
        miniservo1.write(180);
        miniservo2.write(0);
        digitalWrite(led, HIGH);
        delay(2000);
    }else{
        miniservo1.write(90);
        miniservo2.write(90);
        digitalWrite(led, LOW);
        delay(2000);
    }
}

#include <Servo.h>

//PINES
const int touch = 37;
const int servo = 38;

Servo myservo;//coge informacion de la libreria

//VARIABLES
int angle = 0;
int estado_ultimo_toque;
int estado_tactil_actual;

void setup() {
  // CONFIGURACIÓN
  Serial.begin(9600);
  
  pinMode(touch, INPUT);
  myservo.attach(servo);
  
  myservo.write(angle);
  estado_tactil_actual = digitalRead(touch);
  
}

void loop() {
  // CODIGO PRINCIPAL

  estado_ultimo_toque = estado_tactil_actual;
  estado_tactil_actual = digitalRead(touch);

  if (estado_ultimo_toque == LOW && estado_tactil_actual == HIGH){
    Serial.println("touch");
    
    if (angle == 0)
        angle = 90;

    else
     if (angle == 90)
         angle = 0;
         
         myservo.write(angle);
    
  }
}

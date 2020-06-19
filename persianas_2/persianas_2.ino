#include <Servo.h>//libreria

//constante LDR Persianas 
int ldrx = A1;// constante del ldr
int v_luzx = 0;//constante

//PERSIANA DERECHA ARRIBA
Servo servo1;// para poder coger las cosas de la libreria
//PERSIANA DERECHA ABAJO
Servo servo2;// para poder coger las cosas de la libreria
//PERSIANA IZQUIERDA ARRIBA
Servo servo3;// para poder coger las cosas de la libreria
//PERSIANA IZQUIERDA ABAJO
Servo servo4;// para poder coger las cosas de la libreria


void setup() {
  //CONFIGURACIÓN
  Serial.begin(9600);
  pinMode(ldrx, INPUT); //declaracion LDR comun

  //PERSIANA DERECHA ARRIBA
  servo1.attach(28);// pin del servo
  servo1.write(0); //variable en el que en el angulo
                //escribiremos el angulo que queremos
                
  //PERSIANA DERECHA ABAJO
  servo2.attach(29);// pin del servo
  servo2.write(0); //variable en el que en el angulo 
                //escribiremos el angulo que queremos
  
  //PERSIANA IZQUIERDA ARRIBA
  servo3.attach(30);// pin del servo
  servo3.write(0); //variable en el que en el angulo
                //escribiremos el angulo que queremos

  //PERSIANA IZQUIERDA ABAJO
  servo4.attach(31);// pin del servo
  servo4.write(0); //variable en el que en el angulo
               //escribiremos el angulo que queremos

}

void Persianas(){
    //CODIGO PRINCIPAL
  v_luzx = analogRead(ldrx);

  if(v_luzx >= 130 && v_luzx <= 160){ //menos intensidad de luz, sube persiana
    servo1.write(0);//angulo cuando reciben ese rango de luz
    servo2.write(0);//angulo cuando reciben ese rango de luz
    servo3.write(0);//angulo cuando reciben ese rango de luz
    servo4.write(0);//angulo cuando reciben ese rango de luz
    Serial.print("minima intensidad de luz =");
    Serial.println(v_luzx);// se observa la luz que recibe
    
  }
    else if  (v_luzx > 180 && v_luzx < 300) //maxima intensidad baja persiana
  { 
    servo1.write(90);//angulo cuando reciben ese rango de luz
    servo2.write(90);//angulo cuando reciben ese rango de luz
    servo3.write(90);//angulo cuando reciben ese rango de luz
    servo4.write(90);//angulo cuando reciben ese rango de luz
    Serial.print("máxima intensidad =");
    Serial.println(v_luzx);// se observa la luz que recibe
    
  }
}

void loop() {
  Persianas();
}

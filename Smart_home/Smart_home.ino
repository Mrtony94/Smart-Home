//Librerias
#include <Servo.h>
#include <Keypad.h>
#include <Password.h>

//--------------------------------------------------------------------------------------------------------------
//PINES
//--------------------------------------------------------------------------------------------------------------
//SENSOR TEMPERATURA y HUMEDAD
const int Sensor = A2 ; // Pin que lee la temperatura
const int ventilador = 10; //pin digital 10
const int ventilador2 = 11; //Pin digital 11
//--------------------------------------------------------------------------------------------------------------
//ILUMINACION
//SENSOR PORCHE
const int ledporche = 26; // el pin donde ponemos el led
const int ldrporche = A0; // el pin donde ponemos el LDR
//SENSOR PUERTA
const int ledpuerta = 27; // el pin donde ponemos el led
const int ldrpuerta = A1; // el pin donde ponemos el LDR
//--------------------------------------------------------------------------------------------------------------
//TOUCH
const int touch = 37;
const int servo = 38;
Servo myservo; //coge informacion de la libreria
//variables
int angle = 0;
int estado_ultimo_toque;
int estado_tactil_actual;
//--------------------------------------------------------------------------------------------------------------
//SENSOR DE MOVIMIENTO SEGUNDA PLANTA
byte sensorfloor = 12;
byte ledfloor = 13;
int movimiento_second_floor_on;

//SENSOR SALON
byte sensorsalon = 22;
byte ledsalon = 23;
int movimiento_salon_on;

//SENSOR COCINA
byte sensorcocina = 25;
byte ledcocina = 24;
int movimiento_cocina_on;
//--------------------------------------------------------------------------------------------------------------
//RIEGO
#define bomba 39
#define sensor_humedad A8 
// cuanto mayor numero más seca estará la tierra
#define seco 700 
//--------------------------------------------------------------------------------------------------------------
//PERSIANAS
int ldrx = A4;//constante del ldr
int v_luzx = 0;//constante

//PERSIANA DERECHA ARRIBA
Servo servo1;//para poder coger las cosas de la libreria
//PERSIANA DERECHA ABAJO
Servo servo2;//para poder coger las cosas de la libreria
//PERSIANA IZQUIERDA ARRIBA
Servo servo3;//para poder coger las cosas de la libreria
//PERSIANA IZQUIERDA ABAJO
Servo servo4;//para poder coger las cosas de la libreria
//--------------------------------------------------------------------------------------------------------------
//GARAJE
//PINES DE ULTRASONIDO
#define echoo 32
#define trig 33
//PINES DE LOS SERVOS Y LED
Servo miniservo1;
Servo miniservo2;
int led = 34;
//VARIABLES
long duracion, distancia;
//--------------------------------------------------------------------------------------------------------------
//SISTEMA DE SEGURIDAD
//POSICIÓN DE ALARMA
boolean activada = false;
boolean activarAlarma = false;// Cuenta atras para la activacion de la alarma
boolean alarmaActivada = false; //cuenta atras para sonar
boolean estaActivada;

//CONSTANTES-VARIABLES
int ct = 15; //tiempo de calibración
int pir = 41;// conexion al pin 41 de arduino
int ledred = 42;// conexion al pin 42 de arduino
int ledgreen = 43;//conexion al pin 43 de arduino
int buzzer = 45;// conexion al pin 45 de arduino
int pantalla = 0;
int i;
int l;
//---------------------------------------
//TECLADO
const byte FILAS = 4;     // define numero de filas
const byte COLUMNAS = 4;    // define numero de columnas
// define la distribucion de teclas
char keys[FILAS][COLUMNAS] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};
byte pinesFilas[FILAS] = {9,8,7,6};   // pines correspondientes a las filas
byte pinesColumnas[COLUMNAS] = {5,4,3,2}; // pines correspondientes a las columnas
Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS);  // crea el teclado (objeto)
char tecla;
String clave = "1234";
String claveIntroducida;
boolean introducirClave;
//---------------------------------------
//--------------------------------------------------------------------------------------------------------------

void setup(){
    Serial.begin(9600);

    //SENSOR TEMPERATURA y HUMEDAD
    pinMode(ventilador,OUTPUT);
    pinMode(ventilador2,OUTPUT);

    //ILUMINACION
    //PORCHE
    pinMode(ledporche, OUTPUT);//le decimos que el led pin 26 será de salida
    pinMode(ledporche, INPUT);//le decimos que el LDR pin A0 será de entrada
    //PUERTA
    pinMode(ledpuerta, OUTPUT);//le decimos que el led pin 27 será de salida
    pinMode(ldrpuerta, INPUT);//le decimos que el LDR pin A1 será de entrada

    //TOUCH
    pinMode(touch, INPUT);
    myservo.attach(servo);
    myservo.write(angle);
    estado_tactil_actual = digitalRead(touch);

    //SENSOR DE MOVIMIENTO
    //SEGUNDA PLANTA
    pinMode(ledfloor,OUTPUT); //configurar como salida
    pinMode(sensorfloor, INPUT); // configurar como entrada
    //SALON
    pinMode(ledsalon,OUTPUT); //configurar como salida
    pinMode(sensorsalon, INPUT); // configurar como entrada
    //COCINA
    pinMode(ledcocina,OUTPUT); //configurar como salida
    pinMode(sensorcocina, INPUT); // configurar como entrada

    //RIEGO
    pinMode(bomba, OUTPUT);//configurar como salida
    pinMode(sensor_humedad,INPUT);//configurar como entrada
    
    //PERSIANAS
    pinMode(ldrx, INPUT); //declaracion LDR comun
    //PERSIANA DERECHA ARRIBA
    servo1.attach(28);// pin del servo
    servo1.write(0); //variable en el que en el angulo escribiremos el angulo que queremos
    //PERSIANA DERECHA ABAJO
    servo2.attach(29);// pin del servo
    servo2.write(0); //variable en el que en el angulo escribiremos el angulo que queremos
    //PERSIANA IZQUIERDA ARRIBA
    servo3.attach(30);// pin del servo
    servo3.write(0); //variable en el que en el angulo escribiremos el angulo que queremos
    //PERSIANA IZQUIERDA ABAJO
    servo4.attach(31);// pin del servo
    servo4.write(0); //variable en el que en el angulo escribiremos el angulo que queremos

    //GARAJE
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

    //SISTEMA DE SEGURIDAD
    pinMode(buzzer, OUTPUT);
    pinMode(ledred,OUTPUT);
    pinMode(ledgreen,OUTPUT);
    pinMode(pir,INPUT);
    calibracion_pir();
}

//FUNCIONES
void sensor_temperatura_humedad(){
    int lectura = analogRead(Sensor);
    float voltaje = 5.0 / 1024 * lectura;
    float temp = voltaje * 100;
    Serial.println(temp);
    delay(1000);

    if (temp >= 25){
        Serial.println("Ventilador esta encendido");
        digitalWrite(ventilador, HIGH);
        digitalWrite(ventilador2, HIGH);
        delay(2000);
    }else{
        digitalWrite(ventilador, LOW);
        digitalWrite(ventilador2, LOW);
    }
}

void iluminacion(){
    int ldrStatus_porche = analogRead(ldrporche); //leer valor LDR
    int ldrStatus_puerta = analogRead(ldrpuerta); //leer valor LDR

    if (ldrStatus_porche <= 150){
        digitalWrite(ledporche, HIGH);//la luz se enciende
        Serial.println("No hay sufuciente luz, enciende las luces");
        delay(2000);
    }else{
        digitalWrite(ledporche, LOW);//la luz se apaga
        Serial.println("Hay luz, apagar las luces");
        delay(2000);
    }
    if (ldrStatus_puerta <= 150){
        digitalWrite(ledpuerta, HIGH);//la luz se enciende
        Serial.println("No hay sufuciente luz, enciende las luces");
        delay(2000);
    }else{
        digitalWrite(ledpuerta, LOW);//la luz se apaga
        Serial.println("Hay luz, apagar las luces");
        delay(2000);
    }
}

void sensor_touch(){
    estado_ultimo_toque = estado_tactil_actual;
    estado_tactil_actual = digitalRead(touch);

    if(estado_ultimo_toque == LOW && estado_tactil_actual == HIGH){
        Serial.println("touch");
        if(angle == 0)
            angle = 90;
        else
            if(angle == 90)
                angle = 0;
                myservo.write(angle);     
    }
}

void sensor_de_movimiento(){
    //Segunda planta
    movimiento_second_floor_on = digitalRead(sensorfloor) == HIGH;
    if(movimiento_second_floor_on){
        Serial.println("movimiento");
        digitalWrite(ledfloor, HIGH); //se enciende el LED
        
    }else{
        Serial.println("NO hay movimiento");
        digitalWrite(ledfloor, LOW); //se apaga el LED
    }
    //COCINA
    movimiento_cocina_on = digitalRead(sensorcocina) == HIGH;
    if(movimiento_cocina_on){
        Serial.println("movimiento");
        digitalWrite(ledcocina, HIGH);
        
    }else{
        Serial.println("No hay movimiento");
        digitalWrite(ledcocina, LOW);
    }
    //SALON
    movimiento_salon_on = digitalRead(sensorsalon) == HIGH;
    if(movimiento_salon_on){
        Serial.println("movimiento");
        digitalWrite(ledsalon, HIGH);
        
    }else{
        Serial.println("NO movimiento");
        digitalWrite(ledsalon, LOW);
    }
}

void riego(){
  int SensorValue = analogRead(sensor_humedad); //coge una muestra de la humedad de la tierra
  Serial.print(SensorValue); Serial.print(" - ");
  
  if(SensorValue >= seco) 
  {
   // Si el suelo esta demasiado seco comienza a regar por unos segundos 
   // y luego se espera unos segundos antes de volver a medir la humedad
   Serial.println("Necesita agua");
   digitalWrite(bomba, LOW);
   
   delay(1000);
   
   digitalWrite(bomba, HIGH);
   
   delay(1000);
  }
  delay(500);
}

void persianas(){
    v_luzx = analogRead(ldrx);

    if(v_luzx >= 130 && v_luzx <= 160){ //menos intensidad de luz, sube persiana
        servo1.write(0);//angulo cuando reciben ese rango de luz
        servo2.write(0);//angulo cuando reciben ese rango de luz
        servo3.write(0);//angulo cuando reciben ese rango de luz
        servo4.write(0);//angulo cuando reciben ese rango de luz
        Serial.print("minima intensidad de luz =");
        Serial.println(v_luzx);// se observa la luz que recibe
        delay(500);
    }else if  (v_luzx > 180 && v_luzx < 300){ //maxima intensidad baja persiana
        servo1.write(90);//angulo cuando reciben ese rango de luz
        servo2.write(90);//angulo cuando reciben ese rango de luz
        servo3.write(90);//angulo cuando reciben ese rango de luz
        servo4.write(90);//angulo cuando reciben ese rango de luz
        Serial.print("máxima intensidad =");
        Serial.println(v_luzx);// se observa la luz que recibe
        delay(500);
    }
}

void garaje(){
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


//SISTEMA DE SEGURIDAD
void sistema_de_seguridad(){
  // CODIGO PRINCIPAL
    inicializacion_alarma();
    funcionamiento_alarma();
}

//Funciones-------------------------------------------------------------------
void calibracion_pir(){
    //INICIACIÓN DEL PIR
    Serial.println("Espere, ahora calibrando el sensor....");
    for(int i = 0; i <= ct; i++){ //vamos a darle un tiempo de calibracion
    Serial.print(((i*100)/ct)); //porcentaje de iniciacion, esperando 15 segundos
    Serial.print("%");
    Serial.println(" COMPLETADO.....");
    delay(1000);
    }

    Serial.println("Calibracion Completada Satisfactoriamente.");
    Serial.println("** SENSOR ACTIVO **");
    delay(50);
}

void inicializacion_alarma(){
    //PRINCIPIO DE EJECUCION --------------------------------------------------
    //si la alarma no está activada
    if (!alarmaActivada){
        if(pantalla == 0){
        //opcion A
        Serial.println("Pulsa 'A' para Activar la Alarma");
        //opcion B
        pantalla = 1;
        }
        tecla = teclado.getKey();
        if(tecla == 'A'){//se activa y la cuenta atras
            tone(buzzer, 1000, 200);
            activarAlarma = true;
        }
    }
}//Fin de la inicializacion de la alarma-------------------------------------

void funcionamiento_alarma(){
    if(activarAlarma){
        Serial.println("Inicializacion de la Alarma en... ");
        int cuenta_atras = 9;
        while (cuenta_atras != 0){
            Serial.println(cuenta_atras);
            cuenta_atras--;
            tone(buzzer,700,100);
            digitalWrite(ledred,HIGH);
            delay(500);
            digitalWrite(ledred,LOW);
            delay(500);
        }
        Serial.println("La Alarma ha sido Activada");
        activarAlarma = false;
        alarmaActivada = true;
    }

    //Con la Alarma activada nos encontramos en 2 situaciones que queramos desactivarla y pongamos bien el codigo o no
    if (alarmaActivada == true){
        //Activamos el Sensor de movimiento
        if(digitalRead(pir) == HIGH){
            //Cuando detecta movimiento, comienza a sonar el Buzzer
            tone(buzzer,1000);
            //Introduccion de Teclas, para desactivacion de la alarma
            int j = 5; //contraseña 5 digitos
            claveIntroducida ="";
            Serial.println("ALARMA SONANDO");
            Serial.println("Introduce la clave");
            activada = true;

            while(activada){
                tecla = teclado.getKey();
                if (tecla != NO_KEY){
                    if (tecla == '0'|| tecla == '1'|| tecla == '2'|| tecla == '3'||
                        tecla == '4'|| tecla == '5'|| tecla == '6'||  tecla == '7'||
                        tecla == '8'|| tecla == '9'){
                        //Añade cada valor que introducimos en el teclado a la variable 'tecla' en la primera posicion
                        //y vamos sumandole 1 al valor para añadirlo de forma continuada hasta completar la clave
                        claveIntroducida += tecla;
                        Serial.print("*");
                        j++;
                    }
                }
                //Una vez introducida la clave tenemos 2 opciones:
                //Si alfinal de la clave añadimos '#' borramos lo introducido y podemos volver a escribir o si escribimos mas de 9 digitos se borra
                if (j > 9 || tecla == '#' ){
                    claveIntroducida = "";
                    j = 5;
                    Serial.println("ALARMA SONANDO");
                    Serial.println("Ha habido un error vuelva a introducir la clave");
                }
                //Si alfinal de la clave añadimos '*' admitimos que la clave es la que queremos introducir (ok)
                if(tecla == '*'){
                    //Si la clave es correcta se apaga la alarma
                    if (claveIntroducida == clave){
                        activada = false;
                        alarmaActivada = false;
                        noTone(buzzer);
                        pantalla = 0;
                        digitalWrite(ledred,LOW);
                        digitalWrite(ledgreen,HIGH);
                        delay(2000);
                    //si la clave no es correcta, podemos volver a introducir la clave de nuevo.
                    }else if(claveIntroducida != clave){ //clave erronea
                        Serial.println("prueba de nuevo");
                        digitalWrite(ledred,HIGH);
                        delay(2000);
                        Serial.println("ALARMA SONANDO");
                        Serial.println("La clave no es correcta intentelo de nuevo: ");
                    }
                }
            }
            digitalWrite(ledred,LOW);
            digitalWrite(ledgreen,LOW);
        }
    }
}

void loop(){
    //Codigo Principal
    void sistema_de_seguridad();
    void iluminacion();
    void sensor_touch();
    void sensor_de_movimiento();
    void riego();
    void persianas();
    void garaje();
}

//LIBRERIAS
#include <Keypad.h>
#include <Password.h>

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

//--------------------------------------------------------------------------------------

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
//--------------------------------------------------------------------------------------

void setup() {
  // CONFIGURACIÓN
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(ledred,OUTPUT);
  pinMode(ledgreen,OUTPUT);
  pinMode(pir,INPUT);
  calibracion_pir();
}

void loop() {
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
  //Fin de la inicializacion de la alarma-------------------------------------
}

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
//Fin de las Funciones-----------------------------------------------------------

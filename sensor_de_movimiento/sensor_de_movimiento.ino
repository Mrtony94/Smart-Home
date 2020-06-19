//SENSOR SECOND FLOOR
byte sensorfloor = 12;
byte ledfloor = 13;
int movimiento_second_floor_on;
int ct = 15; //tiempo de calibración

//SENSOR SALON
byte sensorsalon = 22;
byte ledsalon = 23;
int movimiento_salon_on;

//SENSOR COCINA
byte sensorcocina = 25;
byte ledcocina = 24;
int movimiento_cocina_on;

void setup() {
  // CONFIGURAR
  //SECOND FLOOR
  pinMode(ledfloor,OUTPUT); //configurar como salida
  pinMode(sensorfloor, INPUT); // configurar como entrada
  
  //SALON
  pinMode(ledsalon,OUTPUT); //configurar como salida
  pinMode(sensorsalon, INPUT); // configurar como entrada
  

  //COCINA
  pinMode(ledcocina,OUTPUT); //configurar como salida
  pinMode(sensorcocina, INPUT); // configurar como entrada

 Serial.begin(9600);//configurar puerto serial
 
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

void sensor_movimiento_second_floor() {
  // CODIGO PRINCIPAL
  //Encender led si hay movimiento
  movimiento_second_floor_on = digitalRead(sensorfloor) == HIGH ;
 if(movimiento_second_floor_on){           //leer el pin del sensor
  Serial.println("movimiento");
  digitalWrite(ledfloor,HIGH);//se enciende Led
 
 }else{
  Serial.println("NO movimiento");
  digitalWrite(ledfloor,LOW);        //se apaga el Led
 }
}

void sensor_movimiento_cocina(){
   // CODIGO PRINCIPAL
  //Encender led si hay movimiento
  movimiento_cocina_on = digitalRead(sensorcocina) == HIGH ;
 if(movimiento_cocina_on){           //leer el pin del sensor
  Serial.println("movimiento");
  digitalWrite(ledcocina,HIGH);//se enciende Led
 
 }else{
  Serial.println("NO movimiento");
  digitalWrite(ledcocina,LOW);        //se apaga el Led
 } 
}

void sensor_movimiento_salon(){
   // CODIGO PRINCIPAL
  //Encender led si hay movimiento
  movimiento_salon_on = digitalRead(sensorsalon) == HIGH ;
 if(movimiento_salon_on){           //leer el pin del sensor
  Serial.println("movimiento");
  digitalWrite(ledsalon,HIGH);//se enciende Led
  
 }else{
  Serial.println("NO movimiento");
  digitalWrite(ledsalon,LOW);        //se apaga el Led
 }  
}
void loop(){
  sensor_movimiento_second_floor();
  sensor_movimiento_cocina();
  sensor_movimiento_salon();

}

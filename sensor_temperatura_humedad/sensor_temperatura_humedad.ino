//SENSOR TEMPERATURA CASA
const int Sensor = A2 ;             // Pin que lee la temperatura
const int ventilador = 10;
const int ventilador2 = 11;

void setup(){
  //CONFIGURACIÓN
  Serial.begin(9600);  
  pinMode(ventilador,OUTPUT);
  pinMode(ventilador2,OUTPUT);

}

void loop(){
  //CODIGO PRINCIPAL
  
  int lectura = analogRead(Sensor);
  float voltaje = 5.0 /1024 * lectura ; 
  float temp = voltaje * 100  ;
  Serial.println(temp) ;
  delay(1000);

  if (temp >=27){
    Serial.println("Ventilador encendido");
    digitalWrite(ventilador,HIGH);
    digitalWrite(ventilador2,HIGH);
    delay(2000);
    
  }else{
    digitalWrite(ventilador,LOW);
    digitalWrite(ventilador2,LOW);
  }
}

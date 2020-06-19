//SENSOR PORCHE
const int ledporche = 26; // el pin donde ponemos el led
const int ldrporche = A0; // el pin donde ponemos el LDR

//SENSOR PUERTA
const int ledpuerta = 27; // el pin donde ponemos el led
const int ldrpuerta = A4; // el pin donde ponemos el LDR

void setup() {
  // CONFIGURACIÓN
  Serial.begin(9600);
  //PORCHE
  pinMode(ledporche, OUTPUT);//le decimos que el led pin 26 será de salida
  pinMode(ldrporche, INPUT);//le decimos que el LDR pin A0 será de entrada

  //PUERTA
  pinMode(ledpuerta, OUTPUT);//le decimos que el led pin 27 será de salida
  pinMode(ldrpuerta, INPUT);//le decimos que el LDR pin A1 será de entrada
   
}

void sensor_porche(){
  //CODIGO PRINCIPAL
  int ldrStatus = analogRead(ldrporche);//lee el valor del LDR

  if (ldrStatus <=150){
    digitalWrite(ledporche, HIGH);// el led se enciende
    Serial.println("no hay luz, el led se enciende");
    delay(2000);
  }

  else {

    digitalWrite(ledporche, LOW);//led se apaga
    Serial.println("hay luz, el led se apaga");
    delay(2000);
  }
}

void sensor_puerta(){
  //CODIGO PRINCIPAL
  int ldrStatus = analogRead(ldrpuerta);//lee el valor del LDR

  if (ldrStatus <=150){
    digitalWrite(ledpuerta, HIGH);// el led se enciende
    Serial.println("no hay luz, el led se enciende");
    delay(2000);
  }

  else {

    digitalWrite(ledpuerta, LOW);//led se apaga
    Serial.println("hay luz, el led se apaga");
    delay(2000);
  }
}
void loop() {
  sensor_porche();
  sensor_puerta();

}

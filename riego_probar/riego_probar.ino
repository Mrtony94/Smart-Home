#define bomba 39
#define sensor_humedad A8

// cuanto mayor numero más seca estará la tierra
#define seco 700

void setup()
{
  Serial.begin(9600);
  pinMode(sensor_humedad, INPUT);
  pinMode(bomba, OUTPUT);
}

void loop()
{
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

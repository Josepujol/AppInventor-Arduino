#include <SoftwareSerial.h>
SoftwareSerial I2CBT(10, 11);
// El TX del módulo BT va al pin 10 del Arduino
// El RX del módulo BT va al pin 11 del Arduino

int incomingByte;      // variable para leer los bytes de entrada
// variables temperatura
const int LM35Pin = A0; // pin conexion
float temperature = 0; // variable almacenar lectura

void setup() {
  // inicializamos la comunicacion serie
  Serial.begin(9600);
  // inicializamos la comunicacion serie BT
  I2CBT.begin(9600);
}

void loop() {
  // leemos el sensor
  int lectura = analogRead(LM35Pin); // Valor entre 0 y 1023
  // convertimos el sensor a ºC
  temperature = (5.0 * lectura * 100.0) / 1024.0;
  // Mostramos el valor de la temperatura
  Serial.print("Temperatura:");
  Serial.print(temperature);
  Serial.println("ºC");

  // comprobamos si hay datos de entrada
  if (I2CBT.available() > 0) {
    // lectura del byte mas antiguo del buffer serial
    incomingByte = I2CBT.read();
    // si el byte es T envia dato de temperatura
    if (incomingByte == 'T') {
      I2CBT.print(temperature);
      //I2CBT.println(" ºC");
    }
  }
  delay(100);
}

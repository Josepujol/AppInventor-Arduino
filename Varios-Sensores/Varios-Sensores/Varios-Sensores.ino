#include <SoftwareSerial.h>
SoftwareSerial I2CBT(10, 11);
// El TX del módulo BT va al pin 10 del Arduino
// El RX del módulo BT va al pin 11 del Arduino

// variables sensor temperatura
const int LM35Pin = A0;
float temperature = 0;

//variables sensor luz
const int LDRPin = A1;
int luz = 0;

void setup() {
  // inicializamos la comunicacion serie BT
  I2CBT.begin(9600);
}

void loop() {
  // leemos el sensor temperatura
  int lectura = analogRead(LM35Pin); // Valor entre 0 y 1023
  // convertimos el sensor a ºC
  temperature = (5.0 * lectura * 100.0) / 1024.0;
  //leemos sensor luz
  luz = analogRead(LDRPin); // Valor entre 0 y 1023
  // Enviamos los datos
  I2CBT.print(temperature);
  I2CBT.print(" ºC");
  I2CBT.print("|"); // separador de datos
  I2CBT.print(luz);
  I2CBT.print(" Valor luz");
  I2CBT.print("|"); // separador de datos
  delay(1000);

}

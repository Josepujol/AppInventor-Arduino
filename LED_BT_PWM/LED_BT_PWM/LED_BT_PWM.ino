#include <SoftwareSerial.h> // incluir la libreria software serial
const int rxBTPin = 11; // El RX del módulo BT va al pin 11 del Arduino
const int txBTPin = 10; // El TX del módulo BT va al pin 10 del Arduino
SoftwareSerial I2CBT(txBTPin, rxBTPin);

const int ledPin = 9; // pin al que el led esta conectado
int incomingByte;      // variable para leer los bytes de entrada
int value = 0;  // variable para almacenar el valor numerico
int pwmValue = 0; // variable para enviar el codigo pwm al led

void setup() {
  // inicializamos el led como pin digital salida
  Serial.begin(9600);
  // inicializamos la comunicacion serie BT
  I2CBT.begin(9600);
}

void loop() {
  // comprobamos si hay datos de entrada
  if (I2CBT.available() > 0) {
    // lectura del byte mas antiguo del buffer serial
    incomingByte = I2CBT.read();
    if (incomingByte >= '0' && incomingByte <= '9') {
      //Acumula los datos numericos multiplicando por 10 el valor acumulado
      value = (value * 10) + (incomingByte - '0'); // Resta 48 que es el valor decimal del 0 ASCII
    }
    else if (incomingByte == '>') // uso > como finalizador
    {
      pwmValue = value;   // Guarda el valor en la variable pwmValue
      Serial.println(pwmValue);     // Lo imprime por monitor serie
      value = 0;  // Dejamos lista la variable para volver a escribir en ella
    }
  }
  analogWrite(ledPin, pwmValue);   // Escribimos el valor PWM en el LED
}

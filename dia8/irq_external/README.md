# Paso 1 - Implentacion del programa en el ESP32

## Hardware

### Lista de componentes

|Elemento|Descripcion|
|--|--|
|1|Placa de desarrollo ESP32|
|2|KY-004 Button (37 sensor Kid - Ladzo)|

### Esquematico

A continuación se muestra esquematico del circuito:

![sch](button_irq-ESP32_sch.png)

### Conexion

A continuación se muestra el diagrama de conexión:

![Diagrama](button_irq-ESP32_bb.png)

## Sofware

El programa que se descargara en la ESP32 se muestra a continuación:

### Caso 1

**Simulación**: [link](https://wokwi.com/projects/376220446820566017)

```ino
#include <Arduino.h>

int ledPin = LED_BUILTIN;  // LED is attached to digital pin 2
int x = 0;                 // variable to be updated by the interrupt
int buttonPin = 4;         // buttton is attached to digital pin 4

// Interrupt service routine for interrupt 0
void increment() {
  x++;
  digitalWrite(ledPin, HIGH);
}

// Setup
void setup() {
  //enable interrupt 0 (pin 2) which is connected to a button
  //jump to the increment function on rising edge
  pinMode(ledPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPin), increment, RISING);
  Serial.begin(9600);  //turn on serial communication
}

// loop
void loop() {
  digitalWrite(ledPin, LOW);
  delay(3000); //pretend to be doing something useful
  Serial.println(x, DEC); //print x to serial monitor
}
```

### Caso 2

**Simulación**: [link](https://wokwi.com/projects/376222724903465985)

```ino
#include <Arduino.h>

const int DEBOUNCE_DELAY = 300; // debounce delay 
int ledPin = LED_BUILTIN;  // LED is attached to digital pin 2
int x = 0;                 // variable to be updated by the interrupt
int buttonPin = 4;         // buttton is attached to digital pin 4

//variables to keep track of the timing of recent interrupts
unsigned long button_time = 0;  
unsigned long last_button_time = 0; 

// declaration ISR
void increment(); 

void setup() {
  //enable interrupt 0 (pin 2) which is connected to a button
  //jump to the increment function on rising edge
  pinMode(ledPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPin), increment, RISING);
  Serial.begin(9600);  //turn on serial communication
}

void loop() {
  digitalWrite(ledPin, LOW);
  delay(3000); //pretend to be doing something useful
  Serial.println(x, DEC); //print x to serial monitor
}

// Interrupt service routine for interrupt 0
void increment() {
  button_time = millis();
  //check to see if increment() was called in the last 250 milliseconds
  if (button_time - last_button_time > DEBOUNCE_DELAY) {
    x++;
    digitalWrite(ledPin, HIGH);
    last_button_time = button_time;
  }
}
```

## Prueba

A continuación se 
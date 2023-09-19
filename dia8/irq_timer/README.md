# Paso 1 - Implentacion del programa en el ESP32

## Hardware

### Lista de componentes

|Elemento|Descripcion|
|--|--|
|1|Placa de desarrollo ESP32|


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


// Inputs
const int LED_PIN = LED_BUILTIN; // LED_PIN (GPIO2)

// Timers
hw_timer_t * timer = NULL;       // H/W timer 

// Variables (Volatile: They're change in the ISR)
volatile int led_state = LOW;  
volatile uint32_t isrCounter = 0; // Interrupt counter


//ISR: Defining Inerrupt function with IRAM_ATTR for faster access
void ARDUINO_ISR_ATTR onTimer(){
  // Increment the counter and set the time of ISR
  isrCounter++;
  led_state = !led_state; // Change the led's state
}

void setup() {
  // I/O configure
  pinMode (LED_PIN, OUTPUT);
  // Serial configuration
  Serial.begin(9600);

  

  /*
  Step1: initialize timerBegin() Function
  
     timer speed (Hz) = Timer clock speed (Mhz) / prescaler

  */

  
  // timer 0, prescalar: 80, UP counting
  timer = timerBegin(0    /* timer 0*/, 
                     80,  /* Preescaler: 80 */
                     true /* Counting: UP (true)*/ 
                    );

  /*
  Step2: Attach Interrupt
  */

  // Attach onTimer function to our timer.
  timerAttachInterrupt(timer, &onTimer, true);

  /*
  Step3:  Define the match timer value 
  */

  // Set alarm to call onTimer function every second (value in microseconds).
  timerAlarmWrite(timer, 
                  1000000, /* Irq cada 1000000us = 1s */
                  true     /* Repeat the alarm (true) */
                 );

  // Start an alarm (Enable Timer with interrupt (Alarm Enable))
  timerAlarmEnable(timer);
}

void loop() {
  // Print it
  digitalWrite(LED_PIN, led_state);
  Serial.print("Interrupt counter: ");
  Serial.println(isrCounter);
  delay(100);
}
```


## Prueba





## Puertos GPIO

* https://learn.sparkfun.com/tutorials/processor-interrupts-with-arduino/all
* https://programarfacil.com/blog/arduino-blog/interrupciones-con-arduino-ejemplo-practico/
* https://www.luisllamas.es/que-son-y-como-usar-interrupciones-en-arduino/
* https://randomnerdtutorials.com/esp32-pir-motion-sensor-interrupts-timers/
* https://www.cpe.ku.ac.th/~cpj/219335/slides/05-concurrency.pdf
* https://randomnerdtutorials.com/esp32-dual-core-arduino-ide/

**Codigo tomado de**: https://learn.sparkfun.com/tutorials/processor-interrupts-with-arduino/all



```ino
int ledPin = LED_BUILTIN;  // LED is attached to digital pin 2
int x = 0;                 // variable to be updated by the interrupt
int buttonPin = 4;         // buttton is attached to digital pin 4

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
  x++;
  digitalWrite(ledPin, HIGH);
}
```

**Simulación**: [link](https://wokwi.com/projects/376220446820566017)


```ino
int ledPin = LED_BUILTIN;  // LED is attached to digital pin 2
int x = 0;                 // variable to be updated by the interrupt
int buttonPin = 4;         // buttton is attached to digital pin 4

//variables to keep track of the timing of recent interrupts
unsigned long button_time = 0;  
unsigned long last_button_time = 0; 

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
  if (button_time - last_button_time > 250) {
    x++;
    digitalWrite(ledPin, HIGH);
    last_button_time = button_time;
  }
}
```

**Simulación**: [link](https://wokwi.com/projects/376222724903465985)



## Timer

Referencia:
* https://www.electronicwings.com/esp32/esp32-timer-interrupts
* https://www.sparkfun.com/news/2613
* https://circuitdigest.com/microcontroller-projects/esp32-timers-and-timer-interrupts
* https://deepbluembedded.com/esp32-timers-timer-interrupt-tutorial-arduino-ide/
   
```ino
/*
 Repeat timer example

 This example shows how to use hardware timer in ESP32. The timer calls onTimer
 function every second. The timer can be stopped with button attached to PIN 0
 (IO0).

 This example code is in the public domain.
 */


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


Lo que vamos de timer [link](https://wokwi.com/projects/376235742395502593)


----

```ino
int pinA = 3; // Connected to CLK
int pinB = 4; // Connected to DT

int encoderPosCount = 0;

int pinALast;
int aVal;
boolean bCW;

void setup() {
  pinMode (pinA,INPUT);
  pinMode (pinB,INPUT);
  /* Read Pin A 
  Whatever state it's in will reflect the last position
  */
  pinALast = digitalRead(pinA);
  Serial.begin (9600);
}

void loop() {
  aVal = digitalRead(pinA);
  if (aVal != pinALast) { 
    // Means the knob is rotating
    if (digitalRead(pinB) != aVal) { 
      // Means pin A Changed first - We're Rotating Clockwise
      encoderPosCount ++;
      bCW = true;
    }
    else { 
      // Otherwise B changed first and we're
      moving CCW bCW = false;
      encoderPosCount--;
    }
    Serial.print ("Rotated: ");
    if (bCW) {
      Serial.println ("clockwise");
    } 
    else {
      Serial.println("counterclockwise");
    }
    Serial.print("Encoder Position: ");
    Serial.println(encoderPosCount);
  }
  pinALast = aVal;
}

```

----


* https://www.theengineeringprojects.com/2021/12/esp32-interrupts.html
* https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/api/timer.html
* https://docs.espressif.com/projects/esp-idf/en/v4.3/esp32/api-reference/peripherals/timer.html
* https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/
* https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/api/timer.html
* https://deepbluembedded.com/esp32-timers-timer-interrupt-tutorial-arduino-ide/
* https://randomnerdtutorials.com/esp8266-nodemcu-big-timer-node-red/
* https://www.arduino.cc/reference/en/libraries/esp32timerinterrupt/
* https://github.com/khoih-prog/ESP32TimerInterrupt
* https://github.com/khoih-prog/ESP32TimerInterrupt/tree/master/examples/multiFileProject

* https://randomnerdtutorials.com/esp32-pir-motion-sensor-interrupts-timers/
* https://randomnerdtutorials.com/micropython-interrupts-esp32-esp8266/
* https://learn.sparkfun.com/tutorials/processor-interrupts-with-arduino/all
* https://github.com/sparkfun/processor_interrupt_examples
* https://learn.adafruit.com/cooperative-multitasking-in-circuitpython-with-asyncio/overview
* https://lastminuteengineers.com/handling-esp32-gpio-interrupts-tutorial/
* https://deepbluembedded.com/esp32-external-interrupts-pins-arduino-examples/
* https://www.sparkfun.com/news/2613
* https://www.sparkfun.com/news/2608
* https://www.sparkfun.com/news/2577
* https://programarfacil.com/blog/arduino-blog/interrupciones-con-arduino-ejemplo-practico/
* https://www.luisllamas.es/que-son-y-como-usar-interrupciones-en-arduino/
* https://descubrearduino.com/interrupciones-esp32-gpio/
* https://www.electrogeekshop.com/esp32-arduino-interrupciones-timer-2/
* https://www.arduino.cc/reference/en/language/functions/interrupts/interrupts/
* https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
* https://controlautomaticoeducacion.com/arduino/interrupciones-arduino/
* https://www.theengineeringprojects.com/2021/12/esp32-interrupts.html

## Referencias

* http://stefanfrings.de/multithreading_arduino/
* https://hackaday.com/2021/03/17/running-57-threads-at-once-on-the-arduino-uno/
* https://www.arduino.cc/reference/en/libraries/arduinothread/
* https://www.digikey.com/en/maker/blogs/2022/how-to-write-multi-threaded-arduino-programs
* https://github.com/ivanseidel/ArduinoThread
* https://learn.adafruit.com/cooperative-multitasking-in-circuitpython-with-asyncio/overview
* https://wiki.seeedstudio.com/Wio-Terminal-TinyML-EI-4/
* https://wiki.seeedstudio.com/reServer-Getting-Started/
* https://www.seeedstudio.com/blog/2021/05/11/multitasking-with-arduino-millis-rtos-more/
* https://www.hackster.io/485734/azure-rtos-threadx-for-arduino-101-threads-963a8d
* 
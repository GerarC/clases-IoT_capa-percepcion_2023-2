# Programación concurrente

Ejemplo realizado en clase (21/09/2023)

## Ejemplos


### Code 1 

Poner a titilar un led usando polling

```ino
#define LED_PIN LED_BUILTIN   // P2 (GPIO2)

int cnt = 0;

void setup() {
  //
  pinMode(LED_PIN, OUTPUT);
  //
  Serial.begin(9600);
  Serial.print("Debug: ");
  Serial.println(cnt);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  delay(500);  
  Serial.println(++cnt);
}
```

**Simulación**: [link](https://wokwi.com/projects/376622730717971457)

### Code 2

Poner a titilar un led usando interrupciones

```ino
#define LED_PIN LED_BUILTIN   // P2 (GPIO2)
#define DELAY 500
//  Timer
hw_timer_t *timer_500m;   

volatile int cnt = 0;

// IRQ  handler
void ARDUINO_ISR_ATTR event_500m(){
  // Increment the counter and set the time of ISR
  cnt++;
  Serial.println(cnt);
}

void setup() {
  //
  pinMode(LED_PIN, OUTPUT);
  // Timer
  timer_500m = timerBegin(0, 80, true);
  timerAttachInterrupt(timer_500m, &event_500m, true);
  timerAlarmWrite(timer_500m, DELAY*1000, true);  //
  Serial.begin(9600);
  Serial.print("Debug: ");
  Serial.println(cnt);
  timerAlarmEnable(timer_500m);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  delay(500);  
  //Serial.println(cnt);
}
```

**Simulación**: [link](https://wokwi.com/projects/376622818935719937)

### Code 3 

Poner a titilar un led usando hilos

```ino
#define LED_PIN LED_BUILTIN   // P2 (GPIO2)
#define DELAY 500
  
int cnt = 0;
int led_state = LOW; 

TaskHandle_t t1;

void blink_500m(void *parameter) {
  // Increment the counter and set the time of ISR
  for(;;) {
    led_state = !led_state;
    digitalWrite(LED_PIN, led_state); 
    Serial.println(cnt);
    delay(DELAY);
    cnt++;
  }
}

void setup() {
  //
  pinMode(LED_PIN, OUTPUT);
  // Hilo
  cnt = 0;
  Serial.begin(9600);
  Serial.print("Debug: ");
  led_state = LOW;
  xTaskCreatePinnedToCore(
      blink_500m, /* Function to implement the task */
      "blink_500m", /* Name of the task */
      10000,  /* Stack size in words */
      NULL,  /* Task input parameter */
      0,  /* Priority of the task */
      &t1,  /* Task handle. */
      0); /* Core where the task should run */
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(4*DELAY); // Para que este hilo lo se apodere tanto de la CPU
}
```

**Simulación**: [link](https://wokwi.com/projects/376624085464601601)

## Code 5 

Poner a titilar un led y enviar dos mensajes seriales diferentes que simulen la actividad de lectura del valor de un sensor. Use interrupciones.

```ino
#define LED_PIN LED_BUILTIN   // P2 (GPIO2)
#define DELAY 500
#define SAMPLE_S1 1
#define SAMPLE_S2 2

//  Timer
hw_timer_t *timer_500m;   

int cnt1 = 0;
int cnt2 = 0;
volatile int EVENT_TRIGGER = LOW;
int led_state = LOW; 
// IRQ  handler
void ARDUINO_ISR_ATTR event_500m(){
  // Increment the counter and set the time of ISR
  EVENT_TRIGGER = HIGH;
}

void setup() {
  //
  pinMode(LED_PIN, OUTPUT);
  // Timer
  timer_500m = timerBegin(0, 80, true);
  timerAttachInterrupt(timer_500m, &event_500m, true);
  timerAlarmWrite(timer_500m, DELAY*1000, true);  //
  Serial.begin(9600);
  Serial.print("Debug: ");
  timerAlarmEnable(timer_500m);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  delay(500);  
  Serial.println(cnt);
  */
  if(EVENT_TRIGGER) {
    // Logica 
    led_state = !led_state; 
    digitalWrite(LED_PIN,led_state);  
    cnt1++; 
    cnt2++;   
    // 
    EVENT_TRIGGER = LOW; // Reconocer 
  }
  if(cnt1 >= 1) {
    Serial.println("Sensor (1)");
    cnt1 = 0;   
  } 
  if(cnt2 >= 2) {
    Serial.println("Sensor (2)");
    cnt2 = 0;   
  } 
}
```

**Simulación**: [link](https://wokwi.com/projects/376624306513869825)

**Nota**: Revisar la simulación esta *muy lenta*.

### Code 6 

Poner a titilar un led y enviar dos mensajes seriales diferentes que simulen la actividad de lectura del valor de un sensor. Use hilos.


```ino
#define LED_PIN LED_BUILTIN   // P2 (GPIO2)
#define DELAY 500

int led_state = LOW; 

TaskHandle_t t1, t2;

void sensor1_sample( void *parameter) {
  for(;;) {
    Serial.println("Sensor (S1)");
    delay(DELAY);
  }
}

void sensor2_sample( void *parameter) {
  for(;;) {
    Serial.println("Sensor (S2)");
    delay(2*DELAY);
  }
}

void setup() {
  //
  pinMode(LED_PIN, OUTPUT);
  // hilo
  xTaskCreatePinnedToCore(
      sensor1_sample, /* Function to implement the task */
      "sensor1", /* Name of the task */
      10000,  /* Stack size in words */
      NULL,  /* Task input parameter */
      0,  /* Priority of the task */
      &t1,  /* Task handle. */
      0); /* Core where the task should run */
  xTaskCreatePinnedToCore(
      sensor2_sample, /* Function to implement the task */
      "sensor2", /* Name of the task */
      10000,  /* Stack size in words */
      NULL,  /* Task input parameter */
      0,  /* Priority of the task */
      &t2,  /* Task handle. */
      0); /* Core where the task should run */
  delay(DELAY);
  Serial.begin(9600);
  Serial.print("Debug: ");
  led_state = LOW;
}

void loop() {
  led_state = !led_state;
  digitalWrite(LED_PIN, led_state);
  delay(DELAY);
}
```

**Simulación**: [link](https://wokwi.com/projects/376624520883710977)

## Reto

* https://randomnerdtutorials.com/esp32-over-the-air-ota-programming/

## Referencias

* https://www.electrosoftcloud.com/freertos-en-esp32-esp8266-multi-tarea/
* https://www.aranacorp.com/es/programa-multitarea-con-esp32-y-freertos/
* https://docs.espressif.com/projects/esp-idf/en/v4.3/esp32/api-reference/system/freertos.html
* https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/freertos.html
* https://randomnerdtutorials.com/esp32-dual-core-arduino-ide/
* https://openthread.io/guides/border-router/espressif-esp32?hl=es-419
* https://www.circuitstate.com/tutorials/how-to-write-parallel-multitasking-applications-for-esp32-using-freertos-arduino/
* https://community.blynk.cc/t/tutorial-esp32-non-blocking-and-concurrent-function-execution/29828
* https://www.instructables.com/Parallelism-and-Much-More-on-the-T-Pico-C3/
* https://softwaremakeshardware.wordpress.com/tag/esp32/
* http://fab.cba.mit.edu/classes/863.16/doc/tutorials/ESP32/index.html
* https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/pthread.html
* https://github.com/espressif/arduino-esp32
* https://github.com/tomerweller/esp32-rtos-webclient
* https://www.exploringarduino.com/
* https://www.exploringarduino.com/content2/ch13/
* https://www.luisllamas.es/esp32-adc/
* https://randomnerdtutorials.com/esp32-pwm-arduino-ide/
* https://www.luisllamas.es/esp32-pwm/



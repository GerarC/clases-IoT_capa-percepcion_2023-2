# Ejemplo 2


### Thing 1 - ESP-PIR (Simulacion)

```h
#pragma once

#include <string>

using namespace std;

// ESP32 I/O config
// Alarm
const byte LIGHT_PIN = LED_BUILTIN; 

// PIR
const byte PIR_MOTION_SENSOR = 5; // GPIO5

// WiFi credentials
const char *SSID = "Wokwi-GUEST";
const char *PASSWORD = "";

// MQTT settings
const string ID = "thing-001";

const string BROKER = "test.mosquitto.org";
const string CLIENT_NAME = ID + "ESP32-PIR";

const string TOPIC = "store/sensor/pir";
```

```cpp
#include <WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>

#include "config.h"

const unsigned MOV_TIMER = 1000;  // 1000 ms

WiFiClient espClient;
PubSubClient client(espClient); // Setup MQTT client

int motion_detected = LOW; 

// Timer

hw_timer_t * timer = NULL;       // H/W timer 

volatile bool event_timer = false; // Interrupt counter

void ARDUINO_ISR_ATTR onTimer(){
  event_timer = true; // Event timer: bandera 1 s 
}

void setup_timer() {
  timer = timerBegin (0    /* timer 0*/, 
                     80,   /* Preescaler: 80 */
                     true  /* Counting: UP (true)*/ 
                    );
  timerAttachInterrupt(timer, &onTimer, true);

  timerAlarmWrite(timer, 
                  MOV_TIMER*1000, /* Irq cada 1000*1000ms = 1 s */
                  true            /* Repeat the alarm (true) */
                 );
  timerAlarmEnable(timer);
}

// --- ESP32

void setup_ports() {
  pinMode(LIGHT_PIN, OUTPUT); 
  pinMode(PIR_MOTION_SENSOR, INPUT); 
}



// ---- Wifi

void connectWiFi() {
  Serial.print("Connecting to ");
  Serial.print(SSID);
  while (WiFi.status() != WL_CONNECTED) {   
    Serial.print(".");
    WiFi.begin(SSID, PASSWORD, 6);
    delay(500);
  }
  Serial.println();
  Serial.print(ID.c_str());
  Serial.println(" connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// ---- MQTT


void reconnectMQTTClient() {
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    if (client.connect(CLIENT_NAME.c_str())) {
      Serial.print("connected to Broker: ");
      Serial.println(BROKER.c_str());
      // Topic(s) subscription
      client.subscribe(TOPIC.c_str());
    }
    else {
      Serial.print("Retying in 5 seconds - failed, rc=");
      Serial.println(client.state());
      delay(5000);
    }
  }
}

void createMQTTClient() {
  client.setServer(BROKER.c_str(), 1883);
  reconnectMQTTClient();
}

void setup() {
  // Setup ports
  setup_ports();
  // Serial setup
  Serial.begin(9600);
  while (!Serial)
    ; // Wait for Serial to be ready
  delay(1000);
  connectWiFi();
  createMQTTClient();
  setup_timer();
}

void loop() {
  reconnectMQTTClient();
  client.loop();
  if (event_timer) {
    event_timer = false; // Reconocimiento de la irq (evento)
    motion_detected = digitalRead(PIR_MOTION_SENSOR);

    digitalWrite(LIGHT_PIN,motion_detected);   
    Serial.println("Hi, people is coming");
    DynamicJsonDocument doc(1024);
    doc["alarm"] = motion_detected;
    
    string telemetry;
    serializeJson(doc, telemetry);
    Serial.print("Sending telemetry ");
    Serial.println(telemetry.c_str());
    client.publish(TOPIC.c_str(), telemetry.c_str());
  }
  delay(100);  
}
```

### Thing 2 - ESP-ALARM (Simulacion)


**Archivo**: config.h

```h
#pragma once

#include <string>

using namespace std;

// ESP32 I/O config
// Alarm
const byte LIGHT_PIN = LED_BUILTIN; 
// Buzzer
const byte BUZZER_PIN = 5;

// WiFi credentials
const char *SSID = "Wokwi-GUEST";
const char *PASSWORD = "";

// MQTT settings
const string ID = "thing-002";

const string BROKER = "test.mosquitto.org";
const string CLIENT_NAME = ID + "ESP32-ALARM";

const string TOPIC = "store/sensor/pir";
```

**Archivo**: main.cpp

```cpp
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#include "config.h"

WiFiClient espClient;
PubSubClient client(espClient); // Setup MQTT client

const int BUZZER_CHANNEL = 0;
const int FREQ = 1000;
const int RESOLUTION = 8;


// --- ESP32

void setup_ports() {
  pinMode(LIGHT_PIN, OUTPUT); // Configure LIGHT_PIN as an output
  // BUZZER PWM init
  ledcSetup(BUZZER_CHANNEL, FREQ, RESOLUTION);
  // BUZZER pin init
  ledcAttachPin(BUZZER_PIN, BUZZER_CHANNEL); 
}

// ---- Wifi

void connectWiFi() {
  Serial.print("Connecting to ");
  Serial.print(SSID);
  while (WiFi.status() != WL_CONNECTED) {   
    Serial.print(".");
    WiFi.begin(SSID, PASSWORD, 6);
    delay(500);
  }
  Serial.println();
  Serial.print(ID.c_str());
  Serial.println(" connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// ---- MQTT


// Handle incomming messages from the broker
void clientCallback(char* topic, byte* payload, unsigned int length) {
  String response;

  for (int i = 0; i < length; i++) {
    response += (char)payload[i];
  }
  Serial.print("Message arrived [");
  Serial.print(TOPIC.c_str());
  Serial.print("] ");
  Serial.println(response);

  
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, response);
  JsonObject obj = doc.as<JsonObject>();

  bool alarm_on = obj["alarm"];
  if(alarm_on == HIGH)  {
    // Turn the light on
    digitalWrite(LIGHT_PIN, HIGH);
    ledcWrite(BUZZER_CHANNEL, 128);
  }
  else if (alarm_on == LOW) {  
    // Turn the light off
    digitalWrite(LIGHT_PIN, LOW);
    ledcWriteTone(BUZZER_CHANNEL, 0);
  }
}

void reconnectMQTTClient() {
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    if (client.connect(CLIENT_NAME.c_str())) {
      Serial.print("connected to Broker: ");
      Serial.println(BROKER.c_str());
      // Topic(s) subscription
      client.subscribe(TOPIC.c_str());
    }
    else {
      Serial.print("Retying in 5 seconds - failed, rc=");
      Serial.println(client.state());
      delay(5000);
    }
  }
}

void createMQTTClient() {
  client.setServer(BROKER.c_str(), 1883);
  client.setCallback(clientCallback);
  reconnectMQTTClient();
}

void setup() {
  // Setup ports
  setup_ports();
  // Serial setup
  Serial.begin(9600);
  while (!Serial)
    ; // Wait for Serial to be ready
  delay(1000);
  connectWiFi();
  createMQTTClient();
}

void loop() {
  reconnectMQTTClient();
  client.loop();
  delay(1000);
}
```

## Simulaciones

**Thing 1 (ESP-PIR)**: [link](https://wokwi.com/projects/378574466884158465)
**Thing 2 (ESP-ALARM)**: [link](https://wokwi.com/projects/378591120304957441)




## Referencias



* https://randomnerdtutorials.com/esp32-date-time-ntp-client-server-arduino/
* https://hackmd.io/@fablabbcn/rydUz5cqv
* https://randomnerdtutorials.com/esp32-mqtt-publish-subscribe-arduino-ide/
* https://www.hackster.io/harshkc2000/toit-and-esp32-mqtt-based-motion-alert-system-7f281a
* https://esp32tutorials.com/esp32-mqtt-publish-ds18b20-node-red-esp-idf/
* https://learn.sparkfun.com/tutorials/introduction-to-mqtt/all
* https://learn.adafruit.com/adafruit-io/mqtt-api
* https://github.com/adafruit/Adafruit_IO_Arduino
* https://wokwi.com/projects/321525495180034642
* https://arduinojson.org/
* https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/api/ledc.html
* https://www.pinguytaz.net/index.php/2021/09/21/musica-con-un-arduinoesp32-y-un-buzzer/
* https://randomnerdtutorials.com/esp32-pwm-arduino-ide/
* https://esp32tutorials.com/esp32-mqtt-publish-ds18b20-node-red-esp-idf/




# Ejemplo 3

Caso metiendo control de luz

## Cosas

### Thing 1 - ESP-PIR (Simulacion)

**Simulación thing1**: [link](https://wokwi.com/projects/378619110441876481)

```h
#pragma once

#include <string>

using namespace std;


// WiFi credentials
const char *SSID = "Wokwi-GUEST";
const char *PASSWORD = "";

// ------------------------- MQTT Network ------------------------- //
const string BROKER = "test.mosquitto.org";

// ----------- thing-001 (self - ESP32-PIR)
// I/O config
// Lamps
const byte LIGHT_PIN = LED_BUILTIN; 
// PIR
const byte PIR_MOTION_SENSOR = 5;

// MQTT settings
const string ID = "thing-001";
const string CLIENT_NAME = ID + "_ESP32-PIR";

// Topics
const string TOPIC1 = ID + "/home/store/sensors/presence/pir";
const string TOPIC2 = ID + "/home/store/actuators/lamps/lamp1";

// ----------- thing-002 (ESP32-ALARM)
// No se necesita poner nada

// ----------- iot-server (control)
// No se ha implementado aun

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

void clientCallback(char* topic, byte* payload, unsigned int length) {
  String response;

  for (int i = 0; i < length; i++) {
    response += (char)payload[i];
  }
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  Serial.println(response);
  
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, response);
  JsonObject obj = doc.as<JsonObject>();

  bool alarm_on = obj["light"];
  if(alarm_on == HIGH)  {
    // Turn the light on
    digitalWrite(LIGHT_PIN, HIGH);
  }
  else if (alarm_on == LOW) {  
    // Turn the light off
    digitalWrite(LIGHT_PIN, LOW);
  }
}

void reconnectMQTTClient() {
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    if (client.connect(CLIENT_NAME.c_str())) {
      Serial.print("connected to Broker: ");
      Serial.println(BROKER.c_str());
      // Topic(s) subscription
      client.subscribe(TOPIC2.c_str());
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
  setup_timer();
}

void loop() {
  reconnectMQTTClient();
  client.loop();
  if (event_timer) {
    event_timer = false; // Reconocimiento de la irq (evento)
    motion_detected = digitalRead(PIR_MOTION_SENSOR);

    Serial.println("Hi, people is coming");
    DynamicJsonDocument doc(1024);
    doc["alarm"] = motion_detected;
    
    string telemetry;
    serializeJson(doc, telemetry);
    Serial.print("Sending telemetry ");
    Serial.println(telemetry.c_str());
    client.publish(TOPIC1.c_str(), telemetry.c_str());
  }
  delay(100);  
}
```

### Thing 2 - ESP-ALARM (Simulacion)

**Simulación**: [link](https://wokwi.com/projects/378623800783269889)

**Archivo**: config.h

```h
#pragma once

#include <string>

using namespace std;


// WiFi credentials
const char *SSID = "Wokwi-GUEST";
const char *PASSWORD = "";

// ------------------------- MQTT Network ------------------------- //
const string BROKER = "test.mosquitto.org";

// ----------- thing-001 (self - ESP32-PIR)

// MQTT settings
const string ID_PIR = "thing-001";

// ----------- thing-002 (self - ESP32-ALARM)

// I/O config
// Lamps
const byte LIGHT_PIN = LED_BUILTIN; 
// Buzzer
const byte BUZZER_PIN = 5;

// MQTT settings
const string ID = "thing-002";
const string CLIENT_NAME = ID + "_ESP32-ALARM";

// Topics
const string TOPIC1 = ID_PIR + "/home/store/sensors/presence/pir";
const string TOPIC2 = ID + "/home/house/actuators/lamps/lamp1";

// ----------- iot-server (control)

// No se ha implementado aun

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
  Serial.print(topic);
  Serial.print("] ");
  Serial.println(response);
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, response);
  JsonObject obj = doc.as<JsonObject>();
  
  if (strcmp(topic,TOPIC1.c_str()) == 0){
    // Alarm topic: "thing-001/home/store/sensors/presence/pir";
    bool alarm_on = obj["alarm"];
    if(alarm_on == HIGH)  {
      ledcWrite(BUZZER_CHANNEL, 128);
    }
    else if (alarm_on == LOW) {  
      ledcWriteTone(BUZZER_CHANNEL, 0);
    }
  }
  else if(strcmp(topic,TOPIC2.c_str()) == 0) {
    // Lamp topic: "thing-002/home/house/actuators/lamps/lamp1"
    digitalWrite(LIGHT_PIN, obj["light"]);
  }
}

void reconnectMQTTClient() {
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    if (client.connect(CLIENT_NAME.c_str())) {
      Serial.print("connected to Broker: ");
      Serial.println(BROKER.c_str());
      // Topic(s) subscription
      client.subscribe(TOPIC1.c_str());
      client.subscribe(TOPIC2.c_str());
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


Test:



Thing 1:
* P: thing-001/home/store/sensors/presence/pir - {"alarm":1} {"alarm":0} 
* S: thing-001/home/store/actuators/lamps/lamp1 - {"light":1} {"light":0}

Thing 2:
* S: thing-001/home/store/sensors/presence/pir - {"alarm":1} {"alarm":0} 
* S: thing-002/home/house/actuators/lamps/lamp1 - {"light":1} {"light":0}

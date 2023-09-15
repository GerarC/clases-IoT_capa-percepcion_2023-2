#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>

const int pinX = 33;    //  P33 (GPIO33 - ADC5)
const int pinY = 32;    //  P32 (GPIO32 - ADC4)
const int pinSW = 15;  //  P15 (GPIO15)
int valueX = 0;        //  Analog
int valueY = 0;        //  Analog
int valueZ = 0;        //  Digital

String thing_nameX = "node0022";
String thing_nameY = "node0023";
String thing_nameZ = "node0024";


// WiFi parameters
const char* ssid = "ssid";
const char* password = "password";

const char* host = "dweet.io";

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  Serial.print("Connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  Serial.println();

  valueX = analogRead(pinX); 
  Serial.print("X:");
  Serial.print(valueX, DEC); 
  valueY = analogRead(pinY); 
  Serial.print(" | Y:"); 
  Serial.print(valueY, DEC); 
  valueZ = digitalRead(pinSW);
  Serial.print(" | Z: "); 
  Serial.println(valueZ, DEC); 
  delay(100);

  Serial.println();

  // We now create a URI for the request
  String urlX = "/dweet/for/" + thing_nameX + "?value=" + String(valueX);
  String urlY = "/dweet/for/" + thing_nameY + "?value=" + String(valueY);
  String urlZ = "/dweet/for/" + thing_nameZ + "?value=" + String(valueZ);

    // Send request
  Serial.print("Requesting URL X: ");
  Serial.println(urlX);
  Serial.println();
  client.print(String("GET ") + urlX + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  Serial.print("Requesting URL Y: ");
  Serial.println(urlY);
  Serial.println();
  client.print(String("GET ") + urlY + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  Serial.print("Requesting URL Z: ");
  Serial.println(urlZ);
  Serial.println();
  client.print(String("GET ") + urlZ + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");

  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 1000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  // Read all the lines from the answer
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  // Close connecting
  Serial.println();
  Serial.println("closing connection");
}

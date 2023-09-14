# Ejemplo

Explorar la plataforma https://dweet.io/ enviando a esta un valor analogico.

## Hardware

![sensor_analgo](sensor_analogo_bb.png)

## Ejemplo 1

### Software

Solo envia los valores sensador al PC mediante el puerto serial.

```ino
const int analogInPin = 15;  //  GPIO15
int sensorValue = 0;         // Value read from the pot

void setup() {
  // Start Serial  
  Serial.begin(115200);    
}

void loop() {
  // Read the analog in value
  sensorValue  = analogRead(analogInPin);
  
  // Display data  
  Serial.print("Sensor:  ");
  Serial.println(sensorValue);
   
  // Wait a few seconds between measurements.
  delay(2000);
}
```

## Ejemplo 2

### Software

Solo envia los valores sensados a [https://dweet.io/](https://dweet.io/) el puerto serial.


```
#include <WiFi.h>
#include <WiFiClient.h>

// WiFi parameters
const char* ssid = "ssid";
const char* password = "password";

const int analogInPin = 15; // GPIO15
int sensorValue = 0;        // Value read from the pot

String thing_name = "node001";

// Host
const char* host = "dweet.io";

void setup() {
  // Start Serial
  Serial.begin(115200);
  delay(10);  

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
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

  // Read the analog in value
  sensorValue  = analogRead(analogInPin);


  // We now create a URI for the request
  String url = "/dweet/for/" + thing_name + "?value=" + String(sensorValue);

  // Send request
  Serial.print("Requesting URL: ");
  Serial.println(url);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
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
```

Note del codigo que el nombre de la cosa en este caso es: ```node001```

### Test

Vaya a [https://dweet.io/](https://dweet.io/) y explore el API:

![api_dweet](API_dweet.png)

Luego registre el dispositivo 
https://dweet.io/follow

https://dweet.io/dweet/for/my-thing-name?hello=world

https://dweet.io/dweet/for/my-thing-name?hello=world

String url = "/dweet/for/" + thing_name + "?value=" + String(sensorValue);

Registre la cosa:

![dweet1](dweet1.png)

Verifique que la cosa esta registrada en https://dweet.io/follow colocando el nombre de la cosa (```node001``` en este caso):

![dweet2](dweet2.png)

Para ver los datos que envia la cosa vaya en el navegador a https://dweet.io/follow/thing_name, donde ```thing_name``` es el nombre de la cosa (```node001``` en este caso):

![dweet3](dweet3.png)

Usando el API, coloque manualmente un valor cualquiera usando el par ```{KEY: VALUE}```, en este caso ```KEY``` es ```"value"``` y ````VALUE``` es ```0```. De este modo los parametros seran ```{"value": 0}``` tal y como se muestra a continuación:

![dweet4](dweet4.png)

Luego observe nuevamente la direccion de la cosa, en nuestro caso: https://dweet.io/follow/node001. 

Proceda a descargar en la ESP32 el código; este despues de ponerse a funcionar arroja la siguiente salida en el monitor serial:

![serial_esp32](serial_esp32.png)

Notese que el ESP32 esta haciendo peticiones para colocar los datos en **dweet.io**, esto se puede corroborar cargango la pagina de la cosa https://dweet.io/follow/node001. La siguiente figura muestra la grafica en el tiempo de los valores enviados:

![dweet5](dweet5.png)

## Enlaces

* https://wokwi.com/projects/348987008435094100
* https://www.esp32.com/viewtopic.php?t=20934
* https://www.home-assistant.io/integrations/dweet/
* https://yungger.medium.com/so-easy-micropython-dweet-io-iot-cloud-platform-42ade3b12187
* https://www.hackster.io/javier-munoz-saez/esp8266-sending-data-to-an-online-deskboard-3e7e91
* https://github.com/phyunsj/dweet.io-node-red
* http://developers.sensetecnic.com/article/post-data-to-dweetio-using-fred/
* https://docs.iotify.io/temp/untitled-4
* https://www.learnrobotics.org/blog/create-a-database-for-iot-using-dweet-io-tutorial/
* https://www.learnrobotics.org/blog/nodemcu-dweet-io-freeboard-io-tutorial-for-iot/


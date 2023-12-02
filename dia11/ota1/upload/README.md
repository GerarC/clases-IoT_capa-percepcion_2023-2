# Subida del programa

A continuación se muestra la subida del programa mediante OTA.

Inicialmente, se verifica la conexion de la red. En nuestro caso tenemos las siguiente IPs:

|Equipo|IP|
|--|--|
|PC|```192.168.1.4```|
|ESP32|```192.168.1.12```|

Esto se verifica mediante la aplicación de los siguientes comandos:

1. IP maquina:

   ![1](PC_ip.png)

2. IP ESP32:

   ![2](ESP32_ip.png)

3. Test de conectividad

   ![3](ping_PC-to-ESP.png)

Luego, lo que hacemos es verificar que el servidor **AsyncElegantOTA** este en funcionamiento usando la URL ```ÈSP32_IP/upload```  en el browser, en nuestro caso tenemos: ```192.168.1.12/upload```

![4](2-upload.png)

Ahora, vamos a proceder a codificar el programa de prueba en el IDE de Arduino como siempre se hace. 

1. Codificar el programa. En nuestro caso creamos el ejemplo del parpadeo cuyo codigo se muestra a continuación:
    
    ```ino
    // the setup function runs once when you press reset or power the board
    void setup() {
      // initialize digital pin LED_BUILTIN as an output.
      pinMode(LED_BUILTIN, OUTPUT);
    }
    
    // the loop function runs over and over again forever
    void loop() {
      digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
      delay(1000);                      // wait for a second
      digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
      delay(1000);                      // wait for a second
    }
    ```

   Para el caso el programa se guardo como **test-blink**: 

   ![5](test-blink.png)

2. Crear el binario:

   ![6](1-upload.png)

   Si todo esta bien dentro del directorio asociado al proyecto **test-blink** se crea un directorio **build**.

   ![7](build_bin1.png)

   Dentro del directorio **build** se crea otro directorio **esp32.esp32.nodemcu-32s** y dentro de este se encuentran las imagenes asociadas al programa:

   ![8](build_bin2.png)

Si todo esta bien lo que resta es subir la imagen a traves del servidor que se esta ejecutando en la ESP32. Tal y como se resalta en las siguientes capturas:

1. Upload 1:
   
   ![9](2-upload.png)

2. Upload 2:

   ![10](3-upload.png)

3. Upload 3:

   ![11](4-upload.png)

4. Upload 4:

   ![12](5-upload.png)

Si todo esta bien, una vez hecho anterior, el ESP32 debera estar ejecutando el programa en cuestion, en el caso el que permite el parpadeo del led. 

Finalmente, retornando a la pagina de upload del servidor tenemos:

![13](6-upload.png)

Si todo esta bien, se deberia actualizar la ESP32 desde con cualquier otra aplicación.


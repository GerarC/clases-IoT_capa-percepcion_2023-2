# Capa de percepción - clase 3

> ## Objetivos
> * Aprender a usar la tarjeta de desarrollo ESP32.
> * Comprender la API básica de entrada y salida del lenguaje Arduino.

## Referencias principales

* La mayor parte de esta clase tomará como base la lección 2 A deeper dive into IoT (lección 2) del curso IoT for Beginners ([link](https://github.com/microsoft/IoT-For-Beginners)).
* También mucha de la información se tomó de la pagina: https://randomnerdtutorials.com/ 
* ESP32 Arduino Core’s documentation (link)


## Componentes de una aplicacion IoT

Una **Cosa** (**Thing**) se refiere a un dispositivo que interactua con el mundo fisico a traves de sensores y actuadores. Para aprender a realizar aplicaciones para IoT el primer paso es disponer de un kit de desarrollo IoT.

Un kit de desarrollo IoT consiste de varios dos positivos IoT de uso general (con caracteristicas que no poseen los dispositivos de producción, tales como pines externos para conectar a sensores y actuadores y hardware adicional para soporte de debugging entre otras cosas) empleados por los desarrolladores para realizar prototipado. Existen dos tipos de kits de desarrollo:
* **Computadora monoplaca (single-board Computer)**

![r-pi](raspberry-pi-4.jpg)

* **Microcontroladores (microcontrollers)**

![arduino-uno](arduino-uno.jpg)

A lo largo de esta parte del curso, solo nos centraremos los **microcontroladores** ya que, las computadores monoplaca se estudiaran con mas detalle en la parte de **capa de red**.

### Microcontroladores

Un microcontrolador (tambien conocido como MCU), es un pequeño computador que consiste de:
* **Una o mas unidades centrales de procesamiento (CPUs)**: Este, es el cerebro del microcontrolador encargado de la ejecución del programa.
* **Memoria (RAM + memoria de programa)**: Lugar donde es almacenado el programa, los datos y las variables.
* **Conexiones de entrada/salida programables**: Para permitir la comunicación con perifericos externos (dispositivos conectados) tales como sensores y actuadores.

Debido a los recursos limitados que poseen los microcontroladores, estos solo pueden ejecutar un numero limitado de  limitado de tareas.

En cuanto a los kits de desarrollo basados en microcontroladores, existen algunos que suelen venis con sensores, actuadores (Por ejemplo el **SparkFun Inventor's Kit Experiment** ([link](https://learn.sparkfun.com/tutorials/sparkfun-inventors-kit-experiment-guide---v41?_ga=2.150401727.841450445.1693442272-1122723610.1691641161&_gl=1*8wq17e*_ga*MTEyMjcyMzYxMC4xNjkxNjQxMTYx*_ga_T369JS7J9N*MTY5MzQ0MjI3MS4xNS4wLjE2OTM0NDIyNzEuNjAuMC4w))) y otros componentes adicionales.

Sin embargo tambien existen algunos microcontroladores con conectividad inalambrica, como Bluetooth o WiFi, ya sea incorporada o mediante la conexión con otro microcontrolador adicional en la placa el cual implenta dicha conectividad.  

![esp32](ESP32_Espressif_ESP-WROOM.jpg)

## Arduino Framework

Cuando hablamos de arduino no solo nos referimos a un microcontrolador especifico, en realidad estamos hablando del **framework para microcontroladores** mas popular en la actualidad.

**Arduino**  es una plataforma opensource de electronica que combina software y hardware. Al ser esta plataforma open hardware, es posible usar el modelo de programación de Arduino para escribir codigo para cualquier otra plataforma compatible con Arduino (placas genericas o de otroa fabricantes).

El modelo de programación de arduino esta basado en el **API de arduino** el cual espone un conjunto de funciónes y estructuras (constantes, variables, tipos de datos, objetos, etc) que permiten la interacción del microcontrolador con hardware externo (sensores y actuadores). La información del API se encuentra en la pagina **Language Reference** ([link](https://www.arduino.cc/reference/en/)).

![arduino-ref](arduino-reference.png)

### Pasos para programar un dispositivo usando el Framework de Arduino

> **Arduino Cheat Sheet**: Existen referencias breves que muestran de manera resumida el API de arduino. La referecia **Arduino Cheat Sheet** ([link](Arduino_Cheat_Sheet.pdf)) es uno de estos casos ([URL principal](https://github.com/liffiton/Arduino-Cheat-Sheet))

Para usar el API de arduino es necesario tener en cuenta los siguientes pasos:
1. Si la placa es generica, verificar esta es Arduino compatible ([link wikipedia](https://en.wikipedia.org/wiki/List_of_Arduino_boards_and_compatible_systems))
2. Identificar claramente, las caracteristicas, los pines y la funcionalidad de la placa a usar. Para esto es necesario revisar el manual de usuario de la placa, A continuación se muestran algunos ejemplos: 
   * Arduino UNO ([link](https://docs.arduino.cc/hardware/uno-rev3)) 
   * NodeMCU-32s ([link](https://docs.ai-thinker.com/_media/nodemcu32-s_specification_v1.3.pdf))
3. Proceder a programar el codigo del firmware siguiendo el modelo de programación de Arduino.

### Funciones basicas del API de Arduino

Las funciones basicas del API de Arduino se encuentran online en **Language Reference** ([link](https://www.arduino.cc/reference/en/))

**Entrada y Salida digital** 

Las funciones de entrada y salida permiten básicamente dos cosas: 
1. Configurar los puertos (**pines**) como entradas o salidas digitales.
2. Leer o escribir dichos puertos de acuerdo a la forma como fueron configurados.

|Función|Información de la función|
|--|--|
|```digitalWrite()```|**Descripción** ([link](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/)): <br> Escribe un valor HIGH o LOW  en un puerto determinado.<br><br>**Sintaxis**: <br> ```digitalWrite(pin, value)```<br><br>**Parámetros**: <li> **pin**: Número del puerto del Arduino. <li> **value**: Valor que se escribe en el puerto (```HIGH``` o ```LOW```).
|```digitalRead()```|**Descripción** ([link](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/)):<br>Lee el valor de un puerto determinado.<br><br>**Sintaxis**: <br>```digitalRead(pin)```<br><br>**Parámetros**: <li>**pin**: Pin del Arduino a ser leído. <li>**Valores retornados**: El valor del puerto al ser leído (```HIGH``` o ```LOW```).
|```pinMode()```|**Descripción** ([link](https://www.arduino.cc/reference/en/language/functions/digital-io/pinmode/)):<br>Permite configurar un puerto como entrada o salida. <br><br>**Sintaxis**: <br>```pinMode(pin, mode)```<br><br>**Parámetros**: <li>**pin**: Pin del Arduino a ser configurado<li>**mode**: Modo: ```INPUT```, ```OUTPUT``` o ```INPUT_PULLUP```.|

**Funciones de entrada y salida análoga**

Permiten interactuar (leer o escribir) con puertos que funcionan como entradas o salidas análogas. La siguiente tabla muestra resume algunas de estas:

|Función|Información de la función|
|---|---|
|```analogRead()```|**Descripción** ([link](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/)):<br>Lee el valor de un puerto análogo determinado devolviendo un valor entero asociado al voltaje que tiene este puerto.<br><br>**Sintaxis**:<br>```analogRead(pin)```<br><br>**Parámetros**:<br><li>**pin**: Número del puerto análogo (```A0``` – ```A5``` para la mayoría de las placas) del Arduino<br><br>**Valores retornados**:<br>Valor análogo  leído en el pin. El rango dependerá de la resolución del conversor análogo digital asociado a el pin (0 – 1024 cuando la resolución es de 10 bits o 0 – 4096 cuando la resolución es de 12 bits).|
|```analogWrite()```|**Descripción** ([link](https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/)):<br>Escribe un valor análogo (modificando el valor del ciclo de dureza de una onda PWM) a un puerto.<br><br>**Sintaxis**:<br>```analogWrite(pin, value)```<br><br>**Parámetros**: <li>**pin**: Pin del Arduino (denotado en la placa con el símbolo ~) en el que se escribe.<li>**value**: Ciclo de dureza entre cero (siempre apagado) y 255 (siempre on).|

**Bases de tiempo**

Son funciones empleadas para la crear retardos y generar marcas de tiempos en los programas, existen varias funciones para este fin como ```delay()```, ```delayMicroseconds()```, ```micros()``` y ```millis()```. La siguiente tabla describe la función ```delay()``` que fue la empleada en los ejemplos anteriores:

|Función|Información de la función|
|---|---|
|```delay()```|**Descripción** ([link](https://www.arduino.cc/reference/en/language/functions/time/delay/)): <br>Detiene el programa por una cantidad de tiempo (en milisegundos) especificada como parámetro.<br><br>**Sintaxis**:<br>```delay(ms)```<br><br>**Parámetros**:<li>**ms**: Número de milisegundos a detener el programa.|

**Funciones de interacción con el puerto serial**

Son funciones empleadas para la configuración e interacción con el puerto serial ([link](https://www.arduino.cc/reference/en/language/functions/communication/serial/)). La siguiente figura muestra algunas funciones de uso común

|Función|Descripción|
|---|---|
|```Serial.begin()```|Configura la velocidad de transmisión serial (bits por segundo = baud).<br><br>**Sintaxis**:<br>```Serial.begin(speed)``` <br><br>**Parámetros**: <ul><li>**```speed```**: Velocidad de transmisión</ul>|
|```Serial.print()```|Imprime los datos del puerto serial en formato ASCII.<br><br>**Sintaxis**:<br>```Serial.print(val)```<br>```Serial.print(val, format)```<br><br>**Parámetros**: <ul><li>**```val```**: Valor a imprimir. El valor puede ser de cualquier tipo.<li>**```format```**: Formato de representación del ASCII (```DEC```, ```HEX```, ```OCT``` o ```BIN```).</ul>|
|```Serial.available()```|Obtiene el número de bytes (caracteres) disponibles por leer en el puerto serial. Estos son datos que ya han llegado y han sido almacenados en el buffer de recepción serial (el cual almacena 64 bytes).<br><br>**Sintaxis**:<br>```Serial.available()```<br><br>**Valores retornados**: Número de bytes disponibles para leer.|
|```Serial.read()```|Lee un dato que entra a través del serial.<br><br>**Sintaxis**:<br>```Serial.read()```<br><br>**Valores retornados**: Primer byte de los datos seriales disponibles (o ```-1``` si no hay datos disponibles). El tipo de dato leído es ```int```.|


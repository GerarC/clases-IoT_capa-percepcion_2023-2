# Capa de percepción - clase 1

> ## Objetivos
> * Repasar los componentes básicos de un sistema IoT.
> * Explorar los componentes básicos que conforman el concepto de cosa.
> * Hablar sobre el software de desarrollo a emplear
> * Investigar sobre los sistemas de desarrollo disponibles en el laboratorio.

## Referencias principales

La mayor parte de esta clase tomará como base la lección 2 **A deeper dive into IoT** ([lección 2](https://github.com/microsoft/IoT-For-Beginners)) del curso **IoT for Beginners** ([link](https://github.com/microsoft/IoT-For-Beginners)) de Microsoft.

# Orden de la clase

### 1. Ejemplo introductorio

A continuación se muestra el diagrama de un sistema de control en tiempo real para jugar con un laberinto hecho en la universidad de Curtin (https://www.curtin.edu.au/):

![iotx](proyecto-IOT1x.png)

En el siguiente video se puede observar el funcionamiento de dicho sistema:

[![IOT3x - IoT Networks and Protocols](https://img.youtube.com/vi/ErS2W58StIs/0.jpg)](https://www.youtube.com/watch?v=ErS2W58StIs)

### 2. Componentes de las aplicaciones IoT

![componentes-iot](componentes_iot-apps.png)

Esta parte tomara como referencia el material del siguiente [link](https://github.com/microsoft/IoT-For-Beginners/blob/main/slides/lesson-2.pdf)


### 3. Placas de desarrollo disponibles

**Arduino UNO**

![arduino-uno](uno-r3.jpg)

Las principales caracteristicas del Arduino se resumen en la siguiente tabla:

|Item |Arduino UNO|
|---|---|
|Microcontrolador |ATmega328P (Atmel)|
|Microprocesador |ATMega 16U2|
|I/O Voltage |5 V|
|Input voltage (nominal) |7 - 12 V (Power jack)|
|Power jack | yes|
|Voltaje de alimentación (Pin)||
|Voltaje de Entradas/Salidas |5 V|
|Voltaje de referencia en el ADC| 5V|
|DC Current per I/O Pin| 20 mA|
|Built-in LED Pin |13|
|Digital I/O Pins |14 (I/O)|
|Analog input pins |6 (ADC 10-bit)|
|PWM pins| 6|
|UART| yes|
|I2C| yes|
|SPI| yes|
|I2S|| 
|WIFI| no|
|Bluetooth| no|
|Programmable | Arduino IDE, Micropython, VS Code|
|Marca | Arduino|

Para mas informacion ver el siguiente [link](https://udea-iot.gitbook.io/introduccion-al-iot/primeros-pasos/placas-de-desarrollo/arduino-uno)

**ESP8266**

![esp-8266](NodeMcuV3_1.jpg)

|Item |ESP8266|
|---|---|
|Microcontrolador |SoC ESP9266EX|
|Microprocesador |Tensilica's L106 Diamond series 32-bit|
|I/O Voltage |5 V|
|Input voltage (nominal) |5 - 12 V (VIN, VCC)|
|Power jack | no|
|Voltaje de alimentación (Pin)|5 V (VIN)|
|Voltaje de Entradas/Salidas |3.3 V|
|Voltaje de referencia en el ADC|3.3 V|
|DC Current per I/O Pin| 12 mA|
|Built-in LED Pin |---|
|Digital I/O Pins |9 (GPIO)|
|Analog input pins |1|
|PWM pins| 4|
|UART| yes|
|I2C| yes|
|SPI| yes|
|I2S| yes| 
|WIFI| IEEE 802.11 b/g/n|
|Bluetooth| no|
|Programmable | Arduino IDE, Micropython, VS Code|
|Marca | Ai-Thinker|

Para mas informacion ver el siguiente [link](https://udea-iot.gitbook.io/introduccion-al-iot/primeros-pasos/placas-de-desarrollo/esp8266)

**ESP32**

![esp32](esp32.png)

|Item |ESP32|
|---|---|
|Microcontrolador |SoC ESP32|
|Microprocesador |Xtensa single-/dual-core 32-bit LX6|
|I/O Voltage |5 V|
|Input voltage (nominal) |---|
|Power jack | no|
|Voltaje de alimentación (Pin)|3.3 V (VIN)|
|Voltaje de Entradas/Salidas |3.3 V|
|Voltaje de referencia en el ADC| |
|DC Current per I/O Pin| 12 mA|
|Built-in LED Pin ||
|Digital I/O Pins |24 (GPIO - Algunos pines solo como entrada)|
|Analog input pins |2 (8-bit)|
|PWM pins| 4|
|UART| yes|
|I2C| yes|
|SPI| yes|
|I2S| | 
|WIFI| IEEE 802.11 b/g/n|
|Bluetooth| yes|
|Programmable | Arduino IDE, Micropython, VS Code|
|Marca | Ai-Thinker|

Para mas informacion ver el siguiente [link](https://udea-iot.gitbook.io/introduccion-al-iot/primeros-pasos/placas-de-desarrollo/esp32)


### 4. Sobre los componentes

**Fabricantes**

En la siguiente tabla se muestran algunas de las principales empresas que se dedican a la fabricación de modulos para prototipado IoT:

|Fabricante|Link|
|---|---|
|Adafruit Industries|https://www.adafruit.com/|
|SparkFun Electronics|https://www.sparkfun.com/|
|dfrobot|https://www.dfrobot.com/|
|Seeeed Studio|https://www.seeedstudio.com/|
|Elegoo|https://www.elegoo.com/|

Ademas de la fabricación, tambien documentan y muestran ejemplos demostrativos de como usar los componentes que allí se fabrican.

**Distribuidores**

Si lo que se quiere es comprar son componentes electronicos existen distribuidores para ello, en la siguiente tabla se muestran algunos de los principales distribuidores de componentes a nivel mundial (tomados de la pagina **2023 Top 50 Electronics Distributors List** ([link](https://www.supplychainconnect.com/rankings-research/article/21264998/2023-top-50-electronics-distributors-list))):

|Distribuidores|Link|
|---|---|
|Mouser Electronics|https://www.mouser.com/|
|DigiKey Corporation|https://www.digikey.com/|
|Arrow Electronics|https://www.arrow.com/|
|WPG Holdings|https://www.wpgholdings.com/main/index/en|
|Avnet|https://www.avnet.com/wps/portal/us/|
|Future Electronics|https://www.futureelectronics.com/|

En el caso colombiano, la siguiente lista (tomada del foro **Listado de proveedores de Electrónica - Colombia** ([link](https://www.forosdeelectronica.com/resources/listado-de-proveedores-de-electr%C3%B3nica-colombia.105/))) contiene algunos de los distribuidores en Colombia:

|Distribuidores|Link|
|---|---|
|I + D|https://didacticaselectronicas.com/|
|Sigma Electronica|https://www.sigmaelectronica.net/|
|Electronilab|https://electronilab.co/|
|Suconel|https://suconel.com/|
|La Red Electronica|https://laredelectronica.com/|

### 5. Actividad para la proxima clase

1. Instalar en su maquina los siguientes programas:
   - [x] Arduino IDE
   - [x] Visual Studio Code
   - [x] Platformio (Complemento de Visual Studio Code)
   - [x] Fritzing
   - [x] draw.io
   - [ ] Mosquito
   - [ ] Mqtt explorer 
   - [ ] Node-red 
   
   Para mas información sobre estas puede consultar el siguiente [link](https://udea-iot.gitbook.io/introduccion-al-iot/pasos-previos/herramientas-necesarias/software)

2. A continuación se listan los directorios de cada uno de los proyectos a trabajar a lo largo del semestre. Teniendo en cuenta las instrucciones dadas en clase editar el archivo **README.md** disponible dentro de cada directorio (para ver la sintaxis markdown puede consultar el siguiente [link](https://github.com/adam-p/markdown-here/wiki/Markdown-Here-Cheatsheet)). A continuación se listan los proyectos:
   
   |#|Proyecto|
   |---|---|
   |1| HAMMER 2.0 ([link](hammer-2/README.md))|
   |2| Smart Scent ([link](smart-scent/README.md))|
   |3| Luft Scntry ([link](luft-sentry/README.md))|
   |4| Sistemas de automatizado de una cava de vino ([link](cava-vino/README.md))|

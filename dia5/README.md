# Librerias

## Uso de librerias

Cuando se adquiere una una impresora, el primer paso para que esta pueda usarse, consiste en obtener e instalar los drivers para que esta pueda funcionar correctamente en el sistema operativo. Normalmente, los fabricantes proporcionan los drivers de los dispositivos y por lo tanto, el procedimiento de poner en marcha el hardware consiste simplemente en ejecutar un simple instalador y listo; sin embargo, a veces se puede dar el caso en que el driver no existe y a menos que uno mismo lo cree, esta condenado a no poder usar dicho hardware y, generalmente, si esto ultimo pasa el resultado es que se quede con los crespos hechos a no ser que sea como **Richard Stallman** (Saint IGNUcius) (Ver: **Cómo sería el mundo y la tecnología hoy en día sin el software libre y sin las ideas de Richard Stallman**([link](https://www.xataka.com/especiales/como-seria-mundo-tecnologia-hoy-dia-software-libre-ideas-richard-stallman)))

![saint_ingnucius](saintignucius.jpg)

En el caso de los sistemas elecrónicos basados en microcontroladores sucede algo similar, cuando se desea que una aplicación use un hardware externo (sensor, actuador o memoria, por citar algunos casos), es necesario disponer de los drivers necesarios para permitir la interacción entre el firmware (programa descargado en el microcontrolador) y el hardware externo con el que este interactua. 

Existen casos en los que el hardware externo no posee soporte, de modo que, se hace necesario para el programador el diseño y la programación de los programas (drivers) necesarios para su interacción y control; sin embargo, esta es una tarea dificil por que exige conocimiento de hardware, protocolos y detalles de bajo nivel relacionados con el diseño del hardware. Afortunadamente, una de las caracteristicas del proyecto Arduino radica en su filosofica **Open Hardware y Software** lo cual hace que gran candidad de hardware sea soportada para la plataforma Arduino.

Gracias a este soporte, es posible encontrar gran cantidad de bibliotecas prediseñadas que ocultan todos los detalles de bajo nivel para controlar el hardware, lo cual permite que el programador se centre en la logica del sistema en vez de en los detalles de bajo nivel.

## Agregando librerias

Exiten tutoriales en internet que explican muy bien como importar librerias portadas al API de Arduino, a continuación se listan estos enlaces:
1. **Installing an Arduino Library** de Sparkfun ([link](https://learn.sparkfun.com/tutorials/installing-an-arduino-library/all))
2. **All About Arduino Libraries** de Adafruit ([link](https://learn.adafruit.com/adafruit-all-about-arduino-libraries-install-use/arduino-libraries))
3. 
4. **Arduino Tips, Tricks, and Techniques** de Adafruit ([link](https://learn.adafruit.com/arduino-tips-tricks-and-techniques))
5. **Installing Libraries - Arduino IDE 1** de Arduino ([link](https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries))
6. **Installing Libraries - Arduino IDE 2** de Arduino ([link](https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-installing-a-library))
7. **Getting Started with VS Code and PlatformIO IDE for ESP32 and ESP8266 (Windows, Mac OS X, Linux Ubuntu)** de randomnerdtutorials ([link](https://randomnerdtutorials.com/vs-code-platformio-ide-esp32-esp8266-arduino/))
8. **Library Management** de Platformio ([link](https://docs.platformio.org/en/latest/librarymanager/index.html))


## Referencias

* https://learn.sparkfun.com/tutorials/installing-an-arduino-library/all
* https://learn.adafruit.com/adafruit-all-about-arduino-libraries-install-use/arduino-libraries
* https://learn.adafruit.com/arduino-tips-tricks-and-techniques/arduino-libraries
* https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries
* https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-installing-a-library
* https://github.com/UdeA-IoT/actividad-4
* https://www.arduino.cc/reference/en/libraries/
* https://esp32io.com/tutorials/esp32-keypad
* https://deepbluembedded.com/esp32-keypad-lcd-example-arduino/
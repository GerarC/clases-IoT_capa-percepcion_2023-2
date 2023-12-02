# Ejemplo 1 - OTA

There are different ways to perform OTA updates. In this tutorial, we’ll cover how to do that using the AsyncElegantOTA library. In our opinion, this is one of the best and easiest ways to perform OTA updates.

The AsyncElegantOTA library creates a web server that you can access on your local network to upload new firmware or files to the filesystem (SPIFFS). The files you upload should be in .bin format. We’ll show you later in the tutorial how to convert your files to .bin format.

Este ejemplo fue tomado y documentado de la pagina **ESP32 OTA (Over-the-Air) Updates – AsyncElegantOTA using Arduino IDE** [[link]](https://randomnerdtutorials.com/esp32-ota-over-the-air-arduino/) de Random Nerd Tutorials. En esta pagina se describe el procedimiento de realizar actualizaciones usando la libreria **AsyncElegantOTA**. 

La libreria **AsyncElegantOTA** [[repo]](https://github.com/ayushsharma82/AsyncElegantOTA) crea un servidor en la red local que permite actualizar firmware o archivos del filesystem (SPIFFS). Los archivos deben ser convertidos en formato bin. La siguiente imagen (tomada de Random Nerd Tutorials) resume el procedimiento:

![ota_rnt](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2021/01/Async-Elegant-OTA-Web-Server-ESP32-How-it-Works.png)

## Pasos previos

Al seguir la guia solo se tuvo problemas en la instalación de la libreria ESPAsyncWebServer la cual se instalo manualmente a partir del repositorio. En el siguiente [link](install/README.md) se describe el proceso de instalación.

## Prueba 

Lo siguiente que se hizo fue probar la instalación. Para ello se cargo el ejemplo de prueba el procedimiento se muestra en el link a continuación [link](test/README.md)

## Subiendo el archivo

El procedimiento se muestra a continuación [link](upload/README.md) 

## Ejercicio







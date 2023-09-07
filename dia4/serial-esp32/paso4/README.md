# Paso 4 - Creación del API para controlar el arduino

## Prerequisitos

Antes de iniciar debera tener instaladas las libreias FastAPI y Uvicorn. Para mas información puede ir al siguiente [link](https://fastapi.tiangolo.com/tutorial/):

```bash
python -m pip install fastapi uvicorn[standard]
```

Tambien, es necesario que se lleve a cabo la instalación de pydantyc

```bash
pip install pydantic
```

En RealPython hay un excelente tutorial conocido que muestra como construir Web APIs usando FastAPI (**Using FastAPI to Build Python Web APIs** - [link](https://realpython.com/fastapi-python-web-apis/))

## Software


### API Endpoints

|HTTP method | API endpoint |Descrición|
|---|---|---|
|```GET``` | ```/ports``` |	Obtiene una lista de puertos |
|```GET``` | ```/connect/<port_id>``` |	Conecta la aplicación al puerto serial elegido |
|```GET``` | ```/disconnect``` | Desconecta la aplicación del puerto serial |
|```GET``` | ```/on``` | Enciende el led (Una vez la aplicación se ha conectado) |
|```GET``` | ```/off``` | Apaga el led (Una vez la aplicación se ha desconectado) |

**Nota**: Hay un bug pues la aplicación no prende ni apaga el led.

```python
#Python
from typing import Optional
from enum import Enum
import serial
import serial.tools.list_ports

#Pydantic
from pydantic import BaseModel
from pydantic import Field

#FastAPI
from fastapi import FastAPI
from fastapi import Body, Query, Path

app = FastAPI()
app.serial = None

@app.get("/")
async def home():
    return {"App": "Ready"}

@app.get("/ports"):
async def listPorts():
   comlist = serial.tools.list_ports.comports()
   ports = []
   for element in comlist:
      ports.append(element.device)
   return {"ports": ports}

@app.get("/connect/{port_id}")
async def connect(port_id): 
    print("Iniciando conexión...")
    app.serial = serial.Serial(port_id,115200)
    if app.serial == None:
        return {"Connection": "Fail"}
    else:
        return {"Connection": "Open"}

@app.get("/disconnect")
async def disconnect():
    app.serial.close()
    return {"Connection": "Close"}

@app.get("/on")
async def led_on():
    app.serial.write('H'.encode())
    return {"led":"on"}

@app.get("/off")
async def led_off():
    app.serial.write('L'.encode())
    return {"led":"off"}
```

## Probando la aplicación

Asumiento que la aplicación se guardo como **api_serialLed_esp32.py**, para ejecutar la aplicación se emplea el comando:

```bash
uvicorn api_serialLed_esp32:app --reload
```

Si todo esta bien, deberia salir algo en consola similar a:

![api_consola](run_apiApp.png)

Por otro lado, si se ejecuta en el navegador la URL **127.0.0.1:8000** la salida sera:

![api_browser](app_ready.png)

Para el resto de las pruebas basta con poner en la URL del navegados cualquiera de los endpoints mensionados en la tabla al principio, o para mayor comodidad pasarlo a traves de la interfaz web facilitada por FastAPI para llevar a cabo las pruebas. Para acceder a esta se coloca en el campo de la URL del navegador **127.0.0.1:8000/docs** lo cual deberia arrojar una salida como la que se muestra a continuación:

![api_browser_docs](run_apiApp_docs.png)

## Importante

**Este programa aun tiene bugs**

## Referencias

1. https://fastapi.tiangolo.com/
2. https://fastapi.tiangolo.com/tutorial/
3. https://fastapi.tiangolo.com/es/tutorial/
4. https://realpython.com/api-integration-in-python/
5. https://realpython.com/flask-connexion-rest-api/
6. https://realpython.com/flask-connexion-rest-api-part-2/
7. https://realpython.com/flask-connexion-rest-api-part-3/
8. https://realpython.com/courses/python-rest-apis-with-fastapi/
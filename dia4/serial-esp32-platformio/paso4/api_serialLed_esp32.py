#Python
import serial
import serial.tools.list_ports

#Pydantic
from pydantic import Field

#FastAPI
from fastapi import FastAPI

app = FastAPI()
app.serial = None

@app.get("/")
async def home():
    return {"App": "Ready"}

@app.get("/ports")
async def listPorts():
   comlist = serial.tools.list_ports.comports()
   ports = []
   for element in comlist:
      ports.append(element.device)
   return {"ports": ports}

@app.get("/connect/{port_id}")
async def connect(port_id): 
    print("Iniciando conexión...")
    app.serial = serial.Serial(port_id,9600)
    if app.serial == None:
        return {"Connection": "Fail"}
    else:
        return {"Connection": "Open", }

@app.get("/disconnect")
async def disconnect():
    app.serial.close()
    return {"Connection": "Close"}

@app.get("/on")
async def led_on():
    app.serial.write(b'h')
    return {"led":"on"}

@app.get("/off")
async def led_off():
    app.serial.write(b'l')
    return {"led":"off"}
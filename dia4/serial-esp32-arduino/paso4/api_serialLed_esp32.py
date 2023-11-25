"""
Para correr:

uvicorn api_serialLed_esp32:app --reload

"""

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
def home():
    return {"App": "Ready"}

@app.get("/ports")
def listPorts():
   comlist = serial.tools.list_ports.comports()
   ports = []
   for element in comlist:
      ports.append(element.device)
   return {"ports": ports}

@app.get("/connect/{port_id}")
def connect(port_id): 
    print("Iniciando conexión...")
    app.serial = serial.Serial(port_id,9600)
    if app.serial == None:
        return {"Connection": "Fail"}
    else:
        return {"Connection": "Open"}

@app.get("/disconnect")
def disconnect():
    app.serial.close()
    return {"Connection": "Close"}

@app.get("/on")
def led_on():
    app.serial.write("H".encode())
    return {"led":"on"}

@app.get("/off")
def led_off():
    #app.serial.flush()
    app.serial.write("L".encode())
    return {"led":"off"}

from fastapi import FastAPI, Request, Response, Form
from fastapi.responses import HTMLResponse
from fastapi.staticfiles import StaticFiles
from fastapi.templating import Jinja2Templates
from fastapi.encoders import jsonable_encoder
from typing import Annotated
import os

import serial
import serial.tools.list_ports



app = FastAPI()
app.led_status = False
app.port = None
app.serial = None

app.mount("/static", StaticFiles(directory="static"), name="static")
templates = Jinja2Templates(directory="templates")

"""
@app.get("/items/{id}", response_class=HTMLResponse)
async def read_item(request: Request, id: str):
    return templates.TemplateResponse("item.html", {"request": request, "id": id})
"""
# https://code-maven.com/slides/python/fastapi-return-html-file
# https://gist.github.com/gbaldera/3751301
# https://jinja.palletsprojects.com/en/3.1.x/templates/
# https://fastapi.tiangolo.com/advanced/custom-response/
# https://stackoverflow.com/questions/74504161/how-to-submit-selected-value-from-html-dropdown-list-to-fastapi-backend
# https://opentechschool.github.io/python-flask/core/forms.html

# https://fastapi.tiangolo.com/tutorial/request-forms/ (Instalar)
# https://eugeneyan.com/writing/how-to-set-up-html-app-with-fastapi-jinja-forms-templates/


@app.get('/')
def root():
    return {"App": "Ready"}

@app.get("/home", response_class=HTMLResponse)
async def read_item(request: Request):
    if app.serial != None:
        # Verificacion del estado del serial 
        if app.serial.isOpen() == True:
            print("Puerto serial desconectado...")
            app.serial.close()
    # Lista de los puertos
    comlist = serial.tools.list_ports.comports()
    puertos = []
    for element in comlist:
      puertos.append(element.device)
    # Actualización de la template asociada a la conexión
    return templates.TemplateResponse("index.html", {"request": request, "puertos": puertos})

@app.get("/control")
async def control(request: Request, port: str):
    app.port = port
    print(f"Iniciando conexión serial con el puerto {app.port} a 9600 bps")
    app.serial = serial.Serial(app.port,9600)
    if app.serial == None:
        return {"Connection": "Fail"}
    else:
        # return {"Connection": "Open"}
        return templates.TemplateResponse("control.html", {"request": request, "puerto": app.port})

@app.get("/led_change")
async def led_on(request: Request):
    # Cambio del estado del led al opuesto
    app.led_status = not(app.led_status)
    if app.led_status:
        # Envio del comando de encendido del led
        print("LED: On")
        app.serial.write(b'h')
    else:
        # Envio del comando de apagado del led
        print("LED: Off")
        app.serial.write(b'l')
    # Actualización de la template asociada al control del led
    return templates.TemplateResponse("control.html", {"request": request, "puerto": app.port})

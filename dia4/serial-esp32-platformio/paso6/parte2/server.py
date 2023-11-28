from fastapi import FastAPI, Request, Response, Form
from fastapi.responses import HTMLResponse
from fastapi.staticfiles import StaticFiles
from fastapi.templating import Jinja2Templates
from fastapi.encoders import jsonable_encoder
from typing import Annotated
import os

app = FastAPI()

app.mount("/static", StaticFiles(directory="static"), name="static")
app.led_status = False
app.port = None

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
    return 'Test'

@app.get("/home", response_class=HTMLResponse)
async def read_item(request: Request):
    puertos = ["COM1", "COM2", "COM3"]
    return templates.TemplateResponse("index.html", {"request": request, "puertos": puertos})

@app.get("/control")
async def control(request: Request, port: str):
    print(request)
    app.port = port
    return templates.TemplateResponse("control.html", {"request": request, "puerto": app.port})

@app.get("/led_change")
async def led_on(request: Request):
    print(request)
    app.led_status = not(app.led_status)
    if app.led_status:
        print("LED: On")
    else:
        print("LED: Off")
    return templates.TemplateResponse("control.html", {"request": request, "puerto": app.port})

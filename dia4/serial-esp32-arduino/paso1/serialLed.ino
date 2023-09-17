/* Entradas y salidas */
#define LIGHT1 26          // P26 (GPIO26)

/* Comandos */
#define LIGHT_ON 'H'       // Luz encendida  
#define LIGHT_OFF 'L'      // Luz apagada  



int cmd = 0; // Comnado entrado por serial

void setup() {
  // Configuración de los puertos digitales
  pinMode(LIGHT1, OUTPUT);    
  digitalWrite(LIGHT1, LOW);
  // Configuracion del puerto serial
  Serial.begin(9600); 
  
}

void loop() {
  // reply only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    cmd = Serial.read();

    // Encendido o apagado de la luz segun el comando
    if(cmd == LIGHT_ON) {
      digitalWrite(LIGHT1, HIGH);
      Serial.println("Light -> ON");
    }
    else if(cmd == LIGHT_OFF) {
      digitalWrite(LIGHT1, LOW);    
      Serial.println("Light -> OFF");
    } 
  }
}

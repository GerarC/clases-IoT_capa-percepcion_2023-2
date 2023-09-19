
void setup() {
  // El LED integrado está conectado al pin 2.
  Serial.begin(9600);
}

void loop() {
  Serial.println("Hola mundo!!!");
  delay(1000);
}

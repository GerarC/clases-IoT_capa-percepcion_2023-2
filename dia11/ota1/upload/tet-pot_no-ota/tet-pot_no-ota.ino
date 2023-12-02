const int analogInPin = 34;  //  GPIO15
int sensorValue = 0;         // Value read from the pot

void setup() {
  // Start Serial  
  Serial.begin(115200);    
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // Read the analog in value
  sensorValue  = analogRead(analogInPin);
  
  // Display data  
  Serial.print("Sensor:  ");
  Serial.println(sensorValue);
   
  // Wait a few seconds between measurements.
  delay(2000);
}
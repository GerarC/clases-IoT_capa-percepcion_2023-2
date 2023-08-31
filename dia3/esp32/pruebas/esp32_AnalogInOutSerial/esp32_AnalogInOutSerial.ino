/*
  Ejemplo adaptado para el ESP32 de:

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogInOutSerial
*/

const int analogInPin = 15;  // Analog input pin that the potentiometer is attached to GPIO15
const int analogOutPin = LED_BUILTIN; // Analog output pin that the LED is attached to ESP32 led.

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 4095, 0, 255); // ADC de 12 bits
  // change the analog out value:
  analogWrite(analogOutPin, outputValue);

  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(2);
}

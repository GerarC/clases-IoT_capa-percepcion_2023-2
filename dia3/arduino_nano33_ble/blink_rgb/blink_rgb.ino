// How to control the RGB Led and Power Led of the Nano 33 BLE boards.  

#define DELAY_TIME 1000 // miliseconds

#define RED 22     
#define BLUE 24     
#define GREEN 23
#define LED_PWR 25

void setup() {
  // initialize the digital Pin as an output
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(LED_PWR, OUTPUT);
}

// the loop function runs over and over again
void loop() {
  digitalWrite(RED, LOW); // turn the LED off by making the voltage LOW
  delay(DELAY_TIME);      // wait for a second
  digitalWrite(GREEN, LOW);
  delay(DELAY_TIME);  
  digitalWrite(BLUE, LOW);
  delay(DELAY_TIME);  
  digitalWrite(RED, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(DELAY_TIME);                         
  digitalWrite(GREEN, HIGH);
  delay(DELAY_TIME);  
  digitalWrite(BLUE, HIGH);
  delay(DELAY_TIME);  
  digitalWrite(LED_PWR, HIGH);
  delay(DELAY_TIME);  
  digitalWrite(LED_PWR, LOW);
  delay(DELAY_TIME);  
}
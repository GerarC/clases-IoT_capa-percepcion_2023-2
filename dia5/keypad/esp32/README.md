# En construcción

A continuación se muestran una lista de ejemplos tomados de diferentes partes:

Teclado matricial ([link](https://wokwi.com/projects/375583898825876481))

* https://playground.arduino.cc/Main/KeypadTutorial/
* https://learn.adafruit.com/matrix-keypad
* https://randomnerdtutorials.com/arduino-membrane-keypad-tutorial/
* 


```ino
#include <Keypad.h>

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Three columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'#','0','*','D'}
};

#define ROW1 23
#define ROW2 22
#define ROW3 21
#define ROW4 19
#define COL1 18
#define COL2 5
#define COL3 4
#define COL4 2

// Connect keypad ROW1, ROW2, ROW3 and ROW4 to these Arduino pins.
byte rowPins[ROWS] = { ROW1, ROW2, ROW3, ROW4 };
// Connect keypad COL0, COL1, COL2 and COL3 to these Arduino pins.
byte colPins[COLS] = { COL1, COL2, COL3, COL4 }; 

// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

const int ledpin = 2;

void setup()
{
  pinMode(ledpin,OUTPUT);
  digitalWrite(ledpin, HIGH);
  Serial.begin(9600);
  Serial.println("System Ok...");
}

void loop()
{
  char key = kpd.getKey();
  if(key)  // Check for a valid key.
  {
    switch (key)
    {
      case '*':
        digitalWrite(ledpin, LOW);
        break;
      case '#':
        digitalWrite(ledpin, HIGH);
        break;
      default:
        Serial.println(key);
    }
  }
}
```
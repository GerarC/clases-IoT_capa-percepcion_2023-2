
# Ejemplo debug

## Montaje

![esp32_debug-serial](esp32_debug-serial.png)

Link de la simulación ([link](https://wokwi.com/projects/358500354708861953))

## Código

```ino
/*-------------- Debug --------------*/
  
// Comentar siguiente linea para no hacer debug serial  
#define DEBUG 1  

/*-------------- Puertos --------------*/

// Swichtes
#define SW1 22
#define SW0 23

// Leds switches
#define LED_SW1 21
#define LED_SW0 19

// Leds secuencia
#define LED_PWM 4

// Potenciometro
#define POT 2

/*-------------- Variables --------------*/
int pot_value = 0;   // Valor del potenciometro (0 - 2013)
int val_pwm = 0;     // Valor del pwm (0 - 255)
int sw_val1;
int sw_val0;
int num_seq; 
int loop_time = 500;

void setup() {
  // Inicializacion de las entradas
  inicializar_entradas();
  inicializar_salidas();
  // Debug Serial
  #if DEBUG
  Serial.begin(9600);
  Serial.println("Configuración de I/O -> OK");
  #endif
}

void loop() {
  /* Entrada analoga */
  #if DEBUG
  Serial.println("------------------------------------");
  #endif
  // Lectura de la entrada analoga (Potenciometro)
  pot_value = analogRead(POT);
  // Mapeo y escritura analoga (PWM)  
  val_pwm = map(pot_value, 0 , 4095, 0, 255);
  analogWrite(LED_PWM,val_pwm);
  #if DEBUG
  // --- Mensajes de debug (Variables analogas) --- //
  Serial.print("POT: ");
  Serial.print(pot_value);  
  Serial.print(" - LED (PWM): ");
  Serial.println(val_pwm); 
  #endif
  // Lectura de los switches
  sw_val0 = digitalRead(SW0);  
  sw_val1 = digitalRead(SW1);
  // --- Mensajes de debug (Entradas digitales) --- //
  #if DEBUG
  Serial.print("SW0: ");
  Serial.print(sw_val0);
  Serial.print(" - SW1: ");
  Serial.println(sw_val1);
  #endif
  // Obtencion de la secuencia binaria
  num_seq = obtener_numero_secuencia(sw_val1, sw_val0);  
  #if DEBUG
  // --- Mensajes de debug Opcion --- //
  Serial.print("Opcion: ");
  Serial.println(num_seq, BIN);
  #endif
  // Encendido de los leds
  encender_leds_indicadores(num_seq); 
  delay(loop_time);
}

void inicializar_entradas() {
  // Inicialice aqui las entradas
  pinMode(SW1, INPUT);
  pinMode(SW0, INPUT);
}

void inicializar_salidas() {
  // Inicialice aqui las salidas
  pinMode(LED_SW1, OUTPUT);
  pinMode(LED_SW0, OUTPUT);
}

int obtener_numero_secuencia(int sw1, int sw0) {
  // Obtiene el numero asociado a una combinación de switches
  int number;  
  if ((sw1 == LOW)&&(sw0 == LOW)) {
    number = 0;  
  }
  else if ((sw1 == LOW)&&(sw0 == HIGH)) {
    number = 1;
  }
  else if ((sw1 == HIGH)&&(sw0 == LOW)) {
    number = 2;  
  }
  else {
    number = 3;
  }  
  return number;
}

void encender_leds_indicadores(int number) {
  // Encendido de luces indicadores  
  switch(number) {
    case 0:
      digitalWrite(LED_SW1,LOW);
      digitalWrite(LED_SW0,LOW);
      break;
    case 1:
      digitalWrite(LED_SW1,LOW);
      digitalWrite(LED_SW0,HIGH);
      break;
    case 2:
      digitalWrite(LED_SW1,HIGH);
      digitalWrite(LED_SW0,LOW);
      break;
    default:
      digitalWrite(LED_SW1,HIGH);
      digitalWrite(LED_SW0,HIGH);
  }
}
```

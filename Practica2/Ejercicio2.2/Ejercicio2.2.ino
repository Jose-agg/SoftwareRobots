/*
   Circuito disponible en Tinkercad en el siguiente enlace:
   https://www.tinkercad.com/things/hlJc0ERJcDu

   La sección "Código" está vacía. Hay que copiar el código de
   este fichero e introducirlo ahí para probar el funcionamiento.
*/

#include <Keypad.h>

// Pines utilizados para los estados abierto y cerrado de la puerta
const int ledDoorOpened = 6; // es un led rojo, que cuando está encendido indica puerta abierta/abriéndose
const int ledDoorClosed = 7; // es un led verde, que cuando está encendido indica puerta cerrada/cerrándose

// Teclado
const byte numRows = 4; // numero de filas del teclado
const byte numColumns = 4; // numero de columnas del teclado
// Matriz con todas las teclas del teclado
char keys[numRows][numColumns] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowsPins[numRows] = {2, 3, 4, 5}; // Pines utilizados para las filas
byte columnsPins[numColumns] = {A0, A1, A2, A3}; // Pines utilizados para las columnas

// Indica el estado de la puerta (abierta/cerrada)
boolean doorIsOpened = false;
// Almacena el instante en el que se abrió la puerta en milisegundos
double timeDoorWasOpened;

// Creamos un objeto Keypad que representa el teclado
Keypad _keypad = Keypad(makeKeymap(keys), rowsPins, columnsPins, numRows, numColumns);

void setup() {
  Serial.begin(9600);
  Serial.println("\n---------\n  Setup\n---------");

  // Salidas de los leds
  pinMode(ledDoorOpened, OUTPUT);
  pinMode(ledDoorClosed, OUTPUT);

  // Inicialmente la puerta está cerrada
  digitalWrite(ledDoorClosed, HIGH);
}

void loop() {
  // Comprobamos si la puerta está abierta y han pasado los 5 segundos
  checkIfTimeHasPassed();

  // Comprobamos si se pulsa el teclado
  checkKeystrokes();
}

void checkIfTimeHasPassed() {
  // Si la puerta está abierta y han pasado 5 segundos desde que se abrió
  if (doorIsOpened && millis() - timeDoorWasOpened >= 5000) {
    Serial.println("\n> Se acaban los 5 segundos de apertura");
    // Se cierra la puerta
    closeTheDoor();
  }
}

void checkKeystrokes() {
  // Obtenemos la tecla pulsada (devuelve '\0' si no se pulsó ninguna)
  char key = _keypad.getKey();

  // Si se pulsó alguna tecla
  if (key != '\0') {
    Serial.println("Tecla pulsada: " + String(key));

    // Si la tecla pulsada es la A y la puerta está cerrada
    if (key == 'A' && !doorIsOpened) {
      // Abrimos la puerta durante 5 segundos
      openTheDoorFor5Seconds();
    }
    // Si la tecla pulsada es la C y la puerta está abierta
    else if (key == 'C' && doorIsOpened) {
      Serial.println("\n> Se fuerza al cierre de la puerta");
      // Se cierra la puerta
      closeTheDoor();
    }
  }
}

void openTheDoorFor5Seconds() {
  Serial.println("\n# Se abre la puerta");

  // Se encienden/apagan los leds correspondientes
  digitalWrite(ledDoorClosed, LOW);
  digitalWrite(ledDoorOpened, HIGH);

  // Se indica que la puerta está abierta y se almacena el momento en el que se abrió
  doorIsOpened = true;
  timeDoorWasOpened = millis();
}

void closeTheDoor() {
  Serial.println("# Se cierra la puerta\n");

  // Se encienden/apagan los leds correspondientes
  digitalWrite(ledDoorClosed, HIGH);
  digitalWrite(ledDoorOpened, LOW);

  // Se indica que la puerta está cerrada
  doorIsOpened = false;
}

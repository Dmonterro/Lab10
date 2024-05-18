#include <Servo.h>

Servo myServo;  // Crea un objeto de tipo Servo

const int servoPin = A0;  // Pin al que está conectado el servo
int angle = 90;           // Ángulo inicial del servo
int speed = 50;           // Velocidad inicial (0 a 100)

unsigned long lastCommandTime = 0; // Último momento en que se recibió un comando

void setup() {
  Serial.begin(9600);               // Inicia la comunicación serial a 9600 baudios
  myServo.attach(servoPin);         // Asigna el pin al servo
  myServo.write(angle);             // Establece el ángulo inicial
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();   // Lee el comando desde la comunicación serial
    lastCommandTime = millis();     // Registra el tiempo del último comando

    switch (command) {
      case 'D':  // Gira el servo a la derecha
        moveServo(angle + 45);
        break;
      case 'I':  // Gira el servo a la izquierda
        moveServo(angle - 45);
        break;
      case 'V':  // Establece la velocidad
        speed = readSerialInt();
        break;
      case 'G':  // Establece el ángulo
        angle = readSerialInt();
        moveServo(angle);
        break;
      default:
        Serial.println("Comando no reconocido");
        break;
    }
  }

  // Control de límite de tiempo para evitar bloqueos
  if (millis() - lastCommandTime > 10000) { // Si no se recibe ningún comando durante 10 segundos
    angle = 90;                             // Restablece el ángulo a la posición central
    moveServo(angle);
  }
}

void moveServo(int targetAngle) {
  int currentAngle = myServo.read();  // Lee el ángulo actual del servo
  int step = (targetAngle > currentAngle) ? 1 : -1;  // Determina la dirección del movimiento

  while (currentAngle != targetAngle) {
    currentAngle += step;  // Ajusta el ángulo actual en pequeños pasos
    myServo.write(currentAngle);  // Envía el ángulo al servo
    delay(map(speed, 0, 100, 20, 1));  // Ajusta el delay según la velocidad
  }
}

int readSerialInt() {
  while (!Serial.available()) {}  // Espera a que llegue el siguiente byte
  return Serial.parseInt();       // Lee el número entero desde la comunicación serial
}

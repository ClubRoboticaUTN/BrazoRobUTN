#include <Servo.h>

// Definir los pines utilizados por el joystick y los servos
const int pinX = A0;  // Pin analógico para el eje X del joystick
const int pinY = A1;
const int servoPin1 = 9;   // Pin PWM para el primer servo
const int servoPin2 = 10;  // Pin PWM para el segundo servo
const int servoPin3 = 11;
int xValue;
int yValue;
int angle11 = 0, angle22 = 180, angle33 = 90;

Servo servo1;  
Servo servo2;  
Servo servo3;
bool flag = 0;

void setup() {
  Serial.begin(9600);        // Iniciar comunicación serial
  servo1.attach(servoPin1);  // Adjuntar el primer servo al pin correspondiente
  servo2.attach(servoPin2);  // Adjuntar el segundo servo al pin correspondiente
  servo3.attach(servoPin3);
  servo1.write(angle11);
  servo2.write(angle22);
  servo3.write(angle33);
}
void loop() {
 
  int x1Value = analogRead(pinX);
  int y1Value = analogRead(pinY);

  flag = 0;
  if (abs(x1Value - 500) > 30 && abs(y1Value - 500) > 30) {
    flag = 1;
    xValue = analogRead(pinX);
    yValue = analogRead(pinY);
    Serial.print("\t LEIDO ");
  }
  
  int angle1 = map(xValue, 531, 1023, 0, 180);
  int angle2 = map(xValue, 500, 0, 0, 180);

  angle33 = map(yValue, 0, 1023, 20, 160);

  servo3.write(angle33);

  servo1.write(angle11);

  servo2.write(angle22);
 
  if (flag) {
    Serial.print("Servo 1 Angle: ");
    Serial.print(angle11);
    Serial.print("\t Servo 2 Angle: ");
    Serial.println(angle22);
    Serial.print("Servo 3 Angle:");
    Serial.print(angle33);
    Serial.print("\t Joystick x: ");
    Serial.println(xValue);
    Serial.print("\t Joystick y: ");
    Serial.println(yValue);
  }
  if (flag) {
    angle11=angle11+angle1/10;
    if(angle1 =! 0){ //sentido horario
      if(angle11 < 180){
        angle11=angle11+angle1/10;
      }
      else{
        angle22=angle22-angle1/10;
      }
    }
    angle22=angle22+angle2/10;
    if(angle2 =! 0){//senrido antihorario
      if(angle22 < 180){
        angle22=angle22+angle2/10;
      }
      else{
        angle11=angle11-angle2/10;
      }
    }
  }
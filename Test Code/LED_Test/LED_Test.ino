int ENA = 2, ENB = 8;
int IN1 = 3, IN2 = 4, IN3 = 5, IN4 = 6;
float leftSpeed, rightSpeed, minSpeed = 100, maxSpeed = 255, speedVal, straightSpeed;
float timeDly, baseFeetPerSecond = 2.2, baseDegreesPerSecond = 360, degreesPerSecond;
int RedLEDsPin = 52, BlueLEDsPin = 53;
void setup() {
  Serial.begin(115200);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(RedLEDsPin, OUTPUT);
  pinMode(BlueLEDsPin, OUTPUT);
  ledAction("Red", 0);
  ledAction("Blue", 0);
  //digitalWrite(ENA, HIGH);
  //digitalWrite(ENB, HIGH);
  //runCommand();
}

void loop() {

  Serial.print(F("\r\nR3\tRed Team"));
  //PS4.setLed(Red);
  ledAction("Red", 0);
  ledAction("Blue", 1);
  delay(150);
  ledAction("Red", 1);
  ledAction("Blue", 0);
  delay(150);
}
void ledAction(String color, int ledState) {
  if (color == "Red") {
    digitalWrite(RedLEDsPin, ledState);
  }
  if (color == "Blue") {
    digitalWrite(BlueLEDsPin, ledState);
  }
}
void motorControl(int IN1State, int IN2State, int IN3State, int IN4State) {
  //digitalWrite(ENA, ENAState);
  //digitalWrite(ENB, ENBState); // look up math for map function use map but not function. only math equation.
  digitalWrite(IN1, IN1State);
  digitalWrite(IN2, IN2State);
  digitalWrite(IN3, IN3State);
  digitalWrite(IN4, IN4State);
}
void setSpeed(int ENAVal, int ENBVal) {
  analogWrite(ENA, ENAVal);
  analogWrite(ENB, ENBVal);
  leftSpeed = ENAVal;
  rightSpeed = ENBVal;
  straightSpeed = ENAVal;

}
void stopMoving() {
  motorControl(0, 0, 0, 0);
}
void moveForwards(float distance, float feetPerSecond) {
  //feetPerSecond = baseFeetPerSecond * (straightSpeed / maxSpeed);
  //feetPerSecond = (.0075 * straightSpeed) + .35;
  speedVal = (feetPerSecond - 0.35) / 0.0075;
  timeDly = (distance / feetPerSecond) * 1000.0;
  setSpeed(speedVal, speedVal);
  Serial.print(speedVal);
  Serial.print("\t\t");
  Serial.println(timeDly);
  motorControl(1, 0, 0, 1);
  delay(timeDly);
  stopMoving();
}
void moveBackwards(float distance, float feetPerSecond) {
  //feetPerSecond = baseFeetPerSecond * (straightSpeed / maxSpeed);
  speedVal = (feetPerSecond - 0.35) / 0.0075;
  timeDly = (distance / feetPerSecond) * 1000.0;
  setSpeed(speedVal, speedVal);
  motorControl(0, 1, 1, 0);
  delay(timeDly);
  stopMoving();
}
void turn(int degree, String dir) {
  stopMoving();
  delay(100);
  setSpeed(125, 125); // add var
  if (dir == "left") {
    motorControl(0, 1, 0, 1);
    //degreesPerSecond = map(leftSpeed, minSpeed, maxSpeed,
    //degreesPerSecond = baseDegreesPerSecond * (leftSpeed / maxSpeed);
  }
  else if (dir == "right") {
    motorControl(1, 0, 1, 0);
    //degreesPerSecond = baseDegreesPerSecond * (rightSpeed / maxSpeed);
  }
  // Omega = 398 degrees per second.
  // Theta = Omega * time

  //timeDly = (degree / degreesPerSecond) * 1000;
  timeDly = (degree + 6) / 136.29 * 1000;
  delay(timeDly);
  stopMoving();
}
void calibrateStraight(String dir) {
  if (dir == "forwards") {
    motorControl(1, 0, 0, 1);
  }
  else if ( dir == "backwards") {
    motorControl(0, 1, 1, 0);
  }
  delay(1000); // goes 12 feet and 3 inches in 5 seconds 12.25 = rate * time.
  //r = d/t . r = 12.25/5 = 2.45 feet/second. t = d/r. t = d/ 2.45. t = d/2.45
  stopMoving();
}
void calibrateTurn(String dir) {
  stopMoving();
  setSpeed(125, 125);
  if (dir == "left") {
    motorControl(0, 1, 0, 1);
  }
  else if (dir == "right") {
    motorControl(1, 0, 1, 0);
  }
  delay(5000); //5 Revolutions and 190 degrees.  360*5 + 190. 1800 + 190 = 1990
  // Theta = Omega * time. Omega = Theta/time. Omega = 1990/5. Omega = 398 degrees per second.
  //speedVal = (feetPerSecond - 0.35) / 0.0075;
  //setSpeed(speedVal, speedVal);
  stopMoving();
}
void runCommand() {
  moveForwards(3, 1.3);
  turn(90, "right");
  moveForwards(1.5, 2);
  turn(270, "left");
  moveBackwards(3, 1.9);
  turn(360, "right");
}

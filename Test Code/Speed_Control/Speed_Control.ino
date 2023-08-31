int ENA = 5, ENB = 6;
int IN1 = 7, IN2 = 8, IN3 = 9, IN4 = 11;
float leftSpeed, rightSpeed, minSpeed = 100, maxSpeed = 255, straightSpeed;
float timeDly, baseFeetPerSecond = 2.2, feetPerSecond, baseDegreesPerSecond = 360, degreesPerSecond;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  //digitalWrite(ENA, HIGH);
  //digitalWrite(ENB, HIGH);
  setSpeed(175, 175);
  moveForwards(1);
  //turn(180,"left");
}

void loop() {
  // put your main code here, to run repeatedly:
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
void moveForwards(float distance) {
  motorControl(1, 0, 0, 1);
  //feetPerSecond = baseFeetPerSecond * (straightSpeed / maxSpeed);
  feetPerSecond = (.0075*straightSpeed) + .35;
  timeDly = (distance / feetPerSecond) * 1000.0;
  Serial.print(feetPerSecond);
  Serial.print("\t\t\t");
  Serial.print(straightSpeed);
  Serial.print("\t\t\t");
  Serial.println(timeDly);
  delay(timeDly);
  stopMoving();
}
void moveBackwards(float distance) {
  motorControl(0, 1, 1, 0);
  //feetPerSecond = baseFeetPerSecond * (straightSpeed / maxSpeed);
  feetPerSecond = (.0075*straightSpeed) + .35;
  timeDly = (distance / feetPerSecond) * 1000;
  delay(timeDly);
  stopMoving();
}
void turn(int degree, String dir) {
  if (dir == "left") {
    motorControl(0, 1, 0, 1);
    //degreesPerSecond = map(leftSpeed, minSpeed, maxSpeed,
    degreesPerSecond = baseDegreesPerSecond * (leftSpeed / maxSpeed);
  }
  else if (dir == "right") {
    motorControl(1, 0, 1, 0);
    degreesPerSecond = baseDegreesPerSecond * (rightSpeed / maxSpeed);
  }
  // Omega = 398 degrees per second.
  // Theta = Omega * time

  timeDly = (degree / degreesPerSecond) * 1000;
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
  if (dir == "left") {
    motorControl(0, 1, 0, 1);
  }
  else if (dir == "right") {
    motorControl(1, 0, 1, 0);
  }
  delay(5000); //5 Revolutions and 190 degrees.  360*5 + 190. 1800 + 190 = 1990
  // Theta = Omega * time. Omega = Theta/time. Omega = 1990/5. Omega = 398 degrees per second.
  stopMoving();
}

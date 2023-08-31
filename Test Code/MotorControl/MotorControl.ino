int ENA = 5, ENB = 6;
int IN1 = 7, IN2 = 8, IN3 = 9, IN4 = 11;
void setup() {
  // put your setup code here, to run once:
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  moveForwards();
  delay(1000);
  moveBackwards();
  delay(1000);
}

void motorControl(int IN1State, int IN2State, int IN3State, int IN4State) {
  digitalWrite(IN1, IN1State);
  digitalWrite(IN2, IN2State);
  digitalWrite(IN3, IN3State);
  digitalWrite(IN4, IN4State);
}
void moveForwards() {
  motorControl(1, 0, 0, 1);
}
void moveBackwards() {
  motorControl(0, 1, 1, 0);
}

#include <Servo.h>
int serPin = 9;
int serPin2 = 13;
int x = 0;
Servo ser;
Servo ser2;
Servo ser3;
Servo ser4;
Servo ser5;

void setup() {
  // put your setup code here, to run once:
  ser.attach(A2);
  ser2.attach(A3);
  ser3.attach(9);
  ser4.attach(11);
  ser5.attach(13);

  ser.write(100); // 180 - 0
  ser2.write(0); //180 - 0
  ser3.write(105); // 0 - 180
  ser4.write(80); // 180 - 0
  ser5.write(50); //90 - 0
  }

void loop() {
  // put your main code here, to run repeatedly:
  /*for (int j = 0; j<=180; j++) {
    ser.write(j);
    ser2.write(j);
    delay(20);
    }*/

}

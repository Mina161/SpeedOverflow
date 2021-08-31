#include <AFMotor.h>
AF_DCMotor front_left(3, MOTOR12_1KHZ);
AF_DCMotor back_left(4, MOTOR12_1KHZ);
AF_DCMotor right(2, MOTOR12_1KHZ);

const int LeftIR = A3;
int leftValue;
const int RightIR = A0;
int rightValue;
const int CenterIR = A1;
int centerValue;
const int black = 900;
const int fast = 250;
const int slow = 110;

void setup() {
  pinMode(LeftIR, INPUT);
  pinMode(RightIR, INPUT);
  pinMode(CenterIR, INPUT);
  Serial.begin(9600);
  setAllSpeed(fast);
  right.run(RELEASE);
  back_left.run(RELEASE);
  front_left.run(RELEASE);
  delay(1000);
}

void setAllSpeed(int s) {
  front_left.setSpeed(s);
  right.setSpeed(s);
  back_left.setSpeed(s);
}

void setRightSpeed(int s) {
  right.setSpeed(s);
}

void setLeftSpeed(int s) {
  front_left.setSpeed(s);
  back_left.setSpeed(s);
}

void forward() {
  front_left.run(FORWARD);
  right.run(FORWARD);
  back_left.run(FORWARD);
}

void backward() {
  back_left.run(BACKWARD);
  right.run(BACKWARD);
  front_left.run(BACKWARD);
}

void brake() {
  right.run(RELEASE);
  back_left.run(RELEASE);
  front_left.run(RELEASE);
}

void turnLeft() {
  setAllSpeed(fast);
  right.run(FORWARD);
  back_left.run(BACKWARD);
  front_left.run(BACKWARD);
}

void turnRight() {
  setAllSpeed(fast);
  right.run(BACKWARD);
  back_left.run(FORWARD);
  front_left.run(FORWARD);
}

void readAll() {
  leftValue = analogRead(LeftIR);
  rightValue = analogRead(RightIR);
  centerValue = analogRead(CenterIR);
}

void loop() {
  
  readAll();
   
//  delay(500);

  Serial.print("Left ");
  Serial.println(leftValue);

  Serial.print("Center ");
  Serial.println(centerValue);

  Serial.print("Right ");
  Serial.println(rightValue);

//  delay(1000);

  if (leftValue >= black && rightValue < black) {
    brake();
    turnLeft();
    delay(50);
  }

  if (leftValue < black && rightValue >= black) {
    brake();
    turnRight();
    delay(50);
  }

  if (leftValue < black && rightValue < black) {
    setAllSpeed(slow);
    forward();
  }

  if (leftValue >= black && centerValue>=black && rightValue >= black) {
    setAllSpeed(slow);
    forward();
  }

  if(leftValue< black && centerValue<black && rightValue<black){
    readAll();
    while(!(centerValue>=black)){
      readAll();
      turnRight();
    }
    brake();
    delay(50);
    
    setAllSpeed(slow);
    forward();
    delay(200);
  }
  delay(1);
}

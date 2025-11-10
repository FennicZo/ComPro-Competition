#include <Arduino.h>

// PINS
#define ENA 9
#define IN1 3
#define IN2 4

#define ENB 10
#define IN3 5
#define IN4 6

#define START_BUTTON A1   // Press to start

// MOVEMENT TIMING
int MOTOR_SPEED = 100;
int RAM_MS     = 700;
int BACKUP_MS  = 80;
int REVERSE_MS = 150;
int TURN_90_MS = 150;
int MOVE_PAUSE = 150;
const int SETTLE_MS = 80;

// MOTOR CONTROL
void motorAForward(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, MOTOR_SPEED);
}
void motorABackward(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, MOTOR_SPEED);
}
void motorBForward(){
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, MOTOR_SPEED);
}
void motorBBackward(){
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, MOTOR_SPEED);
}

void stopAll(){
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  delay(SETTLE_MS);
}

// SPIN TURN
void turnRight90(){
  motorAForward();
  motorBBackward();
  delay(TURN_90_MS);
  stopAll();
}
void turnLeft90(){
  motorABackward();
  motorBForward();
  delay(TURN_90_MS);
  stopAll();
}

// MOVEMENT
void forwardBlockIndexed(){
  motorAForward();
  motorBForward();
  delay(RAM_MS);
  stopAll();

  motorABackward();
  motorBBackward();
  delay(BACKUP_MS);
  stopAll();
}

void reverseBlock(){
  motorABackward();
  motorBBackward();
  delay(REVERSE_MS);
  stopAll();
}

// SHORTCUT FUNCTIONS
void fwd(int n){
  while(n--){
    forwardBlockIndexed();
    delay(MOVE_PAUSE);
  }
}

void rev(int n){
  while(n--){
    reverseBlock();
    delay(MOVE_PAUSE);
  }
}

void turnR(int n){
  while(n--){
    turnRight90();
    delay(MOVE_PAUSE);
  }
}

void turnL(int n){
  while(n--){
    turnLeft90();
    delay(MOVE_PAUSE);
  }
}

// MAZE A PATH
void runMazeA(){

  // PART 1
  fwd(1); turnR(1);
  fwd(2); turnR(1);
  fwd(1);
  rev(1); turnL(1);
  fwd(1); turnL(1);

  // PART 2
  fwd(1); turnL(1);
  fwd(3); turnR(1);
  fwd(1); turnR(1);
  fwd(1); turnL(1);
  fwd(1); turnR(1);
  fwd(2); turnR(1);
  fwd(1); turnL(1);
  fwd(1); turnL(1);
  fwd(1);

  // PART 3 (reverse PART 2) ----
  rev(1); turnR(1);
  rev(1); turnR(1);
  rev(1); turnL(1);
  rev(2); turnL(1);
  rev(1); turnL(1);
  rev(1); turnR(1);
  rev(3); turnR(1);
  rev(1);

  // Finish path
  fwd(1); turnL(1);
  fwd(1);

  stopAll();
}

// MAIN
void waitRelease(){
  while(digitalRead(START_BUTTON)==LOW);
  while(digitalRead(START_BUTTON)==HIGH);
  delay(150);
}

void setup(){
  pinMode(START_BUTTON, INPUT_PULLUP);

  pinMode(IN1,OUTPUT); pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT); pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT); pinMode(ENB,OUTPUT);

  stopAll();
  Serial.begin(9600);
  Serial.println("READY — Press START");
}

void loop(){
  if(digitalRead(START_BUTTON)==LOW){
    delay(200);
    runMazeA();
    Serial.println("Run Complete — Press START to run again");
    waitRelease();
  }
}
#include <MultiStepper.h>
#include <AccelStepper.h>


#define MICROSTEPS 1
#define MOTOR_STEPS 200
#define DIR_Y 4
#define STEP_Y 5
#define LEFT_STOP 2
#define RIGHT_STOP 3
#define MAX_BLOCKS 2
#define TYPE 1
int HOMEPOSITION_FULLSTEPS;
int HOMEPOSITION_MICROSTEPS = HOMEPOSITION_FULLSTEPS * MICROSTEPS;
int DISTANCE_TO_EDGE;
int RIGHT_SIDE;
AccelStepper stepperY(TYPE, STEP_Y, DIR_Y);

void setup() {

  Serial.begin(115200);
  stepperY.setMaxSpeed(2000*MICROSTEPS);
  stepperY.setAcceleration(2000*MICROSTEPS);
  stepperY.setCurrentPosition(0);
  pinMode(LEFT_STOP, INPUT_PULLUP);
  digitalWrite(LEFT_STOP, HIGH);
  pinMode(RIGHT_STOP, INPUT_PULLUP);
  digitalWrite(RIGHT_STOP, HIGH);
  motorCalibrate(stepperY);
}

void loop() {

stepperY.move(-RIGHT_SIDE+1);
while(stepperY.currentPosition()!=stepperY.targetPosition()){
  stepperY.run();
}
stepperY.move(RIGHT_SIDE-1);
while(stepperY.currentPosition()!=stepperY.targetPosition()){
  stepperY.run();
}





}

void motorCalibrate(AccelStepper stepper) {
  int count = 0;

  Serial.println("Calibrating Motor...");
  Serial.println("Motor should be centered");
  delay(500);

  //move left until button hit
  stepper.move(-1100*MICROSTEPS);  
  //stepper.setSpeed(-1000*MICROSTEPS);
  while (digitalRead(LEFT_STOP) == true) {
    stepper.run();
    //stepper.runSpeed();
  }
  stepper.setCurrentPosition(0);
  Serial.print("Leftmost value: "); Serial.println(count);

  //move right until button hit
  stepper.move(1100*MICROSTEPS);
  //stepper.setSpeed(1000*MICROSTEPS);
  while (digitalRead(RIGHT_STOP) == true) {
    stepper.run();
    //stepper.runSpeed();
  }
  count = stepper.currentPosition(); //get steps at right edge
  Serial.print("Rightmost value: "); Serial.println(count);
  Serial.println("Calibration Complete");
  Serial.print("Total Microsteps Across Path: "); Serial.println(count);
  delay(500);
  
  Serial.println("Moving to center position...");
  delay(100);
  stepper.moveTo(count/2);
  stepper.setSpeed(-500*MICROSTEPS);
  
  while(stepper.currentPosition() != stepper.targetPosition()){
    stepper.runSpeed();//moves to center
  }
  delay(500);
  Serial.print("MiddlePosition: "); Serial.println(stepper.currentPosition());

  
  HOMEPOSITION_FULLSTEPS = count/2; //in microsteps 
  RIGHT_SIDE = count;


}

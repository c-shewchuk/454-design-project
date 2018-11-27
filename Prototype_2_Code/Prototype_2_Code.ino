#include <ArduinoSTL.h>

#include <DRV8825.h>
#include <BasicStepperDriver.h>
#include <MultiDriver.h>
#include <DRV8880.h>
#include <SyncDriver.h>
#include <DRV8834.h>
#include <A4988.h>

#include <PixySPI_SS.h>
#include <PixyI2C.h>
#include <Pixy.h>
#include <TPixy.h>
#include <PixyUART.h>

#include <math.h>
#include "Grid.h"
#include "Point.h"
using namespace std;


int counter = 0;
int dataset = 5;
int time;
float vxMatrix[5] = {0, 0, 0, 0, 0};
float vyMatrix[5] = {0, 0, 0, 0, 0};
float gamma;
float beta;
unsigned int bounces;
int yfinal;
int posOrNeg;
int loop_time;
int TABLE_HEIGHT_IN_STEPS;
int TABLE_WIDTH_IN_STEPS;
unsigned int PUCK_COLOUR = 0;
unsigned int AI_COLOUR = 1;
uint16_t blocks;
float pixToSteps;
int y_new;
int x_new;
int xAI;
int yAI;
int yOffset;
int xOffset;
int error  = 100;
#define MICROSTEPS 1
#define MOTOR_STEPS 200

int HOMEPOSITION_FULLSTEPS;
#define DIR_Y 8
#define STEP_Y 9
#define LEFT_STOP 2
#define RIGHT_STOP 3
int RPM = 200;
int HOMEPOSITION_MIRCOSTEPS = HOMEPOSITION_FULLSTEPS * MICROSTEPS;

#define MAX_BLOCKS 2;


Pixy pixy;
BasicStepperDriver stepperY(MOTOR_STEPS, DIR_Y, STEP_Y);

void setup() {
  // put your setup code here, to run once:
  //Get first pixy reading to initialize xPuck and yPuck (puck location)
  Serial.begin(115200);
  //Serial.print("Pixy successfully initialized");
  stepperY.begin(200, MICROSTEPS);

  pinMode(LEFT_STOP, INPUT_PULLUP);
  digitalWrite(LEFT_STOP, HIGH);
  pinMode(RIGHT_STOP, INPUT_PULLUP);
  digitalWrite(RIGHT_STOP, HIGH);

  /*
    Grid grid(TABLE_WIDTH,TABLE_HEIGHT);
    Point newPuckPoint;
    Point newAIPoint;
  */

  //loop_time = millis();
  motorCalibrate(stepperY);

}

void loop() {
  stepperY.move(100);
  delay(1000);
  stepperY.move(-100);
  delay(1000);

  /*
        loop_time = millis()-loop_time;
        blocks = pixy.getBlocks(MAX_BLOCKS);
        newPuckPoint = grid.translatePoint(pixy.blocks[PUCK_COLOUR].x,pixy.blocks[PUCK_COLOUR].y);
        newAIPoint = grid.translatePoint(pixy.blocks[AI_COLOUR].x,pixy.blocks[AI_COLOUR].y);
        x_new = newPuckPoint.xValue;
        y_new = newPuckPoint.yValue;
        xAI = newAIPoint.xValue;
        translateToCM();

        averageVelocity(x_new,y_new);
        predictY();
        //use absolute value for
        if (stepperY.currentPosition()-stepperY.targetPosition() == TRUE){
            if((abs(yfinal) > abs(stepperY.targetPosition())+error) || abs(yfinal) < abs(stepperY.targetPosition())-error){
                make_Decision();    //if decision off my certain amount, make new decision
                stepperY.runSpeed();
            }
        }
  */
}


void motorCalibrate(AccelStepper stepper) {
  int count = 0;
  int temp;

  Serial.println("Calibrating Motor...");
  Serial.println("Motor should be centered");
  delay(500);
  while (digitalRead(LEFT_STOP) == true) {
    stepper.move(-1);
    count--;
  }
  temp = count;
  Serial.print("Leftmost value: "); Serial.println(count + 1);
  while (digitalRead(RIGHT_STOP) == true) {
    stepper.move(+1);
    count++;
  }
  Serial.print("Rightmost value: "); Serial.println(count - 1);
  Serial.println("Calibration Complete");
  Serial.print("Total Microsteps Across Path: "); Serial.println(abs(temp) + count);
  delay(1000);
  Serial.println("Moving to center position...");
  stepper.move(temp - count); //moves to center
  HOMEPOSITION_FULLSTEPS = (temp - count) / MICROSTEPS; //in microsteps


}

void translateToSteps() {
  y_new += yOffset;
  x_new += xOffset;
  xAI += xOffset;
  y_new *= pixToSteps;
  x_new *= pixToSteps;
  xAI *= pixToSteps;

}

void trackYSteps() {

}
/*
  void averageVelocity() {
  vxPuck -= vxMatrix[counter]; //Deletes oldest vx velocity in set
  vyPuck -= vyMatrix[counter]; //Deletes oldest vyvelocity in set
  vxMatrix[counter] = (x_new - xPuck) / (dataset * loop_time / 1000); //DIVIDE BY TIME??? dataset variable allows us to avoid creating new variable to hold vxAverage
  vyMatrix[counter] = (y_new - yPuck) / (dataset * loop_time / 1000); //DIVIDE BY TIME??? dataset variable allows us to avoid creating new variable to hold vyAverage
  vxPuck += vxMatrix[counter];
  vyPuck += vxMatrix[counter];
  xPuck = x_new;
  yPuck = y_new;

  counter++;
  if (counter >= dataset) {
    counter = 0;        //ensures running average of _  number of data points
  }
  }


  void predictY() {
  gamma = abs(xAI - xPuck) / xPuck;
  posOrNeg = abs(vyPuck) / (-vyPuck); //if posOrNeg is pos then vy is up if posOrNeg is neg then vy is down
  beta = (gamma * vyPuck); //the -posOrNeg*striker_rad/2 is an arbitrary correction factor
  if (yPuck + beta < 0) {
  bounces = (int) (abs(beta) - yPuck) / TABLE_HEIGHT + 1;
  } else if (yPuck + beta > TABLE_HEIGHT) {
  bounces = (int) (abs(beta) - (TABLE_HEIGHT - yPuck)) / TABLE_HEIGHT + 1;
  } else {
    bounces = 0;
  }
  yfinal = (int) (abs((pow(-1, (bounces + 1) % 2)) - posOrNeg) / 2) * TABLE_HEIGHT -
  posOrNeg * pow(-1, (bounces % 2)) * (abs(beta) - posOrNeg * yPuck + ((posOrNeg - 1) / 2)
    TABLE_HEIGHT - (bounces - 1) * TABLE_HEIGHT));
  }


  void make_Decision() {

  stepperY.moveTo(yfinal);
  stepperY.setSpeed(vyAI);


  }
*/

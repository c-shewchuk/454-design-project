#include <ArduinoSTL.h>

#include <MultiStepper.h>
#include <AccelStepper.h>

#include <PixySPI_SS.h>
#include <PixyI2C.h>
#include <Pixy.h>
#include <TPixy.h>
#include <PixyUART.h>
#include <SPI.h>

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
int TABLE_HEIGHT;
int TABLE_WIDTH;
uint16_t blocks;
float mmToSteps;
int pxToMM = 22;
float stepsToMM;
float y_new;
float x_new;
int xAI; int vxAI; int xPuck;
int yAI; int vyAI; int yPuck;
int yOffset;
int xOffset;
int error  = 100;
int MAX_VELOCITY;
float vxPuck;
float vyPuck;

#define PUCK_COLOUR 0
#define AI_COLOUR 1
#define MICROSTEPS 1
#define TYPE 1
#define DIR_Y 8
#define STEP_Y 9
#define LEFT_STOP 2
#define RIGHT_STOP 3
#define MAX_BLOCKS 1
#define HEIGHT_MM 734
#define WIDTH_MM 1694



Pixy pixy;
AccelStepper stepperY(TYPE,STEP_Y,DIR_Y);

Point newPuckPoint;
Point newAIPoint;


void setup() {
  Serial.begin(9600);
  Serial.print("Pixy successfully initialized");

  //set up end stops
  pinMode(LEFT_STOP,INPUT_PULLUP);
  digitalWrite(LEFT_STOP,HIGH);
  pinMode(RIGHT_STOP,INPUT_PULLUP);
  digitalWrite(RIGHT_STOP,HIGH);
  
  loop_time = millis();
  motorCalibrate(stepperY);

  xAI = 22; xAI *= mmToSteps*pxToMM; //converts to steps
  
  pixy.init(); 
}

void loop() {
 
        loop_time = millis()-loop_time;
        blocks = pixy.getBlocks(MAX_BLOCKS);
        //get puck location from pixy in pixels
        Grid grid(HEIGHT_MM, WIDTH_MM); //units in mm
        newPuckPoint = grid.translatePoint(pixy.blocks[PUCK_COLOUR].x, pixy.blocks[PUCK_COLOUR].y); //in mm
        //get AI location from pixy in pixels
        
 
        
        //unpack objects
        x_new = newPuckPoint.xValue; //in mm
        y_new = newPuckPoint.yValue; // in mm
        Serial.print(x_new); Serial.print("  "); Serial.println(y_new);
        yAI = stepperY.currentPosition(); // in steps
        averageVelocity(x_new,y_new); 
  

        //translate unpacked values to steps
        translateToSteps(); //converts mm to steps

        

        //calculate average velocity in steps
   
        //calculate new yfinal and new vyAI
        predictY(); 
        

        //if currently running decision
        if (abs(stepperY.currentPosition()-stepperY.targetPosition()) == true){
            //check if decision is off course
            if((abs(yfinal) > abs(stepperY.targetPosition())+error) || abs(yfinal) < abs(stepperY.targetPosition())-error){
                make_Decision();    
                stepperY.runSpeed();
            }else{
              stepperY.runSpeed();
            }
        }else{
          make_Decision();
          stepperY.runSpeed();
        }
        if((digitalRead(LEFT_STOP) == false) || (digitalRead(RIGHT_STOP) == false)){
          stepperY.setSpeed(0);
        }
 
}


void motorCalibrate(AccelStepper stepper) {
  int count = 0;
  stepper.setMaxSpeed(5000*MICROSTEPS);
  stepper.setAcceleration(5000*MICROSTEPS);

//move to left side
stepper.move(-1100*MICROSTEPS);  
  while (digitalRead(LEFT_STOP) == true) {
    stepper.run();
  }
  stepper.setCurrentPosition(0);

//move to right side
  stepper.move(1100*MICROSTEPS);
  while (digitalRead(RIGHT_STOP) == true) {
    stepper.run();
  }

  TABLE_HEIGHT = stepper.currentPosition();
  TABLE_WIDTH = TABLE_HEIGHT*2.237;
  
  stepper.moveTo(TABLE_HEIGHT/2);
  stepper.setSpeed(-1000*MICROSTEPS);
  while(stepper.currentPosition() != stepper.targetPosition()){
    stepper.runSpeed();//moves to center
  }

}

void translateToSteps(){
  y_new *= mmToSteps;
  x_new *= mmToSteps;
}

void averageVelocity(float x_new, float y_new) {
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
  gamma = abs(xAI - xPuck) / vxPuck;
  posOrNeg = abs(vyPuck) / (-vyPuck); //if posOrNeg is pos then vy is up if posOrNeg is neg then vy is down
  beta = (gamma * vyPuck); //the -posOrNeg*striker_rad/2 is an arbitrary correction factor
  if (yPuck + beta < 0) {
  bounces = (int) (abs(beta) - yPuck) / TABLE_HEIGHT + 1;
  } else if (yPuck + beta > TABLE_HEIGHT) {
  bounces = (int) (abs(beta) - (TABLE_HEIGHT - yPuck)) / TABLE_HEIGHT + 1;
  } else {
    bounces = 0;
  }
  yfinal = (int) (abs((pow(-1, (bounces + 1) % 2)) - posOrNeg) / 2) * TABLE_HEIGHT - posOrNeg * pow(-1, (bounces % 2)) * (abs(beta) - posOrNeg * yPuck + ((posOrNeg - 1) / 2) * TABLE_HEIGHT - (bounces - 1) * TABLE_HEIGHT);
  vyAI = (yfinal-yAI)/gamma;

  
}


void make_Decision() {

  stepperY.moveTo(yfinal);
  if(vyAI>MAX_VELOCITY){
    vyAI = MAX_VELOCITY;
  }
  stepperY.setSpeed(vyAI);
  

}

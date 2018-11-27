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
using namespace std;

#define PUCK_COLOUR 0
#define AI_COLOUR 1
#define MICROSTEPS 1
#define TYPE 1
#define DIR_Y 4
#define STEP_Y 5
#define LEFT_STOP 2
#define RIGHT_STOP 3
#define MAX_BLOCKS 1
#define HEIGHT_MM 734
#define WIDTH_MM 1694


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
int absStep = 0; 
int TABLE_HEIGHT;
int TABLE_WIDTH;
uint16_t blocks;
float mmToSteps = 15.16;
int pxToMM = 2.4;
float y_new; float y_temp;
float x_new;
int yOffset = 32;
int xOffset = 13;
int xAI = (33-xOffset)*pxToMM*mmToSteps; int vxAI; int xPuck;
int yAI; int vyAI; int yPuck;
int error  = 100;
int MAX_VELOCITY;
float vxPuck;
float vyPuck;





Pixy pixy;
AccelStepper stepperY(TYPE,STEP_Y,DIR_Y);



void setup() {
  Serial.begin(9600);


  //set up end stops
  pinMode(LEFT_STOP,INPUT_PULLUP);
  digitalWrite(LEFT_STOP,HIGH);
  pinMode(RIGHT_STOP,INPUT_PULLUP);
  digitalWrite(RIGHT_STOP,HIGH);
  
  


  
  pixy.init(); 
  Serial.print("Pixy successfully initialized");
  blocks = pixy.getBlocks(MAX_BLOCKS); 
        //unpack objects
  x_new = pixy.blocks[PUCK_COLOUR].x; //in px
  y_new = pixy.blocks[PUCK_COLOUR].y; // in px
  xPuck = x_new;
  yPuck = y_new;
  Serial.println(motorCalibrate(stepperY));
  delay(1000);
  Serial.println(TABLE_HEIGHT);
  
}

void loop() {
 
        blocks = pixy.getBlocks(MAX_BLOCKS);
        
        //unpack objects
        x_new = pixy.blocks[PUCK_COLOUR].x; //in px
        y_new = pixy.blocks[PUCK_COLOUR].y; // in px
        yAI = stepperY.currentPosition(); // in steps
        
        translateToSteps(); //converts px to steps
        
        averageVelocity(x_new,y_new); 
        Serial.print("Puck position: "); Serial.println(y_new);
        Serial.print("AI position: "); Serial.println(stepperY.currentPosition()); 
        

        //translate unpacked values to steps
        Serial.println("This is ");
        Serial.println(stepperY.currentPosition()); 
        
        stepperY.setCurrentPosition(0);
        stepperY.moveTo(400);
        stepperY.setSpeed(200*MICROSTEPS);
        while(stepperY.targetPosition() != stepperY.currentPosition()){
          stepperY.runSpeed();
          Serial.println(stepperY.currentPosition());
        }
        Serial.println("YES");
        stepperY.moveTo(0);
        stepperY.setSpeed(-200*MICROSTEPS);
        while(stepperY.targetPosition() != stepperY.currentPosition()){
          stepperY.runSpeed();
          Serial.println(stepperY.currentPosition());
        }
        
        
        
        //calculate average velocity in steps
   
        //calculate new yfinal and new vyAI 
        
/*
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
        */
        /*
        make_Decision();
        Serial.println(vyAI);
          while(stepperY.currentPosition() != stepperY.targetPosition()){
          stepperY.runSpeed();
        }
        if((digitalRead(LEFT_STOP) == false) || (digitalRead(RIGHT_STOP) == false)){
          stepperY.stop();
          while(stepperY.currentPosition() != stepperY.targetPosition()){
            stepperY.runSpeed();
          }
        }
        */
}

void movehere(AccelStepper stepper, int curr, int moveTO, int SetSpeed)
{
        stepperY.setCurrentPosition(curr);
        stepperY.moveTo(moveTO);
        stepperY.setSpeed(200*MICROSTEPS);
        while(stepperY.targetPosition() != stepperY.currentPosition()){
          stepperY.runSpeed();
          Serial.println(stepperY.currentPosition());
        }
}

void follow(AccelStepper stepper) {
  int count = 0;
  
  stepper.setMaxSpeed(3500*MICROSTEPS);
  stepper.setAcceleration(3500*MICROSTEPS);

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
  stepper.setSpeed(-500*MICROSTEPS);
  while(stepper.currentPosition() != stepper.targetPosition()){
    stepper.runSpeed();//moves to center
  }

}

int motorCalibrate(AccelStepper stepper) {
  int count = 0;
  int absStep = 0;
  stepper.setMaxSpeed(3500*MICROSTEPS);
  stepper.setAcceleration(3500*MICROSTEPS);

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
  stepper.setSpeed(-500*MICROSTEPS);
  while(stepper.currentPosition() != stepper.targetPosition()){
    stepper.runSpeed();//moves to center
  }

  return stepper.currentPosition();
  

}

void translateToSteps(){
  x_new -= xOffset;
  y_new -= yOffset;
  y_new *= pxToMM*mmToSteps;// now in steps
  x_new *= pxToMM*mmToSteps;// now in steps
  
}

void averageVelocity(float x_new, float y_new) {
  //vxPuck -= vxMatrix[counter]; //Deletes oldest vx velocity in set
  //vyPuck -= vyMatrix[counter]; //Deletes oldest vyvelocity in set
  //vxMatrix[counter] = (x_new - xPuck) / (dataset); //DIVIDE BY TIME??? dataset variable allows us to avoid creating new variable to hold vxAverage
  //vyMatrix[counter] = (y_new - yPuck) / (dataset); //DIVIDE BY TIME??? dataset variable allows us to avoid creating new variable to hold vyAverage
  //vxPuck += vxMatrix[counter];
  //vyPuck += vxMatrix[counter];
  vxPuck = x_new-xPuck;
  vyPuck = y_new-yPuck;
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
  Serial.println(yfinal);
  vyAI = (yfinal-yAI)/gamma;
  Serial.println(vyAI);
  
}


void make_Decision() {

  stepperY.moveTo(yfinal);
  if(vyAI>MAX_VELOCITY){
    vyAI = MAX_VELOCITY;
  }
  stepperY.setSpeed(vyAI/1000);

  

}

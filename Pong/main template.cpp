//
//  main.cpp
//  ENPH454Template
//
//  Created by Griffin Staples on 2018-10-21.
//  Copyright © 2018 Clarity. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <vector>
using namespace std

////////////INITIALIZATION///////////
//import necessary pixy+steppermotor+ai libraries

/*
 
 DECLARE PINS
 
 //Puck Variables
 int xPuck; float vxPuck;
 int yPuck; float vyPuck;
 float rPuck;
 
 //Opponent Striker Variables
 int xStriker; float vxStriker;
 int yStriker; float vyStriker;
 float rPaddle;

 //AI Variables
 int xAI; float vxAI;
 int yAI; float vyAI;

 //Rink Boundaries
 int Left; int Right; int Top; int Bottom;
 int topNetY; int bottomNetY;
 
 //Stepper Motors
 
 const int stepPerRev = 360;
 
 
 
 
 //DEFINE USEFUL VARIABLES THAT NEED TO BE CALCULATED
 int rinkMiddleX;
 int yInt;
 int tInt;
 
 
 //OTHER DEFINTITIONS
 int counter = 0;
 int dataset = 5;
 int time;
 float vxMatrix[5] = 0;
 float vyMatrix[5] = 0;
 float gamma;
 float beta;
 float yfinal;
 int bounces;
 int yfinal;
 int posOrNeg;
 int loop_time;
 int start_time;
 int decision_length;
 
 
 
 
 
 
 
 ///////////VOID SETUP/////////////
 
 DECLARE PINMODES
 INITIALIZE STEPPERS
 
 INITIALIZE PIXY AND SET SETTINGS
 Get first pixy reading to initialize xPuck and yPuck (puck location)
 loop_time = millis();
 
 
 
 
 */



//initialize loop_time to be 20milliseconds

//////////VOID LOOP////////////
int main(){
    
    if(newPixyData){
        loop_time = millis()-loop_time;
        //GET X AND Y PIXY DATA
        //DE_FISHEYE X AND Y PIXY DATA
        //x_new; y_new;
        
        averageVelocity(x_new,y_new);
        predictY();
        
        if (decision_Status() == TRUE){
            if((abs(yfinal) > abs(original_Prediction)+error) || abs(yfinal) < abs(original_Prediction)-error){
                make_Decision();    //if decision off my certain amount, make new decision
            }
        }
        else{
            make_Decision();        //if no decision currently made, make decision
        }
    }
    
}



    
void averageVelocity(int x_new, int y_new, int loop_time){
    vxPuck -= vxMatrix[counter]; //Deletes oldest vx velocity in set
    vyPuck -= vyMatrix[counter]; //Deletes oldest vyvelocity in set
    vxMatrix[counter] = (x_new-xPuck)/(dataset*loop_time/1000); //DIVIDE BY TIME??? dataset variable allows us to avoid creating new variable to hold vxAverage
    vyMatrix[counter] =(y_new-yPuck)/(dataset*loop_time/1000); //DIVIDE BY TIME??? dataset variable allows us to avoid creating new variable to hold vyAverage
    vxPuck += vxMatrix[counter];
    vyPuck += vxMatrix[counter];
    xPuck = x_new;
    yPuck = y_new;
    
    counter++;
    if(counter>=dataset){
        counter=0;          //ensures running average of _  number of data points
    }
}


void predictY(){
    gamma = abs(xAI-xPuck)/xPuck);
    posOrNeg = abs(vyPuck)/(-vyPuck); //if posOrNeg is pos then vy is up if posOrNeg is neg then vy is down
    beta = (gamma*vyPuck); //the -posOrNeg*striker_rad/2 is an arbitrary correction factor
    bounces = (int) ((abs(beta)+posOrNeg*yPuck)/SCREEN_HEIGHT+(1-posOrNeg)/2);
    yfinal = abs((pow(-1,(bounces+1)%2))-posOrNeg)/2)*SCREEN_HEIGHT-posOrNeg*pow(-1,(bounces%2))*(abs(beta)-posOrNeg*yPuck+((posOrNeg-1)/2)*SCREEN_HEIGHT-(bounces-1)*SCREEN_HEIGHT);
}

bool decision_Status(int decision_length){
    if(millis()-start_time >= decision_length){
        return 1;
    }
    else{
        return 0;
    }
}

void make_Decision(){
    start_time = millis();
    //insert logic here;
}

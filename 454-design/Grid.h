//
// Created by Curtis Shewchuk on 2018-10-30.
//

#include <vector>
#include <iostream>
#include "Point.h"
using namespace std;
#pragma once

/*
 * Grid is a class that deals with and computes the calibration for the virtual grid on the table
 */
class Grid{

public:
    vector<double> coeffcients;
    static int virtualWidth;
    static int virtualHeight;
    Point topCenter;
    Point topLeft;
    Point topRight;
    Point bottomLeft;
    Point bottomRight;
    Point bottomCenter;
    Point center;
    Point centerRight;
    Point centerLeft;


    Grid(vector<double> inputData, double, double);

    static void initialize(double virtualWidth, double virtualHeight);
    static void setDefaultCalibration();
    static vector<double> computeCoefficents(vector< vector<double> >, vector<double>);



};


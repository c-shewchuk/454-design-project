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
    vector<float> topQuadraticCoeff;
    vector<float> bottomQuadraticCoeff;
    vector<float> centerHorizontalCoeff;
    vector<float> leftQuadraticCoeff;
    vector<float> rightQuadraticCoeff;
    vector<float> centerVerticalCoeff;
    int virtualWidth;
    int virtualHeight;
    Point topCenter;
    Point topLeft;
    Point topRight;
    Point bottomLeft;
    Point bottomRight;
    Point bottomCenter;
    Point center;
    Point centerRight;
    Point centerLeft;

    /*
     * Default constructor for a grid, requires the data of the curved surface and the virtualHeight and virtualWidth of the grid
     */
    Grid(int, int);

    /*
     * Initialize the virutalWidth and virtualHeight, and all the default pins of the
     */
    void initialize(int virtualWidth, int virtualHeight);

    /*
     * Sets default calibration of the table
     * TODO: STILL NEEDS CALIBRATION
     */
    void setDefaultCalibration();

    /*
     * Computes the quadratic coefficients required to map the curved surface as a flat one
     */
    vector<float> computeCoefficents(vector< vector<float> >, vector<float>);

    /*
     * Takes in point given by the Pixy and maps its coordinates to the virtual, flat grid
     */

    Point translatePoint(int,int);

private:
    vector< vector<float> > setPointVector(int, int, int);
    vector<float> addPointsToVector(int, int, int);


};


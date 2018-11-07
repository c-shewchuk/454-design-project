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
    Grid(vector< vector< double> >, double, double);

    /*
     * Initialize the virutalWidth and virtualHeight, and all the default pins of the
     */
    void initialize(double virtualWidth, double virtualHeight);

    /*
     * Sets default calibration of the table
     * TODO: NEEDS DATA TO THE CPP CALLS
     */
    void setDefaultCalibration();

    /*
     * Computes the quadratic coefficients required to map the curved surface as a flat one
     */
    vector<double> computeCoefficents(vector< vector<double> >, vector<double>);



};


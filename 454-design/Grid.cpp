//
// Created by Curtis Shewchuk on 2018-10-30.
//

#include "Grid.h"
#include <iostream>
#include <vector>

using namespace std;



Grid::Grid(float virtualHeight, float virtualWidth){
    this->initialize(virtualWidth, virtualHeight);
}

void Grid::initialize(float virtualWidth, float virtualHeight) {
    Grid::virtualHeight = virtualHeight;
    Grid::virtualWidth = virtualWidth;

    setDefaultCalibration();
}

/*
 * This needs to be ACTUALLY Calibrated still, but for now, they're all at the origin...
 * I will input the default values they used to see what happens when we use our camera
 */
void Grid::setDefaultCalibration(){
    /*
     * Default Points
     */
    this->bottomCenter = Point(155,190);
    this->bottomLeft = Point(12,170);
    this->bottomRight = Point(293,82);
    this->center = Point(156,100);
    this->topCenter = Point(160,12);
    this->centerLeft = Point(9,96);
    this->centerRight = Point(303,107);
    this->topLeft = Point(17,20);
    this->topRight = Point(299,30);

    /*
     * Initialize the coefficients
     */

    this->bottomQuadraticCoeff = addPointsToVector(this->bottomQuadraticCoeff, this->bottomLeft.yValue, this->bottomCenter.yValue, this->bottomRight.yValue);
    this->topQuadraticCoeff = addPointsToVector(this->topQuadraticCoeff, this->topLeft.yValue, this->topCenter.yValue, this->topRight.yValue);
    this->centerHorizontalCoeff = addPointsToVector(this->centerHorizontalCoeff, this->centerLeft.yValue, this->center.yValue, this->centerRight.yValue);
    this->leftQuadraticCoeff = addPointsToVector(this->leftQuadraticCoeff, this->topLeft.xValue, this->centerLeft.xValue, this->bottomLeft.xValue);
    this->rightQuadraticCoeff = addPointsToVector(this->rightQuadraticCoeff, this->topRight.xValue, this->centerRight.xValue, this->bottomRight.xValue);
    this->centerVerticalCoeff = addPointsToVector(this->centerVerticalCoeff, this->topCenter.xValue, this->center.xValue, this->bottomCenter.xValue);


    /*
     * Setup 2D vector floats to pass into calculation
     */

    vector< vector<float> > topQuad2D = setPointVector(this->topLeft.xValue,this->topCenter.xValue, this->topRight.xValue);
    vector< vector<float> > bottomQuad2D = setPointVector(this->bottomLeft.xValue, this->bottomCenter.xValue, this->bottomRight.xValue);
    vector< vector<float> > centerHorizontalQuad2D = setPointVector(this->centerLeft.xValue, this->center.xValue, this->centerRight.xValue);
    vector< vector<float> > leftQuad2D = setPointVector(this->topLeft.yValue, this->centerLeft.yValue, this->bottomLeft.yValue);
    vector< vector<float> > rightQuad2D = setPointVector(this->topRight.yValue, this->centerRight.yValue, this->bottomRight.yValue);
    vector< vector<float> > centerVerticalQuad2D = setPointVector(this->topCenter.yValue, this->center.yValue, this->bottomCenter.yValue);

    /*
     * Calculate the coefficients for our grid
     */

    this->bottomQuadraticCoeff = computeCoefficents(bottomQuad2D,this->bottomQuadraticCoeff);
    this->topQuadraticCoeff = computeCoefficents(topQuad2D, this->topQuadraticCoeff);
    this->centerHorizontalCoeff = computeCoefficents(centerHorizontalQuad2D, this->centerHorizontalCoeff);
    this->leftQuadraticCoeff = computeCoefficents(leftQuad2D, this->leftQuadraticCoeff);
    this->rightQuadraticCoeff = computeCoefficents(rightQuad2D, this->rightQuadraticCoeff);
    this->centerVerticalCoeff = computeCoefficents(centerVerticalQuad2D, this->centerVerticalCoeff);

}
vector<float> Grid::computeCoefficents(vector< vector<float> > data, vector<float> coefficients){
    int i, j, k, k1, N;
    N = coefficients.size();

    for(k = 0; k < N; k++){
        k1 = k + 1;
        for (i = k; i < N; i++){
            if(data[i][k] != 0){
                for(j = k1; j < N; j++){
                    data[i][j] /= data[i][k];
                }
                coefficients[i] /= data[i][k];
            }
        }
        for(i = k1; i < N; i++){
            if(data[i][k] != 0){
                for(j = k1; j < N; j++){
                    data[i][j] -= data[k][j];
                }
                coefficients[i] -= coefficients[k];
            }
        }
    }
    for(i = N-2; i >= 0; i--){
        for(j = N-1; j >= 0; j--){
            coefficients[i] -= data[i][j] * coefficients[j];
        }
    }

    return coefficients;

}

vector< vector<float> > Grid::setPointVector(int left, int center, int right){
    vector< vector<float> > points(3, vector<float>(2));
    points.at(0).at(0) = left*left; // square the top left value
    points.at(0).at(1) = left;
    points.at(1).at(0) = center*center;
    points.at(1).at(1) = center;
    points.at(2).at(0) = right*right;
    points.at(2).at(1) = right;

    return points;
}

/*
 * Quickly add the values need to the point vectors used to calculate the coefficients. Function because it happens A LOT.
 */
vector<float> Grid::addPointsToVector(vector<float> input, int left, int center, int right) {
    input.resize(3);
    input[0] = left;
    input[1] = center;
    input[2] = right;
    return input;
}

/*
 * Translates the pixy point, y values are vertical, x are horizontal
 *
 * THIS MAY POSSIBLY NEED A COORDINATE FLIP BUT THATS OKAY
 */
Point Grid::translatePoint(int xvalue, int yvalue) {
    Point pixyPoint = Point(xvalue,yvalue);
    float centerY = centerHorizontalCoeff[0]*xvalue*xvalue + centerHorizontalCoeff[1] * xvalue + centerHorizontalCoeff[2];
    float centerX = centerVerticalCoeff[0]*yvalue*yvalue + centerHorizontalCoeff[1] * yvalue + centerVerticalCoeff[2];

    if (yvalue < centerY){
        float topY = topQuadraticCoeff[0]* xvalue*xvalue +topQuadraticCoeff[1]*xvalue + topQuadraticCoeff[2];
        float ratioY = (yvalue-topY) / (centerY - topY);
        pixyPoint.yValue = (virtualHeight * ratioY )/ 2;
    }
    else{
        float botY = bottomQuadraticCoeff[0] * xvalue * xvalue + bottomQuadraticCoeff[1] * xvalue + bottomQuadraticCoeff[2];
        float ratioY = (botY - yvalue) / (botY - centerY);
        pixyPoint.yValue = virtualHeight - (virtualHeight * ratioY )/ 2;
    }

    if(xvalue < centerX){
        float leftX = leftQuadraticCoeff[0] * yvalue * yvalue + leftQuadraticCoeff[1] * yvalue + leftQuadraticCoeff[2];
        float ratioX = (xvalue - leftX) /(centerX - leftX);
        pixyPoint.xValue = (virtualWidth *ratioX) / 2;
    }
    else{
        float rightX = rightQuadraticCoeff[0] * yvalue * yvalue + leftQuadraticCoeff[1] * yvalue + leftQuadraticCoeff[2];
        float ratioX = (rightX - xvalue) / (rightX - centerX);
        pixyPoint.xValue = virtualWidth - (virtualWidth *ratioX) / 2;
    }

    return pixyPoint;

}






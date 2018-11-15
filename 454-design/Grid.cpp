//
// Created by Curtis Shewchuk on 2018-10-30.
//

#include "Grid.h"
#include <iostream>
#include <vector>

using namespace std;



Grid::Grid(int virtualHeight, int virtualWidth){
    this->bottomCenter = Point(161,81);
    this->bottomLeft = Point(24,164);
    this->bottomRight = Point(164,184);
    this->center = Point(164,105);
    this->topCenter = Point(169,29);
    this->centerLeft = Point(20,104);
    this->centerRight = Point(312,102);
    this->topLeft = Point(21,40);
    this->topRight = Point(308,37);
    this->initialize(virtualWidth, virtualHeight);
}

void Grid::initialize(int virtualWidth, int virtualHeight) {
    this->virtualHeight = virtualHeight;
    this->virtualWidth = virtualWidth;

    setDefaultCalibration();
}

/*
 * This needs to be ACTUALLY Calibrated still, but for now, they're all at the origin...
 * I will input the default values they used to see what happens when we use our camera
 */
void Grid::setDefaultCalibration(){

    /*
     * Initialize the coefficients
     */

    vector<float> bottomQDCoeff = addPointsToVector(this->bottomLeft.yValue, this->bottomCenter.yValue, this->bottomRight.yValue);
    vector<float> topQDCoeff = addPointsToVector(this->topLeft.yValue, this->topCenter.yValue, this->topRight.yValue);
    vector<float> centerQDHorizontalCoeff = addPointsToVector(this->centerLeft.yValue, this->center.yValue, this->centerRight.yValue);
    vector<float> leftQDCoeff = addPointsToVector(this->topLeft.xValue, this->centerLeft.xValue, this->bottomLeft.xValue);
    vector<float>rightQDCoeff = addPointsToVector(this->topRight.xValue, this->centerRight.xValue, this->bottomRight.xValue);
    vector<float> centerQDVerticalCoeff = addPointsToVector(this->topCenter.xValue, this->center.xValue, this->bottomCenter.xValue);


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

    this->bottomQuadraticCoeff = computeCoefficents(bottomQuad2D,bottomQDCoeff);
    this->topQuadraticCoeff = computeCoefficents(topQuad2D, topQDCoeff);
    this->centerHorizontalCoeff = computeCoefficents(centerHorizontalQuad2D, centerQDHorizontalCoeff);
    this->leftQuadraticCoeff = computeCoefficents(leftQuad2D, leftQDCoeff);
    this->rightQuadraticCoeff = computeCoefficents(rightQuad2D, rightQDCoeff);
    this->centerVerticalCoeff = computeCoefficents(centerVerticalQuad2D, centerQDVerticalCoeff);

}
vector<float> Grid::computeCoefficents(vector< vector<float> > data, vector<float> coefficients){
    int i = 0;
    int j = 0;
    int k = 0;
    int k1 = 0;
    int N = 0;
    N = static_cast<int>(coefficients.size());

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
        for(j = N-1; j >= (i+1); j--){
            coefficients[i] -= (data[i][j] * coefficients[j]);
        }
    }

    return coefficients;

}

vector< vector<float> > Grid::setPointVector(int left, int center, int right){
    vector< vector<float> > points(3, vector<float>(2));
    points[0][0] = left*left;
    points[0][1] = left;
    points[1][0] = center*center;
    points[1][1] = center;
    points[2][0] = right*right;
    points[2][1] = right;

    return points;
}

/*
 * Quickly add the values need to the point vectors used to calculate the coefficients. Function because it happens A LOT.
 */
vector<float> Grid::addPointsToVector(int left, int center, int right) {
    vector<float> output(3);
    output[0] = left;
    output[1] = center;
    output[2] = right;
    return output;
}

/*
 * Translates the pixy point, y values are vertical, x are horizontal
 *
 * THIS MAY POSSIBLY NEED A COORDINATE FLIP BUT THATS OKAY
 */
Point Grid::translatePoint(int xvalue, int yvalue) {
    Point pixyPoint = Point(xvalue,yvalue);
    float centerY = (centerHorizontalCoeff[0]*xvalue*xvalue) + (centerHorizontalCoeff[1] * xvalue) + centerHorizontalCoeff[2];
    float centerX = (centerVerticalCoeff[0]*yvalue*yvalue) + (centerVerticalCoeff[1] * yvalue) + centerVerticalCoeff[2];

    if (yvalue < centerY){
        float topY = topQuadraticCoeff[0]* xvalue*xvalue +topQuadraticCoeff[1]*xvalue + topQuadraticCoeff[2];
        float ratioY = (yvalue-topY) / (centerY - topY);
        pixyPoint.yValue = static_cast<int>(virtualHeight / 2 * ratioY);
    }
    else{
        float botY = (bottomQuadraticCoeff[0] * xvalue * xvalue) + (bottomQuadraticCoeff[1] * xvalue) + bottomQuadraticCoeff[2];
        float ratioY = (botY - yvalue) / (botY - centerY);
        pixyPoint.yValue = static_cast<int>(virtualHeight - (virtualHeight / 2 * ratioY));
    }

    if(xvalue < centerX){
        float leftX = (leftQuadraticCoeff[0] * yvalue * yvalue) + (leftQuadraticCoeff[1] * yvalue) + leftQuadraticCoeff[2];
        float ratioX = (xvalue - leftX) /(centerX - leftX);
        pixyPoint.xValue = static_cast<int>(virtualWidth / 2 * ratioX);
    }
    else{
        float rightX = (rightQuadraticCoeff[0] * yvalue * yvalue) + (leftQuadraticCoeff[1] * yvalue) + leftQuadraticCoeff[2];
        float ratioX = (rightX - xvalue) / (rightX - centerX);
        pixyPoint.xValue = static_cast<int>(virtualWidth - (virtualWidth / 2 * ratioX));
    }

    return pixyPoint;

}






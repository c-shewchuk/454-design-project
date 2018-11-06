//
// Created by Curtis Shewchuk on 2018-10-30.
//

#include "Grid.h"
#include <iostream>
#include <vector>

using namespace std;



Grid::Grid(vector<double> inputData, double virtualHeight, double virtualWidth){
    this->initialize(virtualWidth, virtualHeight);
    this->computeCoefficents()
}

void Grid::initialize(double virtualWidth, double virtualHeight){
    Grid::virtualHeight = virtualHeight;
    Grid::virtualWidth = virtualWidth;

    setDefaultCalibration();
}
void Grid::setDefaultCalibration(){
    this->bottomCenter = Point();
    this->bottomLeft = Point();
    this->bottomRight = Point();
    this->center = Point();
    this->topCenter = Point();
    this->centerLeft = Point();
    this->centerRight = Point();
    this->topLeft = Point();
    this->topRight = Point();
}
vector<double> Grid::computeCoefficents(vector< vector<double> > , vector<double>){

}




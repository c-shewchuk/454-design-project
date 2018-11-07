//
// Created by Curtis Shewchuk on 2018-10-30.
//

#include "Grid.h"
#include <iostream>
#include <vector>

using namespace std;



Grid::Grid(vector< vector <double> > inputData, double virtualHeight, double virtualWidth){
    this->initialize(virtualWidth, virtualHeight);
    this->coeffcients = this->computeCoefficents(inputData, this->coeffcients);
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
vector<double> Grid::computeCoefficents(vector< vector<double> > data, vector<double> coefficients){
    int i, j, k, k1, N;
    N = coefficients.size();

    for(k = 0; k < N; k++){
        k1 = k++; // k + 1
        for (i = k; i < N; i++){
            if(data.at(i).at(k) != 0){
                for(j = k1; j < N; j++){
                    data.at(i).at(j) /= data.at(i).at(k);
                }
                coefficients[i] /= data.at(i).at(k);
            }
        }
        for(i = k1; i < N; i++){
            if(data.at(i).at(k) != 0){
                for(j = k1; j < N; j++){
                    data.at(i).at(j) -= data.at(k).at(j);
                }
                coefficients.at(i) -= coefficients.at(k);
            }
        }
    }
    for(i = N-2; i >= 0; i--){
        for(j = N-1; j >= 0; j--){
            coefficients.at(i) -= data.at(i).at(j) * coefficients.at(j);
        }
    }

    return coefficients;

}




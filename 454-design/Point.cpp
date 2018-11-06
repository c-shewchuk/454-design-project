//
// Created by Curtis Shewchuk on 2018-11-01.
//

#include "Point.h"

Point::Point(int xVal, int yVal): xValue(xVal), yValue(yVal){
    if((xVal || yVal) <= 0){
        throw logic_error("Point values must be greater than zero");
    }
}

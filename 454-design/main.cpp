#include <iostream>
#include "Grid.h"
#include "Point.h"

using namespace std;

/*
 * This will be the part of the program that actually boots on the boot of the system
 */
int main() {

    // Init the grid
    Grid grid(1920,1080);

    cout << "It worked!!" << endl;
    cout << grid.topRight.xValue << endl;
    int size = grid.bottomQuadraticCoeff.size();
    cout << size << endl;
    for (int i = 0; i < size; i++){
        cout << grid.bottomQuadraticCoeff.at(i) << endl;

    }

    Point test = grid.translatePoint(40,40);

    cout << test.xValue << endl;
    cout << test.yValue << endl;
    return 0;

}
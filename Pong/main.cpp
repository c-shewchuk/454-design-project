#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Puck.h"

int main() {
    double x;
    double y;
    double vx;
    double vy;

    Puck puck1;
    while (true) {
        puck1.slide();
        puck1.edges();

    }
    return 0;
}

#ifndef ROUTE_GENERATOR_H
#define ROUTE_GENERATOR_H

#include <iostream>
#include <iomanip>
#include <cmath>

struct Coordinates {
    double latitude;
    double longitude;
};

Coordinates interpolateCoordinates(const Coordinates& start, const Coordinates& end, double t);

void generateRoute(const Coordinates& startPoint, const Coordinates& viaPoint1, const Coordinates& viaPoint2,
                   const Coordinates& endPoint, int numPoints);

#endif // ROUTE_GENERATOR_H

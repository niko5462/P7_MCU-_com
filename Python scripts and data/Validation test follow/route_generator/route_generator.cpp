#include "route_generator.h"

Coordinates interpolateCoordinates(const Coordinates& start, const Coordinates& end, double t) {
    Coordinates result;
    result.latitude = start.latitude + t * (end.latitude - start.latitude);
    result.longitude = start.longitude + t * (end.longitude - start.longitude);
    return result;
}

void generateRoute(const Coordinates& startPoint, const Coordinates& viaPoint1, const Coordinates& viaPoint2,
                   const Coordinates& endPoint, int numPoints) {
    std::cout << std::fixed << std::setprecision(0);

    for (int i = 0; i < numPoints; ++i) {
        double t = static_cast<double>(i) / (numPoints - 1);
        Coordinates currentPoint;

        if (t < 0.33) {
            currentPoint = interpolateCoordinates(startPoint, viaPoint1, t / 0.33);
        } else if (t < 0.66) {
            currentPoint = interpolateCoordinates(viaPoint1, viaPoint2, (t - 0.33) / 0.33);
        } else {
            currentPoint = interpolateCoordinates(viaPoint2, endPoint, (t - 0.66) / 0.34);
        }

        //std::cout << currentPoint.latitude << "," << currentPoint.longitude << "\n";
        //std::cout << currentPoint.longitude << "\n";
        std::cout << "coordinate" << i + 1 << ".lat = " << currentPoint.latitude <<  ";\n";
        std::cout << "coordinate" << i + 1 << ".lng = " << currentPoint.longitude << ";\n";
    }
}

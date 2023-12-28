#include "route_generator/route_generator.h"
#include "route_generator/CoordinateStorage.h"
#include "route_generator/CoordinateParser.h"

int main() {
    const Coordinates startPoint = {570138952, 99874556};
    const Coordinates viaPoint1 = {570161515, 99854032};
    const Coordinates viaPoint2 = {570179819, 99878129};
    const Coordinates endPoint = {570178176, 99924727};

    const int numPoints = 50;

    generateRoute(startPoint, viaPoint1, viaPoint2, endPoint, numPoints);

    return 0;
}

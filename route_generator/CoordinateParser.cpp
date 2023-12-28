#include "CoordinateParser.h"
#include <sstream>

CoordinateParser::CoordinateParser(const char* coordinateCharArray) {
    parseCoordinateString(coordinateCharArray);
}

double CoordinateParser::getLatitude() const {
    return latitude;
}

double CoordinateParser::getLongitude() const {
    return longitude;
}

void CoordinateParser::parseCoordinateString(const char* coordinateCharArray) {
    std::istringstream iss(coordinateCharArray);
    char delimiter;
    iss >> latitude >> delimiter >> longitude;
}

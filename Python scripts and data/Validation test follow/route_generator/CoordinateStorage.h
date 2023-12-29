#ifndef COORDINATE_STORAGE_H
#define COORDINATE_STORAGE_H

#include <vector>
#include <string>
#include "CoordinateParser.h"

class CoordinateStorage {
public:
    void addCoordinate(const char* coordinateString);
    void printCoordinates() const;

private:
    std::vector<CoordinateParser> coordinates;
};

#endif // COORDINATE_STORAGE_H

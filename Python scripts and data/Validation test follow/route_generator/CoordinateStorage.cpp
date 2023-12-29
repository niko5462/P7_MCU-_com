
#include <iostream>
#include "CoordinateStorage.h"

void CoordinateStorage::addCoordinate(const char* coordinateCharArray) {
    // Create a temporary CoordinateParser object from the char array
    CoordinateParser tempParser(coordinateCharArray);
    
    // Print the parsed coordinates
    std::cout << "Parsed Coordinate - Latitude: " << tempParser.getLatitude() 
              << "Longitude: " << tempParser.getLongitude() << "\n";
    
    // Add the temporary object to the vector
    coordinates.emplace_back(std::move(tempParser));
}

void CoordinateStorage::printCoordinates() const {
    for (const auto& coord : coordinates) {
        std::cout << "Latitude: " << coord.getLatitude() << ": Longitude: " << coord.getLongitude() << "\n";
    }
}

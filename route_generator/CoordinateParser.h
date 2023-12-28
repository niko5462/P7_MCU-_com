#ifndef COORDINATE_PARSER_H
#define COORDINATE_PARSER_H

#include <cstring> // Include for const char*

class CoordinateParser {
public:

    CoordinateParser(const char* coordinateCharArray);

    double getLatitude() const;
    double getLongitude() const;

private:
    double latitude;
    double longitude;

    void parseCoordinateString(const char* coordinateCharArray);
};

#endif // COORDINATE_PARSER_H

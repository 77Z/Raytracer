#ifndef RAYTRACER_UTIL_HPP
#define RAYTRACER_UTIL_HPP

#include <limits>

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Methods

inline double degToRad(double deg) {
	return deg * pi / 180.0;
}


#endif /* RAYTRACER_UTIL_HPP */
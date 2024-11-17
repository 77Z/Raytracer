#ifndef RAYTRACER_UTIL_HPP
#define RAYTRACER_UTIL_HPP

#include <limits>
#include <random>

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Methods

inline double degToRad(double deg) {
	return deg * pi / 180.0;
}

inline double randomDouble() {
	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
	static std::mt19937 generator;
	return distribution(generator);
}

inline double randomDouble(double min, double max) {
	return min + (max-min)*randomDouble();
}

#endif /* RAYTRACER_UTIL_HPP */
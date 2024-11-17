#ifndef RAYTRACER_COLOR_HPP
#define RAYTRACER_COLOR_HPP

#include "Interval.hpp"
#include "vec3.hpp"

#include <cmath>
#include <iostream>
#include <ostream>

using color = vec3;

inline double linearToGamma(double linearComponent) {
	if (linearComponent > 0)
		return sqrt(linearComponent);

	return 0;
}

inline void writeColor(std::ostream& out, const color& pixelColor) {
	auto r = pixelColor.x();
	auto g = pixelColor.y();
	auto b = pixelColor.z();

	r = linearToGamma(r);
	g = linearToGamma(g);
	b = linearToGamma(b);

	// Translate 0-1 range to 0-255
	static const Interval intensity(0.000, 0.999);
	int rbyte = int(256 * intensity.clamp(r));
	int gbyte = int(256 * intensity.clamp(g));
	int bbyte = int(256 * intensity.clamp(b));

	out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif /* RAYTRACER_COLOR_HPP */
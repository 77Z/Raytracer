#ifndef RAYTRACER_COLOR_HPP
#define RAYTRACER_COLOR_HPP

#include "vec3.hpp"

#include <iostream>
#include <ostream>

using color = vec3;

inline void writeColor(std::ostream& out, const color& pixelColor) {
	auto r = pixelColor.x();
	auto g = pixelColor.y();
	auto b = pixelColor.z();

	// Translate 0-1 range to 0-255
	int rbyte = int(255.999 * r);
	int gbyte = int(255.999 * g);
	int bbyte = int(255.999 * b);

	out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif /* RAYTRACER_COLOR_HPP */
#ifndef RAYTRACER_RAY_HPP
#define RAYTRACER_RAY_HPP

#include "vec3.hpp"

class Ray {
public:
	Ray() {}

	Ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

	const point3& origin() const { return orig; }
	const point3& direction() const { return dir; }

	point3 at(double t) const {
		return orig + t*dir;
	}

private:
	point3 orig;
	vec3 dir;
};

#endif /* RAYTRACER_RAY_HPP */
#ifndef RAYTRACER_CAMERA_HPP
#define RAYTRACER_CAMERA_HPP

#include "Hittable.hpp"
#include "color.hpp"
#include "ray.hpp"

class Camera {
public:

	void render(const Hittable& world) {

	}

private:

	void initialize() {}

	color rayColor(const Ray& r, const Hittable& world) const {
		hitRecord rec;
		if (world.hit(r, Interval(0, infinity), rec)) {
			return 0.5 * (rec.normal + color(1, 1, 1));
		}

		vec3 unitDirection = unitVector(r.direction());
		auto a = 0.5 * (unitDirection.y() + 1.0);
		return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
	}
};

#endif /* RAYTRACER_CAMERA_HPP */
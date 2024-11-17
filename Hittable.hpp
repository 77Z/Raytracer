#ifndef RAYTRACER_HITTABLE_HPP
#define RAYTRACER_HITTABLE_HPP

#include "Interval.hpp"
#include "ray.hpp"
#include "vec3.hpp"
#include <memory>

class Material;

class hitRecord {
public:
	point3 p;
	vec3 normal;
	std::shared_ptr<Material> mat;
	double t;
	bool frontFace;

	void setFaceNormal(const Ray& r, const vec3& outwardNormal) {
		// The parameter `outwardNormal` is assumed to have unit length

		frontFace = dot(r.direction(), outwardNormal) < 0;
		normal = frontFace ? outwardNormal : -outwardNormal;
	}
};

class Hittable {
public:
	virtual ~Hittable() = default;

	virtual bool hit(const Ray& r, Interval ray_t, hitRecord& rec) const = 0;
};

#endif /* RAYTRACER_HITTABLE_HPP */
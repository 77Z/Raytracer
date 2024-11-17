#ifndef RAYTRACER_SPHERE_HPP
#define RAYTRACER_SPHERE_HPP

#include "Hittable.hpp"
#include "Interval.hpp"
#include "Material.hpp"
#include "ray.hpp"
#include "vec3.hpp"
#include <cmath>
#include <memory>

class Sphere : public Hittable {
public:
	Sphere(const point3& center, double radius, std::shared_ptr<Material> mat)
		: center(center)
		, radius(fmax(0, radius))
		, mat(mat) { }

	bool hit(const Ray& r, Interval ray_t, hitRecord& rec) const override {
		vec3 oc = center - r.origin();
		auto a = r.direction().length_squared();
		auto h = dot(r.direction(), oc);
		auto c = oc.length_squared() - radius*radius;
		auto discriminant = h*h - a*c; // Quad formula

		if (discriminant < 0)
			return false;
		
		auto sqrtd = sqrt(discriminant);

		// Find the nearest root that lies in the acceptable range
		auto root = (h - sqrtd) / a;
		if (!ray_t.surrounds(root)) {
			root = (h + sqrtd) / a;
			if (!ray_t.surrounds(root))
				return false;
		}

		rec.t = root;
		rec.p = r.at(rec.t);
		vec3 outwardNormal = (rec.p - center) / radius;
		rec.setFaceNormal(r, outwardNormal);
		rec.mat = mat;

		return true;
	}

private:
	point3 center;
	double radius;
	std::shared_ptr<Material> mat;
};

#endif /* RAYTRACER_SPHERE_HPP */
#ifndef RAYTRACER_MATERIAL_HPP
#define RAYTRACER_MATERIAL_HPP

#include "Hittable.hpp"
#include "color.hpp"
#include "ray.hpp"
#include "vec3.hpp"

class Material {
public:
	virtual ~Material() = default;

	virtual bool scatter(
		const Ray& r_in,
		const hitRecord& rec,
		color& attenuation,
		Ray& scattered
	) const {
		return false;
	}
};

class UniformDiffuse : public Material {
	UniformDiffuse(const color& albedo) : albedo(albedo) {}

	bool scatter(
		const Ray& r_in, const hitRecord& rec, color& attenuation, Ray& scattered
	) const override {
		auto scatterDirection = randomOnHemisphere(rec.normal);

		if (scatterDirection.nearZero())
			scatterDirection = rec.normal;

		scattered = Ray(rec.p, scatterDirection);
		attenuation = albedo;
		return true;
	}

private:
	color albedo;
};

class Lambertian : public Material {
public:
	Lambertian(const color& albedo) : albedo(albedo) {}

	bool scatter(
		const Ray& r_in, const hitRecord& rec, color& attenuation, Ray& scattered
	) const override {
		auto scatterDirection = rec.normal + randomUnitVector();

		// Catch degenerate scatter direction
		if (scatterDirection.nearZero())
			scatterDirection = rec.normal;

		scattered = Ray(rec.p, scatterDirection);
		attenuation = albedo;
		return true;
	}
private:
	color albedo;
};

class Metal : public Material {
public:
	Metal(const color& albedo, double fuzz)
	: albedo(albedo)
	, fuzz(fuzz < 1 ? fuzz : 1)
		{ }

	bool scatter(
		const Ray& r_in, const hitRecord& rec, color& attenuation, Ray& scattered
	) const override {
		vec3 reflected = reflect(r_in.direction(), rec.normal);
		reflected = unitVector(reflected) + (fuzz * randomUnitVector());
		scattered = Ray(rec.p, reflected);
		attenuation = albedo;

		return (dot(scattered.direction(), rec.normal) > 0);
	}

private:
	color albedo;
	double fuzz;
};

#endif /* RAYTRACER_MATERIAL_HPP */
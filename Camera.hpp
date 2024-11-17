#ifndef RAYTRACER_CAMERA_HPP
#define RAYTRACER_CAMERA_HPP

#include "Hittable.hpp"
#include "Util.hpp"
#include "color.hpp"
#include "ray.hpp"
#include "vec3.hpp"
#include "Material.hpp"

class Camera {
public:
	double	aspectRatio		= 1.0;	// Ex: 16.0 / 9.0
	int		imageWidth		= 100;
	int		samplesPerPixel	= 10;	// Random samples per pixel
	int		maxDepth		= 10;	// Maximum number of ray bounces

	void render(const Hittable& world, std::ostream &out) {
		initialize();

		out << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

		for (int j = 0; j < imageHeight; j++) {
			std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
			for (int i = 0; i < imageWidth; i++) {
				color pixelColor(0, 0, 0);
				for (int sample = 0; sample < samplesPerPixel; sample++) {
					Ray r = getRay(i, j);
					pixelColor += rayColor(r, maxDepth, world);
				}
				writeColor(out, pixelSamplesScale * pixelColor);
			}
		}

		std::clog << "\rDone.                     \n";
	}

private:
	int imageHeight;
	double pixelSamplesScale;
	point3 center;
	point3 pixel00_loc;
	vec3 pixelDelta_u;
	vec3 pixelDelta_v;

	void initialize() {
		// Calc image height
		imageHeight = int(imageWidth / aspectRatio);
		imageHeight = (imageHeight < 1) ? 1 : imageHeight;

		pixelSamplesScale = 1.0 / samplesPerPixel;

		center = point3(0, 0, 0);

		auto focalLength = 1.0;
		auto viewportHeight = 2.0;
		auto viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);

		// Calc vectors across the horizontal and down the vertical viewport edges
		auto viewport_u = vec3(viewportWidth, 0, 0);
		auto viewport_v = vec3(0, -viewportHeight, 0);

		// Calc the horizontal and vertical delta vectors from pixel to pixel
		pixelDelta_u = viewport_u / imageWidth;
		pixelDelta_v = viewport_v / imageHeight;

		// Calc the location of the upper left pixel
		auto viewportUpperLeft = center - vec3(0, 0, focalLength) - viewport_u / 2 - viewport_v / 2;
		pixel00_loc = viewportUpperLeft + 0.5 * (pixelDelta_u + pixelDelta_v);
	}

	Ray getRay(int i, int j) const {
		// Construct a camera ray originating from the origin and directed at a
		// randomly sampled point around the pixel location: i, j

		auto offset = sampleSquare();
		auto pixelSample = pixel00_loc
						 + ((i + offset.x()) * pixelDelta_u)
						 + ((j + offset.y()) * pixelDelta_v);
		auto rayOrigin = center;

		auto rayDirection = pixelSample - rayOrigin;

		return Ray(rayOrigin, rayDirection);
	}

	vec3 sampleSquare() const {
		// Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit
		// sqaure.
		return vec3(randomDouble() - 0.5, randomDouble() - 0.5, 0);
	}

	color rayColor(const Ray& r, int depth, const Hittable& world) const {
		if (depth <= 0)
			return color(0, 0, 0);

		hitRecord rec;
		if (world.hit(r, Interval(0.001, infinity), rec)) {
			Ray scattered;
			color attenuation;
			if (rec.mat->scatter(r, rec, attenuation, scattered))
				return attenuation * rayColor(scattered, depth-1, world);
			return color(0, 0, 0);
		}

		vec3 unitDirection = unitVector(r.direction());
		auto a = 0.5 * (unitDirection.y() + 1.0);
		return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
	}
};

#endif /* RAYTRACER_CAMERA_HPP */
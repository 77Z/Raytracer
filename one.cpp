#include "Hittable.hpp"
#include "HittableList.hpp"
#include "Interval.hpp"
#include "Sphere.hpp"
#include "Util.hpp"
#include "color.hpp"
#include "ray.hpp"
#include "vec3.hpp"
#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>

color rayColor(const Ray& r, const Hittable& world) {
	
}

int main() {
	std::ofstream outImage("image.ppm");

	auto aspectRatio = 16.0 / 9.0;
	int imageWidth = 1920;

	// Calc image height
	int imageHeight = int(imageWidth / aspectRatio);
	imageHeight = (imageHeight < 1) ? 1 : imageHeight;

	// World
	HittableList world;

	world.add(make_shared<Sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<Sphere>(point3(0.4, 0, -1), 0.5));
	world.add(make_shared<Sphere>(point3(0, -100.5, -1), 100));

	// Camera
	auto focalLength = 1.0;
	auto viewportHeight = 2.0;
	auto viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);
	auto cameraCenter = point3(0, 0, 0);

	// Calc vectors across the horizontal and down the vertical viewport edges
	auto viewport_u = vec3(viewportWidth, 0, 0);
	auto viewport_v = vec3(0, -viewportHeight, 0);

	// Calc the horizontal and vertical delta vectors from pixel to pixel
	auto pixelDelta_u = viewport_u / imageWidth;
	auto pixelDelta_v = viewport_v / imageHeight;

	// Calc the location of the upper left pixel
	auto viewportUpperLeft = cameraCenter - vec3(0, 0, focalLength) - viewport_u / 2 - viewport_v / 2;
	auto pixel00_loc = viewportUpperLeft + 0.5 * (pixelDelta_u + pixelDelta_v);



	// Render

	outImage << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

	for (int j = 0; j < imageHeight; j++) {
		std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
		for (int i = 0; i < imageWidth; i++) {
			auto pixelCenter = pixel00_loc + (i * pixelDelta_u) + (j * pixelDelta_v);
			auto rayDirection = pixelCenter - cameraCenter;
			Ray r(cameraCenter, rayDirection);

			color pixelColor = rayColor(r, world);

			writeColor(outImage, pixelColor);
		}
	}

	std::clog << "\rDone.                     \n";

	outImage.close();

	return 0;
}

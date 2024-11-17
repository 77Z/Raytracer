#include "Camera.hpp"
#include "HittableList.hpp"
#include "Material.hpp"
#include "Sphere.hpp"
#include "color.hpp"
#include "vec3.hpp"
#include <fstream>
#include <memory>

int main() {
	std::ofstream outImage("image.ppm");

	HittableList world;

	// world.add(make_shared<Sphere>(point3(0, 0, -1), 0.5));
	// world.add(make_shared<Sphere>(point3(0.4, 0, -1), 0.5));
	// world.add(make_shared<Sphere>(point3(0, -100.5, -1), 100));

	auto materialGround = make_shared<Lambertian>(color(0.8, 0.8, 0.0));
	auto materialCenter = make_shared<Lambertian>(color(0.1, 0.2, 0.5));
	auto materialLeft = make_shared<Metal>(color(0.8, 0.8, 0.8), 0.3);
	auto materialRight = make_shared<Metal>(color(0.8, 0.6, 0.2), 1.0);

	world.add(make_shared<Sphere>(point3( 0.0, -100.5, -1.0), 100.0, materialGround));
	world.add(make_shared<Sphere>(point3( 0.0,    0.0, -1.2),   0.5, materialCenter));
	world.add(make_shared<Sphere>(point3(-1.0,    0.0, -1.0),   0.5, materialLeft));
	world.add(make_shared<Sphere>(point3( 1.0,    0.0, -1.0),   0.5, materialRight));

	Camera cam;

	cam.aspectRatio = 16.0 / 9.0;
	cam.imageWidth = 1920;
	cam.samplesPerPixel = 100;
	cam.maxDepth = 50;

	cam.render(world, outImage);

	outImage.close();

	return 0;
}

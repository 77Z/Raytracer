#ifndef RAYTRACER_HITTABLE_LIST_HPP
#define RAYTRACER_HITTABLE_LIST_HPP

#include "Hittable.hpp"
#include "Interval.hpp"
#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

class HittableList : public Hittable {
public:
	std::vector<shared_ptr<Hittable>> objects;

	HittableList() {}
	HittableList(shared_ptr<Hittable> object) { add(object); }

	void clear() { objects.clear(); }

	void add(shared_ptr<Hittable> object) {
		objects.push_back(object);
	}

	bool hit(const Ray& r, Interval ray_t, hitRecord& rec) const override {
		hitRecord tempRec;
		bool hitAnything = false;
		auto closestSoFar = ray_t.max;

		for (const auto& object : objects) {
			if (object->hit(r, Interval(ray_t.min, closestSoFar), tempRec)) {
				hitAnything = true;
				closestSoFar = tempRec.t;
				rec = tempRec;
			}
		}

		return hitAnything;
	}
};

#endif /* RAYTRACER_HITTABLE_LIST_HPP */
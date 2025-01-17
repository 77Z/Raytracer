#ifndef RAYTRACER_VEC3_HPP
#define RAYTRACER_VEC3_HPP

#include "Util.hpp"
#include <cmath>
#include <iostream>
#include <ostream>

using std::sqrt;

class vec3 {
public:
	double e[3];

	vec3() : e{0, 0, 0} {}
	vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

	double x() const { return e[0]; }
	double y() const { return e[1]; }
	double z() const { return e[2]; }

	vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
	double operator[](int i) const { return e[i]; }
	double& operator[](int i) { return e[i]; }

	vec3& operator+=(const vec3& v) {
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}

	vec3& operator*=(double t) {
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	vec3& operator/=(double t) {
		// Clever operator and arithmatic trick
		return *this *= 1/t;
	}

	double length() const {
		return sqrt(length_squared());
	}

	double length_squared() const {
		return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
	}

	bool nearZero() const {
		// Returns true if the vector is close to zero in all directions
		auto s = 1e-8;
		return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
	}

	static vec3 random() {
		return vec3(randomDouble(), randomDouble(), randomDouble());
	}

	static vec3 random(double min, double max) {
		return vec3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
	}
};

// alias for vec3, useful for clarity
using point3 = vec3;

// Vector Util Methods
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}


inline vec3 operator-(const vec3& u, const vec3& v) {
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3& v) {
	return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3& v, double t) {
	return t * v;
}

inline vec3 operator/(const vec3& v, double t) {
	return (1 / t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
	return u.e[0] * v.e[0]
		 + u.e[1] * v.e[1]
		 + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
	return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
				u.e[2] * v.e[0] - u.e[0] * v.e[2],
				u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unitVector(const vec3& v) {
	return v / v.length();
}

inline vec3 randomInUnitSphere() {
	while (true) {
		auto p = vec3::random(-1, 1);
		if (p.length_squared() < 1)
			return p;
	}
}

inline vec3 randomUnitVector() {
	return unitVector(randomInUnitSphere());
}

inline vec3 randomOnHemisphere(const vec3& normal) {
	vec3 onUnitSphere = randomUnitVector();
	if (dot(onUnitSphere, normal) > 0.0) // In the same hemisphere as the normal
		return onUnitSphere;

	return -onUnitSphere;
}

inline vec3 reflect(const vec3& v, const vec3& n) {
	return v - 2*dot(v, n)*n;
}

#endif /* RAYTRACER_VEC3_HPP */
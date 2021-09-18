#include "Vec3.h"
std::istream& operator>>(std::istream& is, Vec3& t) {
	is >> t.v[0] >> t.v[1] >> t.v[2];
	return is;
}

std::ostream& operator<<(std::ostream& os, const Vec3& t) {
	os << t.v[0] << " " << t.v[1] << " " << t.v[2];
	return os;
}

void Vec3::makeUnitVector() {
	double k = 1.0 / sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	v[0] *= k;
	v[1] *= k;
	v[2] *= k;
}


double Vec3::dot(const Vec3 &v1, const Vec3 &v2) {
	return v1.v[0] * v2.v[0] + v1.v[1] * v2.v[1] + v1[2] * v2.v[2];
}

Vec3 Vec3::cross(const Vec3& v1, const Vec3& v2) {
	return Vec3((v1.v[1] * v2.v[2] - v1.v[2] * v2.v[1]),
		(-(v1.v[0] * v2.v[2] - v1.v[2] * v2.v[0])),
		(v1.v[0] * v2.v[1] - v1.v[1] * v2.v[0]));
}

inline Vec3& Vec3::operator+=(const Vec3 & v1) {
	v[0] += v1.v[0];
	v[1] += v1.v[1];
	v[2] += v1.v[2];
	return *this;
}

inline Vec3& Vec3::operator*=(const Vec3& v1) {
	v[0] *= v1.v[0];
	v[1] *= v1.v[1];
	v[2] *= v1.v[2];

	return *this;
}

inline Vec3& Vec3::operator/=(const Vec3& v1) {
	v[0] /= v1.v[0];
	v[1] /= v1.v[1];
	v[2] /= v1.v[2];

	return *this;
}

inline Vec3& Vec3::operator-=(const Vec3& v1) {
	v[0] -= v1.v[0];
	v[1] -= v1.v[1];
	v[2] -= v1.v[2];

	return *this;
}

inline Vec3& Vec3::operator*=(const double t) {
	v[0] *= t;
	v[1] *= t;
	v[2] *= t;

	return *this;
}

inline Vec3& Vec3::operator/=(const double t) {
	double k = 1.0 / t;
	v[0] *= k;
	v[1] *= k;
	v[2] *= k;

	return *this;
}

Vec3 Vec3::unitVector(Vec3 v1) {
	return v1 / v1.length();
}
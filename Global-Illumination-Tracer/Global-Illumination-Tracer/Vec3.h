#pragma once
#include <stdlib.h>
#include <iostream>

class Vec3
{
	public:
		double v[3];

		Vec3() { v[0] = 0, v[1] = 0, v[2] = 0; }
		Vec3(double v0, double v1, double v2) { v[0] = v0, v[1] = v1, v[2] = v2; }
		inline double x() const { return v[0]; }
		inline double y() const { return v[1]; }
		inline double z() const { return v[2]; }

		inline const Vec3& operator+() const { return *this; }
		inline Vec3 operator-() const { return Vec3(-v[0], -v[1], -v[2]); }
		inline double operator[](int i) const { return v[i]; }
		inline double& operator[](int i) { return v[i]; }

		Vec3& operator+=(const Vec3& v1);
		Vec3& operator-=(const Vec3& v1);
		Vec3& operator*=(const Vec3& v1);
		Vec3& operator/=(const Vec3& v1);
		Vec3& operator*=(const double t);
		Vec3& operator/=(const double t);


		inline double squaredLength() const {
			return (v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
		}
		inline double length() const {
			return sqrt(squaredLength());
		}

		//std::ostream& operator<<(std::ostream& os, const Vec3& t);
		//std::istream& operator>>(std::istream& is, Vec3& t);

		void makeUnitVector();
		double dot(const Vec3 &v1, const Vec3 &v2);
		Vec3 cross(const Vec3 &v1, const Vec3 &v2);
		Vec3 unitVector(Vec3 v1);

};

inline Vec3 operator-(const Vec3& v1, const Vec3& v2) {
	return Vec3(v1.v[0] - v2.v[0], v1.v[1] - v2.v[1], v1.v[2] - v2.v[2]);
}

inline Vec3 operator+(const Vec3& v1, const Vec3& v2) {
	return Vec3(v1.v[0] + v2.v[0], v1.v[1] + v2.v[1], v1.v[2] + v2.v[2]);
}


inline Vec3 operator*(const Vec3& v1, const Vec3& v2) {
	return Vec3(v1.v[0] * v2.v[0], v1.v[1] * v2.v[1], v1.v[2] * v2.v[2]);
}

inline Vec3 operator/(const Vec3& v1, const Vec3& v2) {
	return Vec3(v1.v[0] / v2.v[0], v1.v[1] / v2.v[1], v1.v[2] / v2.v[2]);
}

inline Vec3 operator*(double t, const Vec3& v) {
	return Vec3(t * v.v[0], t * v.v[1], t * v.v[2]);
}

inline Vec3 operator/(const Vec3& v, double t) {
	return Vec3(v.v[0] / t, v.v[1] / t, v.v[2] / t);
}

inline Vec3 operator*(const Vec3& v, double t) {
	return Vec3(t * v.v[0], t * v.v[1], t * v.v[2]);
}


#ifndef BITSMITHERY_MATH_MATH_HPP
	#define BITSMITHERY_MATH_MATH_HPP

	#include <cmath>
    #include <algorithm>

	namespace bitsmithery
	{
		namespace math
		{
			auto const nan = NAN;
			using std::isnan;

			auto const inf = INFINITY;
			using std::isinf;

			long double const pi = 3.14159265358979323846264338327950288419716939937510L;

			using std::sin;
			using std::cos;
			using std::tan;

			using std::asin;
			using std::acos;
			using std::atan;

			template <typename T>
			T sqr(T x);
			using std::sqrt;

			using std::exp;
			using std::log;

			using std::min;
			using std::max;
			template <typename T>
			T clamp(T a, T x, T b);

			using std::abs;
			using std::round;
			using std::floor;
			using std::ceil;
		}
	}

	#include "math.inl"

#endif

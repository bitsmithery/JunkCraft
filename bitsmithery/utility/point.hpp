#ifndef APP_UTIL_POINT_HPP
	#define APP_UTIL_POINT_HPP

	#include <type_traits>

	#include "../math/vector.hpp"

	namespace bitsmithery
	{
		namespace utility
		{
			template <typename T>
			class point
			{
				public:
					T x; T y;

					point() = default;
					point(point const& that) = default;
					point& operator=(point const& that) = default;
					point(point&& that) = default;
					point& operator=(point&& that) = default;
					~point() = default;

					template <typename X, typename Y>
					point(X const& x, Y const& y);

					template <typename U>
					point(point<U> const& that);

					template <typename U>
					point& operator=(point<U> const& that);

					template <typename U>
					explicit point(math::vector<U> const& that);

					template <typename U>
					explicit operator math::vector<U>() const;
			};

			typedef point<float> pointf;
			typedef point<double> pointd;
			typedef point<int> pointi;
			typedef point<unsigned> pointu;

			template <typename L, typename R>
			math::vector<typename std::common_type<L, R>::type> operator-(point<L> const& l, point<R> const& r);

			template <typename L, typename R>
			point<typename std::common_type<L, R>::type> operator+(point<L> const& l, math::vector<R> const& r);
			template <typename L, typename R>
			point<L>& operator+=(point<L>& l, math::vector<R> const& r);

			template <typename L, typename R>
			point<typename std::common_type<L, R>::type> operator-(point<L> const& l, math::vector<R> const& r);
			template <typename L, typename R>
			point<L>& operator-=(point<L>& l, math::vector<R> const& r);

			template <typename L, typename R>
			bool operator==(point<L> const& l, point<R> const& r);
			template <typename L, typename R>
			bool operator!=(point<L> const& l, point<R> const& r);
		}
	}

	#include "point.inl"

#endif

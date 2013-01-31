#ifndef BITSMITHERY_MATH_VECTOR_HPP
    #define BITSMITHERY_MATH_VECTOR_HPP

	#include <type_traits>

	#include "math.hpp"

	namespace bitsmithery
	{
		namespace math
		{
			template <typename T>
			class vector
			{
				public:
					T x; T y;

					vector() = default;
					vector(vector const& that) = default;
					vector& operator=(vector const& that) = default;
					vector(vector&& that) = default;
					vector& operator=(vector&& that) = default;
					~vector() = default;

					template <typename X, typename Y>
					vector(X const& x, Y const& y);

					template <typename U>
					vector(vector<U> const& that);

					template <typename U>
					vector& operator=(vector<U> const& that);
			};

			typedef vector<float> vectorf;
			typedef vector<double> vectord;
			typedef vector<int> vectori;
			typedef vector<unsigned> vectoru;

			template <typename T>
			vector<T> operator-(vector<T> const& v);

			template <typename L, typename R>
			vector<typename std::common_type<L, R>::type> operator+(vector<L> const& l, vector<R> const& r);
			template <typename L, typename R>
			vector<L>& operator+=(vector<L>& l, vector<R> const& r);

			template <typename L, typename R>
			vector<typename std::common_type<L, R>::type> operator-(vector<L> const& l, vector<R> const& r);
			template <typename L, typename R>
			vector<L>& operator-=(vector<L>& l, vector<R> const& r);

			template <typename L, typename R>
			vector<typename std::common_type<L, R>::type> operator*(vector<L> const& l, R const& r);
			template <typename L, typename R>
			vector<L>& operator*=(vector<L>& l, R const& r);
			template <typename L, typename R>
			vector<typename std::common_type<L, R>::type> operator*(L const& l, vector<R> const& r);

			template <typename L, typename R>
			vector<typename std::common_type<L, R>::type> operator/(vector<L> const& l, R const& r);
			template <typename L, typename R>
			vector<L>& operator/=(vector<L>& l, R const& r);

			template <typename L, typename R>
			typename std::common_type<L, R>::type dot(vector<L> const& l, vector<R> const& r);

			template <typename L, typename R>
			typename std::common_type<L, R>::type cross(vector<L> const& l, vector<R> const& r);

			template <typename T>
			auto sqr(vector<T> const& v)
				-> decltype(dot(v, v));

			template <typename T>
			auto len(vector<T> const& v)
				-> decltype(sqrt(sqr(v)));

			template <typename T>
			auto unit(vector<T> const& v)
				-> decltype(v/len(v));

			template <typename L, typename R>
			bool operator==(vector<L> const& l, vector<R> const& r);
			template <typename L, typename R>
			bool operator!=(vector<L> const& l, vector<R> const& r);

			template <typename T>
			vector<T> perp(vector<T> const& v);
		}
	}

	#include "vector.inl"

#endif

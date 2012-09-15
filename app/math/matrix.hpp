#ifndef APP_MATH_MATRIX_HPP
	#define APP_MATH_MATRIX_HPP

	#include <type_traits>

	#include "vector.hpp"

	namespace bitsmithery
	{
		namespace math
		{
			template <typename T>
			class matrix
			{
				public:
					T s00; T s01; T s02;
					T s10; T s11; T s12;

					matrix() = default;
					matrix(matrix const& that) = default;
					matrix& operator=(matrix const& that) = default;
					matrix(matrix&& that) = default;
					matrix& operator=(matrix&& that) = default;
					~matrix() = default;

					template
					<
						typename S00, typename S01, typename S02,
						typename S10, typename S11, typename S12
					>
					matrix
					(
						S00 const& s00, S01 const& s01, S02 const& s02,
						S10 const& s10, S11 const& s11, S12 const& s12
					);

					template <typename U>
					matrix(matrix<U> const& that);

					template <typename U>
					matrix& operator=(matrix<U> const& that);

					static matrix translation(vector<T> const& displacement);
					matrix& translate(vector<T> const& displacement);

					template <typename Angle>
					static matrix rotation(Angle const& angle);
					template <typename Angle>
					matrix& rotate(Angle const& angle);

					static matrix scaling(T const& factor);
					matrix& scale(T const& factor);
			};

			typedef matrix<float> matrixf;
			typedef matrix<double> matrixd;

			template <typename T>
			matrix<T> operator~(matrix<T> const& m);

			template <typename L, typename R>
			matrix<typename std::common_type<L, R>::type> operator*(matrix<L> const& l, matrix<R> const& r);
			template <typename L, typename R>
			matrix<L>& operator*=(matrix<L>& l, matrix<R> const& r);

			template <typename M, typename V>
			vector<typename std::common_type<M, V>::type> operator*(matrix<M> const& m, vector<V> const& v);
		}
	}

	#include "matrix.inl"

#endif

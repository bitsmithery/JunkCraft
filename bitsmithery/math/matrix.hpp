#ifndef BITSMITHERY_MATH_MATRIX_HPP
	#define BITSMITHERY_MATH_MATRIX_HPP

	#include <type_traits>

	#include "vector.hpp"

	namespace bitsmithery
	{
		namespace math
		{
			template <typename E>
			class matrix
			{
				public:
					E e00; E e01;
					E e10; E e11;
					E e20; E e21;

					matrix() = default;
					matrix(matrix const& that) = default;
					matrix& operator=(matrix const& that) = default;
					matrix(matrix&& that) = default;
					matrix& operator=(matrix&& that) = default;
					template <typename TE>
					matrix(matrix<TE> const& that);
					template <typename TE>
					matrix& operator=(matrix<TE> const& that);
					~matrix() = default;

					template
					<
						typename E00, typename E01,
						typename E10, typename E11,
						typename E20, typename E21
					>
					matrix
					(
						E00 const& e00, E01 const& e01,
						E10 const& e10, E11 const& e11,
						E20 const& e20, E21 const& e21
					);
			};

			template <typename E>
			matrix<E> operator~(matrix<E> const& m);

			template <typename LE, typename RE>
			matrix<typename std::common_type<LE, RE>::type> operator*(matrix<LE> const& l, matrix<RE> const& r);
			template <typename LE, typename RE>
			matrix<LE>& operator*=(matrix<LE>& l, matrix<RE> const& r);

			template <typename VE, typename ME>
			vector<typename std::common_type<VE, ME>::type> operator*(vector<VE> const& v, matrix<ME> const& m);
			template <typename VE, typename ME>
			vector<VE>& operator*=(vector<VE>& v, matrix<ME> const& m);

			template <typename ME, typename DE>
			matrix<ME> translation(vector<DE> const& displacement);

			template <typename ME, typename A>
			matrix<ME> rotation(A const& angle);
			template <typename ME, typename A, typename CE>
			matrix<ME> rotation(A const& angle, vector<CE> const& center);

			template <typename ME, typename F>
			matrix<ME> scaling(F const& factor);
			template <typename ME, typename F, typename CE>
			matrix<ME> scaling(F const& factor, vector<CE> const& center);
			template <typename ME, typename FE>
			matrix<ME> scaling(vector<FE> const& factor);
			template <typename ME, typename FE, typename CE>
			matrix<ME> scaling(vector<FE> const& factor, vector<CE> const& center);
		}
	}

	#include "matrix.inl"

#endif

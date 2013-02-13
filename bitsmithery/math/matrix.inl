#include <math.h>

namespace bitsmithery
{
	namespace math
	{
		template <typename E>
		template <typename TE>
		matrix<E>::matrix(matrix<TE> const& that)
			: e00(that.e00), e01(that.s01)
			, e10(that.e10), e11(that.s11)
			, e20(that.e20), e21(that.s21)
		{}

		template <typename E>
		template <typename TE>
		matrix<E>& matrix<E>::operator=(matrix<TE> const& that)
		{
			e00 = that.e00; e01 = that.e01;
			e10 = that.e10; e11 = that.e11;
			e20 = that.e20; e21 = that.e21;
			return *this;
		}

		template <typename E>
		template
		<
			typename E00, typename E01,
			typename E10, typename E11,
			typename E20, typename E21
		>
		matrix<E>::matrix
		(
			E00 const& e00, E01 const& e01,
			E10 const& e10, E11 const& e11,
			E20 const& e20, E21 const& e21
		)
			: e00(e00), e01(e01)
			, e10(e10), e11(e11)
			, e20(e20), e21(e21)
		{}

		template <typename E>
		matrix<E> operator~(matrix<E> const& m)
		{
			auto const id = 1 / (m.s00 * m.s11 - m.s01 * m.s10);
			return {
				(                      + m.s11) * id, (                      - m.s01) * id,
				(                      - m.s10) * id, (                      + m.s00) * id,
				(m.e10 * m.e21 - m.e20 * m.e11) * id, (m.e20 * m.e01 - m.e00 * m.e21) * id,
			};
		}

		template <typename LE, typename RE>
		matrix<typename std::common_type<LE, RE>::type> operator*(matrix<LE> const& l, matrix<RE> const& r)
		{
			return {
				(l.e00 * r.e00 + l.e01 * r.e10        ), (l.e00 * r.e01 + l.e01 * r.e11        ),
				(l.e10 * r.e00 + l.e11 * r.e10        ), (l.e10 * r.e01 + l.e11 * r.e11        ),
				(l.e20 * r.e00 + l.e21 * r.e10 + r.e20), (l.e20 * r.e01 + l.e21 * r.e11 + r.e21),
			};
		}
		template <typename LE, typename RE>
		matrix<LE>& operator*=(matrix<LE>& l, matrix<RE> const& r)
		{
			return l *= r;
		}

		template <typename VE, typename ME>
		vector<typename std::common_type<VE, ME>::type> operator*(vector<VE> const& v, matrix<ME> const& m)
		{
			return {(v.x * m.e00 + v.y * m.e10 + m.e20), (v.x * m.e01 + v.y * m.e11 + m.e21)};
		}
		template <typename VE, typename ME>
		vector<VE>& operator*=(vector<VE>& v, matrix<ME> const& m)
		{
			return v *= m;
		}

		template <typename ME, typename DE>
		matrix<ME> translation(vector<DE> const& displacement)
		{
			return {
				             1,              0,
				             0,              1,
				displacement.x, displacement.y,
			};
		}

		template <typename ME, typename A>
		matrix<ME> rotation(A const& angle)
		{
			auto const s = sin(angle), c = cos(angle);
			return {
				+c, -s,
				+s, +c,
				 0,  0,
			};
		}
		template <typename ME, typename A, typename CE>
		matrix<ME> rotation(A const& angle, vector<CE> const& center)
		{
			return translation(-center) * rotation(angle) * translation(+center);
		}

		template <typename ME, typename F>
		matrix<ME> scaling(F const& factor)
		{
			return {
				factor,      0,
				     0, factor,
				     0,      0,
			};
		}
		template <typename ME, typename F, typename CE>
		matrix<ME> scaling(F const& factor, vector<CE> const& center)
		{
			return translation(-center) * scaling(factor) * translation(+center);
		}
		template <typename ME, typename FE>
		matrix<ME> scaling(vector<FE> const& factor)
		{
			return {
				factor.x,        0,
				       0, factor.y,
				       0,        0,
			};
		}
		template <typename ME, typename FE, typename CE>
		matrix<ME> scaling(vector<FE> const& factor, vector<CE> const& center)
		{
			return translation(-center) * scaling(factor) * translation(+center);
		}
	}
}

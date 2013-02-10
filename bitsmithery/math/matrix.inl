#include "common.hpp"

namespace bitsmithery
{
	namespace math
	{
		template <typename T>
		template
		<
			typename S00, typename S01, typename S02,
			typename S10, typename S11, typename S12
		>
		inline
		matrix<T>::matrix
		(
			S00 const& s00, S01 const& s01, S02 const& s02,
			S10 const& s10, S11 const& s11, S12 const& s12
		)
			: s00(s00), s01(s01), s02(s02)
			, s10(s10), s11(s11), s12(s12)
		{}

		template <typename T>
		template <typename U>
		inline
		matrix<T>::matrix(matrix<U> const& that)
			: s00(that.s00), s01(that.s01), s02(that.s02)
			, s10(that.s10), s11(that.s11), s12(that.s12)
		{}

		template <typename T>
		template <typename U>
		inline
		matrix<T>& matrix<T>::operator=(matrix<U> const& that)
		{
			s00 = that.s00; s01 = that.s01; s02 = that.s02;
			s10 = that.s10; s11 = that.s11; s12 = that.s12;
			return *this;
		}

		template <typename T>
		inline
		matrix<T> matrix<T>::translation(vector<T> const& displacement)
		{
			return
			{
				T(1), T(0), displacement.x,
				T(0), T(1), displacement.y
			};
		}
		template <typename T>
		inline
		matrix<T>& matrix<T>::translate(vector<T> const& displacement)
		{
			return (*this) *= translation(displacement);
		}

		template <typename T>
		template <typename Angle>
		inline
		matrix<T> matrix<T>::rotation(Angle const& angle)
		{
			T s = sin(angle);
			T c = cos(angle);
			return
			{
				c, -s, T(0),
				s,  c, T(0),
			};
		}
		template <typename T>
		template <typename Angle>
		inline
		matrix<T>& matrix<T>::rotate(Angle const& angle)
		{
			return (*this) *= rotation(angle);
		}

		template <typename T>
		inline
		matrix<T> matrix<T>::scaling(T const& factor)
		{
			return
			{
				factor,   T(0),   T(0),
				  T(0), factor,   T(0),
			};
		}
		template <typename T>
		inline
		matrix<T>& matrix<T>::scale(T const& factor)
		{
			return (*this) *= scaling(factor);
		}

		template <typename T>
		inline
		matrix<T> operator~(matrix<T> const& m)
		{
			auto d = m.s00*m.s11 - m.s01*m.s10;
			return
			{
				 m.s11/d, -m.s01/d, (m.s01*m.s12 - m.s11*m.s02)/d,
				-m.s10/d,  m.s00/d, (m.s10*m.s02 - m.s00*m.s12)/d
			};
		}

		template <typename L, typename R>
		inline
		matrix<typename std::common_type<L, R>::type> operator*(matrix<L> const& l, matrix<R> const& r)
		{
			return
			{
				l.s00*r.s00 + l.s01*r.s10, l.s00*r.s01 + l.s01*r.s11, l.s00*r.s02 + l.s01*r.s12 + l.s02,
				l.s10*r.s00 + l.s11*r.s10, l.s10*r.s01 + l.s11*r.s11, l.s10*r.s02 + l.s11*r.s12 + l.s12
			};
		}
		template <typename L, typename R>
		inline
		matrix<L>& operator*=(matrix<L>& l, matrix<R> const& r)
		{
			return l = l*r;
		}

		template <typename M, typename V>
		inline
		vector<typename std::common_type<M, V>::type> operator*(matrix<M> const& m, vector<V> const& v)
		{
			return {m.s00*v.x + m.s01*v.y + m.s02, m.s10*v.x + m.s11*v.y + m.s12};
		}
	}
}

#ifndef BITSMITHERY_MATH_VECTOR_HPP
    #define BITSMITHERY_MATH_VECTOR_HPP

	#include <type_traits>
	#include <math.h>

	namespace bitsmithery
	{
		namespace math
		{
			template <typename E>
			class vector
			{
				public:
					E x; E y;

					vector() = default;
					vector(vector const& that) = default;
					vector& operator=(vector const& that) = default;
					vector(vector&& that) = default;
					vector& operator=(vector&& that) = default;
					template <typename TE>
					vector(vector<TE> const& that);
					template <typename TE>
					vector& operator=(vector<TE> const& that);
					~vector() = default;

					template <typename X, typename Y>
					vector(X const& x, Y const& y);
			};

			template <typename E>
			vector<E> operator+(vector<E> const& v);

			template <typename E>
			vector<E> operator-(vector<E> const& v);

			template <typename LE, typename RE>
			vector<typename std::common_type<LE, RE>::type> operator+(vector<LE> const& l, vector<RE> const& r);
			template <typename LE, typename RE>
			vector<LE>& operator+=(vector<LE>& l, vector<RE> const& r);

			template <typename LE, typename RE>
			vector<typename std::common_type<LE, RE>::type> operator-(vector<LE> const& l, vector<RE> const& r);
			template <typename LE, typename RE>
			vector<LE>& operator-=(vector<LE>& l, vector<RE> const& r);

			template <typename VE, typename S>
			vector<typename std::common_type<VE, S>::type> operator*(vector<VE> const& v, S const& s);
			template <typename VE, typename S>
			vector<VE>& operator*=(vector<VE>& v, S const& s);
			template <typename S, typename VE>
			vector<typename std::common_type<S, VE>::type> operator*(S const& s, vector<VE> const& v);

			template <typename VE, typename S>
			vector<typename std::common_type<VE, S>::type> operator/(vector<VE> const& v, S const& s);
			template <typename VE, typename S>
			vector<VE>& operator/=(vector<VE>& v, S const& s);

			template <typename LE, typename RE>
			typename std::common_type<LE, RE>::type dot(vector<LE> const& l, vector<RE> const& r);

			template <typename LE, typename RE>
			typename std::common_type<LE, RE>::type wedge(vector<LE> const& l, vector<RE> const& r);

			template <typename E>
			auto sqr_norm(vector<E> const& v)
				-> decltype(v.x * v.x + v.y * v.y);

			template <typename E>
			auto norm(vector<E> const& v)
				-> decltype(sqrt(sqr_norm(v)));

			template <typename E>
			auto unit(vector<E> const& v)
				-> decltype(v / norm(v));

			template <typename LE, typename RE>
			bool operator==(vector<LE> const& l, vector<RE> const& r);
			template <typename LE, typename RE>
			bool operator!=(vector<LE> const& l, vector<RE> const& r);
		}
	}

	#include "vector.inl"

#endif

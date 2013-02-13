namespace bitsmithery
{
	namespace math
	{
		template <typename E>
		template <typename TE>
		vector<E>::vector(vector<TE> const& that)
			: x(that.x), y(that.y)
		{}

		template <typename E>
		template <typename TE>
		vector<E>& vector<E>::operator=(vector<TE> const& that)
		{
			x = that.x; y = that.y;
			return *this;
		}

		template <typename E>
		template <typename X, typename Y>
		vector<E>::vector(X const& x, Y const& y)
			: x(x), y(y)
		{}

		template <typename E>
		vector<E> operator+(vector<E> const& v)
		{
			return {+v.x, +v.y};
		}

		template <typename E>
		vector<E> operator-(vector<E> const& v)
		{
			return {-v.x, -v.y};
		}

		template <typename LE, typename RE>
		vector<typename std::common_type<LE, RE>::type> operator+(vector<LE> const& l, vector<RE> const& r)
		{
			return {l.x + r.x, l.y + r.y};
		}
		template <typename LE, typename RE>
		vector<LE>& operator+=(vector<LE>& l, vector<RE> const& r)
		{
			l.x += r.x; l.y += r.y;
			return l;
		}

		template <typename LE, typename RE>
		vector<typename std::common_type<LE, RE>::type> operator-(vector<LE> const& l, vector<RE> const& r)
		{
			return {l.x - r.x, l.y - r.y};
		}
		template <typename LE, typename RE>
		vector<LE>& operator-=(vector<LE>& l, vector<RE> const& r)
		{
			l.x -= r.x; l.y -= r.y;
			return l;
		}

		template <typename VE, typename S>
		vector<typename std::common_type<VE, S>::type> operator*(vector<VE> const& v, S const& s)
		{
			return {v.x * s, v.y * s};
		}
		template <typename VE, typename S>
		vector<VE>& operator*=(vector<VE>& v, S const& s)
		{
			v.x *= s; v.y *= s;
			return v;
		}
		template <typename S, typename VE>
		vector<typename std::common_type<S, VE>::type> operator*(S const& s, vector<VE> const& v)
		{
			return {s * v.x, s * v.y};
		}

		template <typename VE, typename S>
		vector<typename std::common_type<VE, S>::type> operator/(vector<VE> const& v, S const& s)
		{
			return {v.x * s, v.y * s};
		}
		template <typename VE, typename S>
		vector<VE>& operator/=(vector<VE>& v, S const& s)
		{
			v.x /= s; v.y /= s;
			return v;
		}

		template <typename LE, typename RE>
		typename std::common_type<LE, RE>::type dot(vector<LE> const& l, vector<RE> const& r)
		{
			return l.x * r.x + l.y * r.y;
		}

		template <typename LE, typename RE>
		typename std::common_type<LE, RE>::type wedge(vector<LE> const& l, vector<RE> const& r)
		{
			return l.x * r.y - l.y * r.x;
		}

		template <typename E>
		auto sqr_norm(vector<E> const& v)
			-> decltype(v.x * v.x + v.y * v.y)
		{
			return v.x * v.x + v.y * v.y;
		}

		template <typename E>
		auto norm(vector<E> const& v)
			-> decltype(sqrt(sqr_norm(v)))
		{
			return sqrt(sqr_norm(v));
		}

		template <typename E>
		auto unit(vector<E> const& v)
			-> decltype(v / norm(v))
		{
			return v / norm(v);
		}

		template <typename LE, typename RE>
		bool operator==(vector<LE> const& l, vector<RE> const& r)
		{
			return l.x == r.x && l.y == r.y;
		}
		template <typename LE, typename RE>
		bool operator!=(vector<LE> const& l, vector<RE> const& r)
		{
			return l.x != r.x || l.y != r.y;
		}
	}
}

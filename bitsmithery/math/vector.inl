namespace bitsmithery
{
	namespace math
	{
		template <typename T>
		template <typename X, typename Y>
		inline
		vector<T>::vector(X const& x, Y const& y)
			: x(x), y(y)
		{}

		template <typename T>
		template <typename U>
		inline
		vector<T>::vector(vector<U> const& that)
			: x(that.x), y(that.y)
		{}

		template <typename T>
		template <typename U>
		inline
		vector<T>& vector<T>::operator=(vector<U> const& that)
		{
			x = that.x; y = that.y;
			return *this;
		}

		template <typename T>
		inline
		vector<T> operator-(vector<T> const& v)
		{
			return {-v.x, -v.y};
		}

		template <typename L, typename R>
		inline
		vector<typename std::common_type<L, R>::type> operator+(vector<L> const& l, vector<R> const& r)
		{
			return {l.x + r.x, l.y + r.y};
		}
		template <typename L, typename R>
		inline
		vector<L>& operator+=(vector<L>& l, vector<R> const& r)
		{
			l.x += r.x; l.y += r.y;
			return l;
		}

		template <typename L, typename R>
		inline
		vector<typename std::common_type<L, R>::type> operator-(vector<L> const& l, vector<R> const& r)
		{
			return {l.x - r.x, l.y - r.y};
		}
		template <typename L, typename R>
		inline
		vector<L>& operator-=(vector<L>& l, vector<R> const& r)
		{
			l.x -= r.x; l.y -= r.y;
			return l;
		}

		template <typename L, typename R>
		inline
		vector<typename std::common_type<L, R>::type> operator*(vector<L> const& l, R const& r)
		{
			return {l.x*r, l.y*r};
		}
		template <typename L, typename R>
		inline
		vector<L>& operator*=(vector<L>& l, R const& r)
		{
			l.x *= r; l.y *= r;
			return l;
		}
		template <typename L, typename R>
		inline
		vector<typename std::common_type<L, R>::type> operator*(L const& l, vector<R> const& r)
		{
			return {l*r.x, l*r.y};
		}

		template <typename L, typename R>
		inline
		vector<typename std::common_type<L, R>::type> operator/(vector<L> const& l, R const& r)
		{
			return {l.x/r, l.y/r};
		}
		template <typename L, typename R>
		inline
		vector<L>& operator/=(vector<L>& l, R const& r)
		{
			l.x /= r; l.y /= r;
			return l;
		}

		template <typename L, typename R>
		inline
		typename std::common_type<L, R>::type dot(vector<L> const& l, vector<R> const& r)
		{
			return l.x*r.x + l.y*r.y;
		}

		template <typename L, typename R>
		inline
		typename std::common_type<L, R>::type cross(vector<L> const& l, vector<R> const& r)
		{
			return l.x*r.y - l.y*r.x;
		}

		template <typename T>
		inline
		auto sqr(vector<T> const& v)
			-> decltype(dot(v, v))
		{
			return dot(v, v);
		}

		template <typename T>
		inline
		auto len(vector<T> const& v)
			-> decltype(sqrt(sqr(v)))
		{
			return sqrt(sqr(v));
		}

		template <typename T>
		inline
		auto unit(vector<T> const& v)
			-> decltype(v/len(v))
		{
			return v/len(v);
		}

		template <typename L, typename R>
		inline
		bool operator==(vector<L> const& l, vector<R> const& r)
		{
			return (l.x == r.x) && (l.y == r.y);
		}
		template <typename L, typename R>
		inline
		bool operator!=(vector<L> const& l, vector<R> const& r)
		{
			return (l.x != r.x) || (l.y != r.y);
		}

		template <typename T>
		inline
		vector<T> perp(vector<T> const& v)
		{
			return vector<T>(-v.y, v.x);
		}
	}
}

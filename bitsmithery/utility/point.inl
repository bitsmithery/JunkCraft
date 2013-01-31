namespace bitsmithery
{
	namespace utility
	{
		template <typename T>
		template <typename X, typename Y>
		inline
		point<T>::point(X const& x, Y const& y)
			: x(x), y(y)
		{}

		template <typename T>
		template <typename U>
		inline
		point<T>::point(point<U> const& that)
			: x(that.x), y(that.y)
		{}

		template <typename T>
		template <typename U>
		inline
		point<T>& point<T>::operator=(point<U> const& that)
		{
			x = that.x; y = that.y;
			return *this;
		}

		template <typename T>
		template <typename U>
		point<T>::point(math::vector<U> const& that)
			: x(that.x), y(that.y)
		{}

		template <typename T>
		template <typename U>
		point<T>::operator math::vector<U>() const
		{
			return {x, y};
		}

		template <typename L, typename R>
		inline
		math::vector<typename std::common_type<L, R>::type> operator-(point<L> const& l, point<R> const& r)
		{
			return {l.x - r.x, l.y - r.y};
		}

		template <typename L, typename R>
		inline
		point<typename std::common_type<L, R>::type> operator+(point<L> const& l, math::vector<R> const& r)
		{
			return {l.x + r.x, l.y + r.y};
		}
		template <typename L, typename R>
		inline
		point<L>& operator+=(point<L>& l, math::vector<R> const& r)
		{
			l.x += r.x;
			l.y += r.y;
			return l;
		}

		template <typename L, typename R>
		inline
		point<typename std::common_type<L, R>::type> operator-(point<L> const& l, math::vector<R> const& r)
		{
			return {l.x - r.x, l.y - r.y};
		}
		template <typename L, typename R>
		inline
		point<L>& operator-=(point<L>& l, math::vector<R> const& r)
		{
			l.x -= r.x; l.y -= r.y;
			return l;
		}

		template <typename L, typename R>
		inline
		bool operator==(point<L> const& l, point<R> const& r)
		{
			return (l.x == r.x) && (l.y == r.y);
		}
		template <typename L, typename R>
		inline
		bool operator!=(point<L> const& l, point<R> const& r)
		{
			return (l.x != r.x) || (l.y != r.y);
		}
	}
}

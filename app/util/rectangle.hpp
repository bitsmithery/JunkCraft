#ifndef APP_UTIL_RECTENGLE_HPP
	#define APP_UTIL_RECTENGLE_HPP

	#include <type_traits>

	#include "../math.hpp"
	#include "size.hpp"

	namespace app
	{
		namespace util
		{
			template <typename T>
			class rectangle
			{
				public:
					math::point<T> a;
					math::point<T> b;

					rectangle() = default;

					template <typename U>
					rectangle(math::point<U> const& a, math::point<U> const& b);

					rectangle(rectangle const& that) = default;

					template <typename U>
					rectangle(rectangle<U> const& that);

					rectangle& operator=(rectangle const& that) = default;

					template <typename U>
					rectangle& operator=(rectangle<U> const& that);

					rectangle(rectangle&& that) = default;

					rectangle& operator=(rectangle&& that) = default;

					~rectangle() = default;

					size<T> get_size() const;

					math::point<T> get_center() const;
			};

			typedef rectangle<float> rectanglef;
			typedef rectangle<double> rectangled;
			typedef rectangle<int> rectanglei;
			typedef rectangle<unsigned> rectangleu;

			template <typename T>
			template <typename U>
			inline
			rectangle<T>::rectangle(math::point<U> const& a, math::point<U> const& b)
				: a(a), b(b)
			{
			}

			template <typename T>
			template <typename U>
			inline
			rectangle<T>::rectangle(rectangle<U> const& that)
				: a(that.a), b(that.b)
			{
			}

			template <typename T>
			template <typename U>
			inline
			rectangle<T>& rectangle<T>::operator=(rectangle<U> const& that)
			{
				a = that.a;
				b = that.b;
				return *this;
			}

			template <typename T>
			inline
			size<T> rectangle<T>::get_size() const
			{
				return {b.x - a.x, b.y - a.y};
			}

			template <typename T>
			inline
			math::point<T> rectangle<T>::get_center() const
			{
				return {(a.x + b.x)/T(2), (a.y + b.y)/T(2)};
			}

			template <typename L, typename R>
			inline
			rectangle<typename std::common_type<L, R>::type> operator&(rectangle<L> const& l, rectangle<R> const& r)
			{
				return
				{
					{math::max(l.a.x, r.a.x), math::max(l.a.y, r.a.y)},
					{math::min(l.b.x, r.b.x), math::min(l.b.y, r.b.y)}
				};
			}

			template <typename L, typename R>
			inline
			rectangle<typename std::common_type<L, R>::type> operator|(rectangle<L> const& l, rectangle<R> const& r)
			{
				return
				{
					{math::min(l.a.x, r.a.x), math::min(l.a.y, r.a.y)},
					{math::max(l.b.x, r.b.x), math::max(l.b.y, r.b.y)}
				};
			}

			template <typename L, typename R>
			inline
			bool operator==(rectangle<L> const& l, rectangle<R> const& r)
			{
				return (l.a == r.a) && (l.b == r.b);
			}

			template <typename L, typename R>
			inline
			bool operator!=(rectangle<L> const& l, rectangle<R> const& r)
			{
				return (l.a != r.a) || (l.b != r.b);
			}

			template <typename Archive, typename T>
			void serialize(Archive& archive, rectangle<T>& object, const unsigned int version)
			{
				archive & object.a;
				archive & object.b;
			}
		}
	}

#endif //APP_UTIL_RECTENGLE_HPP

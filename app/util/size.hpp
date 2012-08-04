#ifndef APP_UTIL_SIZE_HPP
	#define APP_UTIL_SIZE_HPP

	namespace app
	{
		namespace util
		{
			template <typename T>
			class size
			{
				public:
					T x; T y;

					size() = default;

					template <typename U>
					size(U const& x, U const& y);

					size(size const& that) = default;

					template <typename U>
					size(size<U> const& that);

					size& operator=(size const& that) = default;

					template <typename U>
					size& operator=(size<U> const& that);

					size(size&& that) = default;

					size& operator=(size&& that) = default;

					~size() = default;

					T get_area() const;
			};

			typedef size<float> sizef;
			typedef size<double> sized;
			typedef size<int> sizei;
			typedef size<unsigned> sizeu;

			template <typename T>
			template <typename U>
			inline
			size<T>::size(U const& x, U const& y)
				: x(x), y(y)
			{
			}

			template <typename T>
			template <typename U>
			inline
			size<T>::size(size<U> const& that)
				: x(that.x), y(that.y)
			{
			}

			template <typename T>
			template <typename U>
			inline
			size<T>& size<T>::operator=(size<U> const& that)
			{
				x = that.x;
				y = that.y;
				return *this;
			}

			template <typename T>
			inline
			T size<T>::get_area() const
			{
				return x*y;
			}

			template <typename L, typename R>
			inline
			bool operator==(size<L> const& l, size<R> const& r)
			{
				return (l.x == r.x) && (l.y == r.y);
			}

			template <typename L, typename R>
			inline
			bool operator!=(size<L> const& l, size<R> const& r)
			{
				return (l.x != r.x) || (l.y != r.y);
			}

			template <typename Archive, typename T>
			void serialize(Archive& archive, size<T>& object, const unsigned int version)
			{
				archive & object.x;
				archive & object.y;
			}
		}
	}

#endif //APP_UTIL_SIZE_HPP

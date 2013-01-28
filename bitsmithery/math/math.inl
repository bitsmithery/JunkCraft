namespace bitsmithery
{
	namespace math
	{
		template <typename T>
		inline
		T sqr(T x)
		{
			return x*x;
		}

		template <typename T>
		inline
		T clamp(T a, T x, T b)
		{
			if (x < a)
				return a;
			if (b < x)
				return b;
			return x;
		}
	}
}

#ifndef BITSMITHERY_UTIL_TUPLE_WRAP_HPP
	#define BITSMITHERY_UTIL_TUPLE_WRAP_HPP

	#include <tuple>

	namespace bitsmithery
	{
		namespace util
		{
			template <typename Tuple, template <typename TupleElement> class Wrapper>
			struct tuple_wrap;

			template <typename... TupleElements, template <typename TupleElement> class Wrapper>
			struct tuple_wrap<std::tuple<TupleElements...>, Wrapper>
			{
				typedef std::tuple<typename Wrapper<TupleElements>::type...> type;
			};
		}
	}

#endif

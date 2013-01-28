#ifndef BITSMITHERY_UTIL_TUPLE_SPILL_HPP
	#define BITSMITHERY_UTIL_TUPLE_SPILL_HPP

	#include <tuple>

	namespace bitsmithery
	{
		namespace util
		{
			template <typename Tuple, template <typename...> class Pit>
			struct tuple_spill;

			template <typename... TupleElements, template <typename...> class Pit>
			struct tuple_spill<std::tuple<TupleElements...>, Pit>
			{
				typedef Pit<TupleElements...> type;
			};
		}
	}

#endif

#ifndef BITSMITHERY_UTIL_TUPLE_FIND_HPP
	#define BITSMITHERY_UTIL_TUPLE_FIND_HPP

	#include <tuple>
	#include <type_traits>
	#include <cstddef>

	namespace bitsmithery
	{
		namespace utility
		{
			template <typename Tuple, typename Target>
			struct tuple_find;

			template <typename TupleHeadElement, typename... TupleTailElements, typename Target>
			struct tuple_find<std::tuple<TupleHeadElement, TupleTailElements...>, Target>
				: std::integral_constant<std::size_t, 1 + tuple_find<std::tuple<TupleTailElements...>, Target>::value>
			{
			};

			template <typename... TupleTailElements, typename Target>
			struct tuple_find<std::tuple<Target, TupleTailElements...>, Target>
				: std::integral_constant<std::size_t, 0>
			{
			};

			template <typename Target>
			struct tuple_find<std::tuple<>, Target>
				: std::integral_constant<std::size_t, 1>
			{
			};
		}
	}

#endif

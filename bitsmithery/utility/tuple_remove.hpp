#ifndef BITSMITHERY_UTIL_TUPLE_REMOVE_HPP
	#define BITSMITHERY_UTIL_TUPLE_REMOVE_HPP

	#include <tuple>

	#include "tuple_join.hpp"

	namespace bitsmithery
	{
		namespace utility
		{
			template <typename Tuple, typename Target>
			struct tuple_remove;

			template <typename TupleHeadElement, typename... TupleTailElements, typename Target>
			struct tuple_remove<std::tuple<TupleHeadElement, TupleTailElements...>, Target>
				: tuple_join<std::tuple<TupleHeadElement>, typename tuple_remove<std::tuple<TupleTailElements...>, Target>::type>
			{
			};

			template <typename Target, typename... TupleTailElements>
			struct tuple_remove<std::tuple<Target, TupleTailElements...>, Target>
				: tuple_remove<std::tuple<TupleTailElements...>, Target>
			{
			};

			template <typename Target>
			struct tuple_remove<std::tuple<>, Target>
			{
				typedef std::tuple<> type;
			};
		}
	}

#endif

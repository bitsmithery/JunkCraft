#ifndef BITSMITHERY_UTIL_TUPLE_UNIQUIZE_HPP
	#define BITSMITHERY_UTIL_TUPLE_UNIQUIZE_HPP

	#include <tuple>

	#include "tuple_join.hpp"
	#include "tuple_remove.hpp"

	namespace bitsmithery
	{
		namespace util
		{
			template <typename Tuple>
			struct tuple_uniquize;

			template <typename TupleHeadElement, typename... TupleTailElements>
			struct tuple_uniquize<std::tuple<TupleHeadElement, TupleTailElements...>>
				: tuple_join<std::tuple<TupleHeadElement>, typename tuple_uniquize<typename tuple_remove<std::tuple<TupleTailElements...>, TupleHeadElement>::type>::type>
			{
			};

			template <typename TupleElement>
			struct tuple_uniquize<std::tuple<TupleElement>>
			{
				typedef std::tuple<TupleElement> type;
			};

			template <>
			struct tuple_uniquize<std::tuple<>>
			{
				typedef std::tuple<> type;
			};
		}
	}

#endif

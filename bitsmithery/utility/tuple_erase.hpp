#ifndef BITSMITHERY_UTIL_TUPLE_ERASE_HPP
	#define BITSMITHERY_UTIL_TUPLE_ERASE_HPP

	#include <tuple>

	#include "tuple_join.hpp"

	namespace bitsmithery
	{
		namespace utility
		{
			template <typename Tuple, std::size_t begin, std::size_t end = begin + 1>
			struct tuple_erase;

			template <typename TupleHeadElement, typename... TupleTailElements, std::size_t begin, std::size_t end>
			struct tuple_erase<std::tuple<TupleHeadElement, TupleTailElements...>, begin, end>
				: tuple_join<std::tuple<TupleHeadElement>, typename tuple_erase<std::tuple<TupleTailElements...>, begin - 1, end - 1>::type>
			{
			};

			template <typename TupleHeadElement, typename... TupleTailElements, std::size_t end>
			struct tuple_erase<std::tuple<TupleHeadElement, TupleTailElements...>, 0, end>
				: tuple_erase<std::tuple<TupleTailElements...>, 0, end - 1>
			{
			};

				// joining head and tail makes this ambiguous with other specializations
			template <typename TupleHeadElement, typename... TupleTailElements>
			struct tuple_erase<std::tuple<TupleHeadElement, TupleTailElements...>, 0, 0>
			{
				typedef std::tuple<TupleHeadElement, TupleTailElements...> type;
			};
		}
	}

#endif

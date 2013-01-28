#ifndef BITSMITHERY_UTIL_TUPLE_JOIN_HPP
	#define BITSMITHERY_UTIL_TUPLE_JOIN_HPP

	#include <tuple>

	namespace bitsmithery
	{
		namespace util
		{
			template <typename... Tuples>
			struct tuple_join;

			template <typename HeadTuple, typename... TailTuples>
			struct tuple_join<HeadTuple, TailTuples...>
				: tuple_join<HeadTuple, typename tuple_join<TailTuples...>::type>
			{
			};

			template <typename... TupleOneElements, typename... TupleTwoElements>
			struct tuple_join<std::tuple<TupleOneElements...>, std::tuple<TupleTwoElements...>>
			{
				typedef std::tuple<TupleOneElements..., TupleTwoElements...> type;
			};

			template <typename... TupleElements>
			struct tuple_join<std::tuple<TupleElements...>>
			{
				typedef std::tuple<TupleElements...> type;
			};

			template <>
			struct tuple_join<>
			{
				typedef std::tuple<> type;
			};
		}
	}

#endif

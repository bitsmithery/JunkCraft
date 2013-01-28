#ifndef BITSMITHERY_UTIL_TUPLE_APPLY_HPP
	#define BITSMITHERY_UTIL_TUPLE_APPLY_HPP

	#include <tuple>

	namespace bitsmithery
	{
		namespace util
		{
			template <typename Tuple, template <typename TupleElement> class... Modifiers>
			struct tuple_apply;

			template <typename... TupleElements, template <typename TupleElement> class HeadModifier, template <typename TupleElement> class... TailModifiers>
			struct tuple_apply<std::tuple<TupleElements...>, HeadModifier, TailModifiers...>
			{
				typedef typename tuple_apply<std::tuple<typename HeadModifier<TupleElements>::type...>, TailModifiers...>::type type;
			};

			template <typename... TupleElements>
			struct tuple_apply<std::tuple<TupleElements...>>
			{
				typedef std::tuple<TupleElements...> type;
			};
		}
	}

#endif

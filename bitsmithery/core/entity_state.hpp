#ifndef BITSMITHERY_CORE_ENTITY_STATE_HPP
	#define BITSMITHERY_CORE_ENTITY_STATE_HPP

	#include <type_traits>

	namespace bitsmithery
	{
		namespace core
		{
			struct entity_state_fragment
			{};

			template <typename Type>
			struct is_entity_state_fragment
			    : std::integral_constant<bool, std::is_base_of<Type, entity_state_fragment>::value && !std::is_same<Type, entity_state_fragment>::value && !std::is_empty<Type>::value>
			{};
		}
	}

#endif

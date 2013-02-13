#ifndef BITSMITHERY_ENTITY_STATE_HPP
	#define BITSMITHERY_ENTITY_STATE_HPP

	#include <type_traits>

	namespace bitsmithery
	{
		struct entity_state_fragment
		{};

		template <typename Type>
		struct is_entity_state_fragment
			: std::integral_constant<bool, std::is_base_of<Type, entity_state_fragment>() && !std::is_same<Type, entity_state_fragment>() && !std::is_empty<Type>()>
		{};
	}

#endif

#ifndef BITSMITHERY_CORE_MESSAGE_HPP
	#define BITSMITHERY_CORE_MESSAGE_HPP

	#include <type_traits>

	namespace bitsmithery
	{
		namespace core
		{
			struct message
			{};

			template <typename Type>
			struct is_message
			    : std::integral_constant<bool, std::is_base_of<Type, message>::value && !std::is_same<Type, message>::value>
			{};
		}
	}

#endif

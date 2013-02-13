#ifndef BITSMITHERY_MESSAGE_HPP
	#define BITSMITHERY_MESSAGE_HPP

	#include <type_traits>

	namespace bitsmithery
	{
		struct message
		{};

		template <typename Type>
		struct is_message
			: std::integral_constant<bool, std::is_base_of<Type, message>() && !std::is_same<Type, message>()>
		{};
	}

#endif

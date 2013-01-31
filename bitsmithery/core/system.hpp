#ifndef BITSMITHERY_CORE_SYSTEM_HPP
	#define BITSMITHERY_CORE_SYSTEM_HPP

	#include <type_traits>

	namespace bitsmithery
	{
		namespace core
		{
			class system
			{
				protected:
					system() = default;
					system(system const& that) = delete;
					system(system&& that) = default;
					system& operator=(system const& that) = delete;
					system& operator=(system&& that) = default;
					~system() = default;
			};

			template <typename Type>
			struct is_system
				: std::integral_constant<bool, std::is_base_of<Type, system>::value && !std::is_same<Type, system>::value>
			{};
		}
	}

#endif

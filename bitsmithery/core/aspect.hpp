#ifndef BITSMITHERY_CORE_ASPECT_HPP
	#define BITSMITHERY_CORE_ASPECT_HPP

	#include <type_traits>
	#include <unordered_map>

	#include "entity.hpp"

	namespace bitsmithery
	{
		namespace core
		{
			class aspect
			{
				protected:
					aspect() = default;
					aspect(aspect const& that) = default;
					aspect& operator=(aspect const& that) = default;
					~aspect() = default;
			};

			template <typename Type>
			struct is_aspect
				: std::integral_constant<bool, std::is_base_of<Type, aspect>::value && !std::is_same<Type, aspect>::value>
			{};

			template <typename Aspect>
			using aspect_map = std::unordered_map<entity_id, Aspect>;

			template <typename Type>
			struct is_aspect_map
				: std::false_type
			{};

			template <typename Aspect>
			struct is_aspect_map<aspect_map<Aspect>>
				: is_aspect<Aspect>
			{};
		}
	}

#endif

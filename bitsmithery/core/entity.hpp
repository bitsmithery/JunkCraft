#ifndef BITSMITHERY_CORE_ENTITY_HPP
	#define BITSMITHERY_CORE_ENTITY_HPP

	#include <cstdint>
	#include <atomic>
	#include <type_traits>

	namespace bitsmithery
	{
		namespace core
		{
			using entity_id = std::uint64_t;

			entity_id const entity_id_invalid = 0;

			class entity_id_generator
			{
				public:
					entity_id_generator();
					entity_id_generator(entity_id_generator const& that) = delete;
					entity_id_generator& operator=(entity_id_generator const& that) = delete;
					~entity_id_generator() = default;

					entity_id operator()();

				private:
					std::atomic<entity_id> next_id;
			};

			template <typename Type>
			struct is_entity_id_generator
				: std::is_same<Type, entity_id_generator>
			{};
		}
	}

	#include "entity.inl"

#endif

#ifndef BITSMITHERY_ENTITY_HPP
	#define BITSMITHERY_ENTITY_HPP

	#include <cstdint>

	namespace bitsmithery
	{
		class entity
		{
			template <template <typename Engine> class... Systems>
			friend class engine;
			public:
				typedef std::uint32_t id;

			private:
				entity() = default;
				entity(entity const& that) = delete;
				entity& operator=(entity const& that) = delete;
				~entity() = default;
		};
	}

#endif

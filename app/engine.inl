namespace bitsmithery
{
	template <template <typename Engine> class... Systems>
	engine<Systems...>::engine()
		: Systems<engine<Systems...>>(*this)...
	{
	}

	template <template <typename Engine> class... Systems>
	template <template <typename Engine> class System>
	System<engine<Systems...>>& engine<Systems...>::system()
	{
		return *this;
	}
	template <template <typename Engine> class... Systems>
	template <template <typename Engine> class System>
	System<engine<Systems...>> const& engine<Systems...>::system() const
	{
		return *this;
	}

	namespace detail
	{
		template <typename Aspect>
		inline std::uintptr_t engine_get_aspect_map_id()
		{
			static char const dummy = '\0';
			return reinterpret_cast<std::uintptr_t>(&dummy);
		}
	}

	template <template <typename Engine> class... Systems>
	template <typename Aspect>
	std::shared_ptr<std::unordered_map<entity::id, Aspect>> engine<Systems...>::aspect_map_ptr()
	{
		auto aspect_map_id = detail::engine_get_aspect_map_id<std::unordered_map<entity::id, Aspect>>();
		auto it = aspect_map_ptrs.find(aspect_map_id);
		if (it == aspect_map_ptrs.end()) {
			auto aspect_map_ptr = std::make_shared<std::unordered_map<entity::id, Aspect>>();
			it = aspect_map_ptrs.insert({aspect_map_id, aspect_map_ptr}).first;
		}
		return std::static_pointer_cast<std::unordered_map<entity::id, Aspect>>(it->second);
	}

//	namespace detail
//	{
//		std::uint32_t random(std::uint32_t seed)
//		{
//			return seed*312937 + 54769273;
//		}
//	}



//	entity::id engine::entity_create()
//	{
//		do {
//			entity_id_seed = detail::random(entity_id_seed);
//		} while (entity_ids.find(entity_id_seed) != entity_ids.end());
//		entity_ids.insert(entity_id_seed);
//		return entity_id_seed;
//	}
//
//	bool engine::entity_exists(entity::id entity_id)
//	{
//		return entity_ids.find(entity_id_seed) != entity_ids.end();
//	}
//
//	void engine::entity_delete(entity::id entity_id)
//	{
//		// remove aspects here
//		entity_ids.erase(entity_id);
//	}
//
//	template <typename Aspect, typename... AspectConstructorArguments>
//	void engine::aspect_attach(entity::id entity_id, AspectConstructorArguments&&... aspect_constructor_arguments)
//	{
//
//	}
//
//	template <typename Aspect>
//	void engine::aspect_remove(entity::id entity_id)
//	{
//
//	}
}

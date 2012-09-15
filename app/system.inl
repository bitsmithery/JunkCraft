namespace bitsmithery
{
	namespace detail
	{
		template <typename Aspect, typename Engine>
		inline std::shared_ptr<std::unordered_map<entity::id, Aspect>> system_get_aspect_map_ptr(Engine& engine)
		{
			return engine.template aspect_map_ptr<Aspect>();
		}
	}

	template <typename Engine, typename... Aspects>
	system<Engine, Aspects...>::system(Engine& engine)
		: engine(engine)
		, aspect_map_ptrs(detail::system_get_aspect_map_ptr<Aspects>(engine)...)
	{
	}
}

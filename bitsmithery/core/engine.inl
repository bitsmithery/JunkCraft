#include <utility>

#include "system.hpp"

namespace bitsmithery
{
	namespace core
	{
		namespace detail
		{
			template <typename... Arguments>
			void dummy_argument_consumer(Arguments...) {}
		}

		template <typename... Systems>
		engine::engine(Systems&&... systems)
		{
			add_systems(std::forward<Systems>(systems)...);
		}

		void engine::run()
		{
//			for (auto& thread : threads) {
//				thread = std::thread(std::mem_fn(&engine::thread_func), this);
//			}
//
//			terminate_request.wait(terminate_request_lock);
//
//			for (auto& thread : threads) {
//				thread.join();
//			}
		}

		namespace detail
		{
//			template <typename AspectMap>
//			using map_aspect = typename std::conditional<
//			    std::is_const<AspectMap>::value,
//			    typename std::add_const<typename AspectMap::mapped_type>::type,
//			    typename AspectMap::mapped_type
//			>::type;
//
//			template <typename System, typename... AspectMaps>
//			std::tuple<map_aspect<AspectMaps>...> system_aspects_impl(void (System::*)(double time_step_this, AspectMaps&... aspect_maps));
//
//			template <typename System>
//			using aspects_of = decltype(aspects_of_impl(&System::step));


		}

//		template <typename Aspect>
//		std::unordered_map<entity::id, Aspect>& engine::get_aspect_map()
//		{
//			auto it = aspect_maps.find(typeid(Aspect));
//			if (it == aspect_maps.end()) {
//				it = aspect_maps.emplace({typeid(Aspect), new std::unordered_map<entity::id, Aspect>}).first;
//			}
//			return std::static_pointer_cast<std::unordered_map<entity::id, Aspect>>(it->second);
//		}




		template <typename FirstSystem, typename... OtherSystems>
		void engine::add_systems(FirstSystem&& first_system, OtherSystems&&... other_systems)
		{
			add_systems(std::forward<FirstSystem>(first_system));
			add_systems(std::forward<OtherSystems>(other_systems)...);
		}

		template <typename System>
		void engine::add_systems(System&& system)
		{
			if (systems.find(typeid(System)) != systems.end()) {
				throw "duplicate_system";
			}
			systems[typeid(System)] = new System(std::forward<System>(system));

			//add_aspect_maps<detail::system_aspects<>>();
		}

		template <typename System>
		auto engine::system_step_argument()
			-> typename std::enable_if<is_system<System>::value, System&>::type
		{
			return static_cast<System&>(*systems[typeid(System)]);
		}







	}
}

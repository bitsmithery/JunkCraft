#ifndef BITSMITHERY_CORE_ENGINE_HPP
	#define BITSMITHERY_CORE_ENGINE_HPP

	#include <atomic>
	#include <thread>
	#include <mutex>
	#include <unordered_map>
	#include <typeindex>
	#include <memory>

	#include "aspect.hpp"
	#include "entity.hpp"
	#include "system.hpp"

	namespace bitsmithery
	{
		namespace core
		{
			class engine;

			namespace detail
			{
				class system_wrapper_base
				{
					friend class engine;
					public:
						system_wrapper_base() = default;
						system_wrapper_base(system_wrapper_base const& that) = delete;
						system_wrapper_base& operator=(system_wrapper_base const& that) = delete;
						virtual ~system_wrapper_base() = default;

					protected:
						template <typename System, typename... Arguments>
						static void step(System& system, engine& engine);

						template <typename System, typename... Arguments>
						static void (*step_select(void (System::*)(Arguments&...)))(System&, engine&);

					private:
						virtual void step(engine& engine) = 0;
				};
			}

			class engine
			{
				friend class detail::system_wrapper_base;
				public:
					template <typename... Systems>
					engine(Systems&&... systems);
					engine(engine const& that) = delete;
					engine& operator=(engine const& that) = delete;
					~engine() = default;

					void run();

				private:
					//util::task_pool task_pool;


					//std::atomic<entity::id> entity_id_next;

					std::unordered_map<std::type_index, std::shared_ptr<detail::system_wrapper_base>> systems;

					template <typename FirstSystem, typename... OtherSystems>
					void add_systems(FirstSystem&& first_system, OtherSystems&&... other_systems);
					template <typename System>
					void add_systems(System&& system);

					template <typename System>
					auto system_step_argument()
						-> typename std::enable_if<is_system<System>::value, System&>::type;

					//double this_step_time;


					std::unordered_map<std::type_index, std::shared_ptr<void>> aspect_maps;
					//std::mutex aspect_maps_mutex;









					template <typename AspectMap>
					auto system_step_argument()
						-> typename std::enable_if<is_aspect_map<AspectMap>::value, AspectMap&>::type;

					template <typename EntityIdGenerator>
					auto system_step_argument()
						-> typename std::enable_if<is_entity_id_generator<EntityIdGenerator>::value, EntityIdGenerator&>::type;

					//std::vector<std::thread> threads;
					//void thread_func(unsigned thread_index, unsigned thread_count);
			};
		}
	}

	#include "engine.inl"

#endif

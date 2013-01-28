#ifndef BITSMITHERY_CORE_ENGINE_HPP
	#define BITSMITHERY_CORE_ENGINE_HPP

	#include <atomic>
	#include <thread>
	#include <mutex>
	#include <unordered_map>
	#include <typeindex>
	#include <memory>

	#include "entity.hpp"
	#include "aspect.hpp"

	namespace bitsmithery
	{
		namespace core
		{
			namespace detail
			{
				class system_base;
			}

			template <typename System>
			class system;

			template <typename Type>
			struct is_system;

			class engine
			{
				template <typename System>
				friend class system;
				public:
					template <typename... Systems>
					engine(Systems&&... systems);
					engine(engine const&) = delete;
					engine& operator=(engine const&) = delete;
					~engine() = default;

					void run();

				private:

					//std::atomic<entity::id> entity_id_next;

					std::unordered_map<std::type_index, std::shared_ptr<detail::system_base>> systems;

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

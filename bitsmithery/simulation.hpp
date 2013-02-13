#ifndef BITSMITHERY_SIMULATION_HPP
	#define BITSMITHERY_SIMULATION_HPP

	#include <atomic>
	#include <thread>
	#include <mutex>
	#include <unordered_map>
	#include <typeindex>
	#include <memory>

	#include "message.hpp"
	#include "entity_id.hpp"
	#include "entity_state.hpp"
	#include "entity_behaviour.hpp"

	namespace bitsmithery
	{
		class simulation
		{
			public:
				simulation() = default;
				simulation(simulation const& that) = delete;
				simulation& operator=(simulation const& that) = delete;
				~simulation() = default;

				void run();

				template <typename Message>
				auto send(entity_id receiver_id, Message&& message)
					-> typename std::enable_if<is_message<Message>(), void>::type;
				template <typename Message>
				auto broadcast(Message&& message)
					-> typename std::enable_if<is_message<Message>(), void>::type;

				entity_id create_entity();
				void destroy_entity(entity_id id);

				template <typename EntityStateFragment>
				auto attach(entity_id id)
					-> typename std::enable_if<is_entity_state_fragment<EntityStateFragment>(), void>::type;
				template <typename EntityStateFragment>
				auto has(entity_id id)
					-> typename std::enable_if<is_entity_state_fragment<EntityStateFragment>(), bool>::type;
				template <typename EntityStateFragment>
				auto remove(entity_id id)
					-> typename std::enable_if<is_entity_state_fragment<EntityStateFragment>(), void>::type;

				template <typename EntityBehaviourFragment>
				auto attach(entity_id id)
					-> typename std::enable_if<is_entity_behaviour_fragment<EntityBehaviourFragment>(), void>::type;
				template <typename EntityBehaviourFragment>
				auto has(entity_id id)
					-> typename std::enable_if<is_entity_behaviour_fragment<EntityBehaviourFragment>(), bool>::type;
				template <typename EntityBehaviourFragment>
				auto remove(entity_id id)
					-> typename std::enable_if<is_entity_behaviour_fragment<EntityBehaviourFragment>(), void>::type;

			private:









		};
	}

#endif

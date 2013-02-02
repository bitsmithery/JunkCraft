#ifndef BITSMITHERY_CORE_ENGINE_HPP
	#define BITSMITHERY_CORE_ENGINE_HPP

	#include <atomic>
	#include <thread>
	#include <mutex>
	#include <unordered_map>
	#include <typeindex>
	#include <memory>

	#include "entity_id.hpp"
	#include "entity_state.hpp"
	#include "entity_behaviour.hpp"

	namespace bitsmithery
	{
		namespace core
		{

			class engine
			{
				public:
					engine() = default;
					engine(engine const& that) = delete;
					engine& operator=(engine const& that) = delete;
					~engine() = default;

					void run();

					template <typename Message>
					auto send(entity_id receiver_id, Message&& message)
						-> typename std::enable_if<is_message<Message>::value, void>::type;
					template <typename Message>
					auto broadcast(Message&& message)
						-> typename std::enable_if<is_message<Message>::value, void>::type;

					entity_id create_entity();
					void destroy_entity(entity_id id);

					template <typename EntityStateFragment>
					auto attach(entity_id id)
						-> typename std::enable_if<is_entity_state_fragment<EntityStateFragment>::value, void>::type;
					template <typename EntityStateFragment>
					auto has(entity_id id)
						-> typename std::enable_if<is_entity_state_fragment<EntityStateFragment>::value, bool>::type;
					template <typename EntityStateFragment>
					auto remove(entity_id id)
						-> typename std::enable_if<is_entity_state_fragment<EntityStateFragment>::value, void>::type;

					template <typename EntityBehaviourFragment>
					auto attach(entity_id id)
						-> std::enable_if<is_entity_behaviour_fragment<EntityBehaviourFragment>, void>::type;
					template <typename EntityBehaviourFragment>
					auto has(entity_id id)
						-> std::enable_if<is_entity_behaviour_fragment<EntityBehaviourFragment>, bool>::type;
					template <typename EntityBehaviourFragment>
					auto remove(entity_id id)
						-> std::enable_if<is_entity_behaviour_fragment<EntityBehaviourFragment>, void>::type;

				private:









			};
		}
	}

	#include "engine.inl"

#endif

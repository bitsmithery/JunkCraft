#ifndef BITSMITHERY_ENTITY_BEHAVIOUR_HPP
	#define BITSMITHERY_ENTITY_BEHAVIOUR_HPP

	#include <type_traits>

	#include "../utility/tuple_all_of.hpp"
	#include "message.hpp"

	namespace bitsmithery
	{
		namespace detail
		{
			struct entity_behaviour_fragment_tag;


			template <typename BehaviourFragment, typename Message>
			struct entity_behaviour_fragment_has_receive_for_message
			{
				private:
					typedef int (&yes)[1];
					typedef int (&no)[2];

					template <typename M, typename... RelevantStateFragments>
					static auto test_helper(void (BehaviourFragment::*)(M const&, engine&, entity_id, RelevantStateFragments&...))
						-> typename std::enable_if<utility::tuple_all_of<std::tuple<RelevantStateFragments...>, is_entity_state_fragment>::value, yes>::type;

					template <typename M>
					static auto test_helper(...)
						-> no;

					template <typename BF>
					static auto test(int)
						-> decltype(test_helper<Message>(&BF::receive));

					template <typename BF>
					static auto test(...)
						-> no;

				public:
					static bool const value = (sizeof(test<BehaviourFragment>(0)) == sizeof(yes));
			};
		}




		template <typename... RelevantMessages>
		struct entity_behaviour_fragment
		{
			typedef detail::entity_behaviour_fragment_tag entity_behaviour_fragment_tag;



			protected:
				template <typename Message>
				auto send(entity_id receiver_id, Message&& message)
					-> typename std::enable_if<is_message<Message>(), void>::type;
				template <typename Message>
				auto broadcast(Message&& message)
					-> typename std::enable_if<is_message<Message>(), void>::type;



				template <typename EntityBehaviourFragment>
				auto attach()
					-> typename std::enable_if<is_entity_behaviour_fragment<EntityBehaviourFragment>(), void>::type;
				template <typename EntityBehaviourFragment>
				auto has()
					-> typename std::enable_if<is_entity_behaviour_fragment<EntityBehaviourFragment>(), bool>::type;
				template <typename EntityBehaviourFragment>
				auto remove()
					-> typename std::enable_if<is_entity_behaviour_fragment<EntityBehaviourFragment>(), void>::type;
		};


		template <typename Type, typename = detail::entity_behaviour_fragment_tag>
		struct is_entity_behaviour_fragment
			: std::false_type
		{};

		template <typename Type>
		struct is_entity_behaviour_fragment<Type, typename Type::entity_behaviour_fragment_tag>
			: std::integral_constant<bool, std::is_same<typename Type::entity_behaviour_fragment_tag, detail::entity_behaviour_fragment_tag>() && std::is_empty<Type>()>
		{};
	}

#endif

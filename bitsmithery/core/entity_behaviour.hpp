#ifndef BITSMITHERY_CORE_ENTITY_BEHAVIOUR_HPP
	#define BITSMITHERY_CORE_ENTITY_BEHAVIOUR_HPP

	#include <type_traits>

	#include "../utility/tuple_all_of.hpp"
	#include "message.hpp"

	namespace bitsmithery
	{
		namespace core
		{
			namespace detail
			{
				struct entity_behaviour_fragment_tag;


				template <typename EntityBehaviourFragment, typename Message>
				struct entity_behaviour_fragment_has_receive_for_message
				{
					private:
						typedef int (&yes)[1];
						typedef int (&no)[2];

						template <typename M, typename... RelevantStateFragments>
						static auto test_helper(void (EntityBehaviourFragment::*)(M const&, engine&, entity_id, RelevantStateFragments&...))
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
						static bool const value = (sizeof(test<EntityBehaviourFragment>(0)) == sizeof(yes));
				};
			}

			template <typename... RelevantMessages>
			struct entity_behaviour_fragment
			{
				typedef detail::entity_behaviour_fragment_tag entity_behaviour_fragment_tag;
			};


			template <typename Type, typename = detail::entity_behaviour_fragment_tag>
			struct is_entity_behaviour_fragment
				: std::false_type
			{};

			template <typename Type>
			struct is_entity_behaviour_fragment<Type, typename Type::entity_behaviour_fragment_tag>
				: std::integral_constant<bool, std::is_same<typename Type::entity_behaviour_fragment_tag, detail::entity_behaviour_fragment_tag>::value && std::is_empty<Type>::value>
			{};
		}
	}

#endif

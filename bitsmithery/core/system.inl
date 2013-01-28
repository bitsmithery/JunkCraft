#include "engine.hpp"

namespace bitsmithery
{
	namespace core
	{
		namespace detail
		{
			template <typename System, typename... Arguments>
			std::unordered_set<std::type_index> system_signature(void (System::*)(Arguments&...))
			{
				return {};
			}
		}

		template <typename System>
		system<System>::system()
		{
			signature = detail::system_signature(&System::step);
			//signature_const = detail::system_signature_const(&System::step);
		}

		namespace detail
		{
			template <typename System, typename... Arguments>
			struct stepper
			{
				static void do_step(System& system, engine& engine)
				{
					system.do_step(engine.system_step_argument<Arguments>()...);
				}
			};

			template <typename System, typename... Arguments>
			stepper<System, Arguments...> select_stepper(void (System::*)(Arguments&...))
			{
				return {};
			}
		}

		template <typename System>
		void system<System>::do_step(engine& engine)
		{
			detail::select_stepper(&System::step).do_step(static_cast<System&>(*this), engine);
		}
	}
}

#ifndef BITSMITHERY_WINDOW_HPP
	#define BITSMITHERY_WINDOW_HPP

	#include <string>

	#include "event/origin.hpp"


	namespace bitsmithery
	{
		namespace detail
		{
			class window_implementation;
		}

		class window final
		{
			public:
				window() = default;
				window(window const& that) = delete;
				window& operator=(window const& that) = delete;
				virtual ~window() = default;

				static std::vector<utility::size<unsigned>> get_valid_fullscreen_sizes();

				struct invalid_fullscreen_size
					: public std::logic_error
				{
					invalid_fullscreen_size()
						: logic_error("invalid_fullscreen_size")
					{
					}
				};

				utility::size<unsigned> get_size();
				void set_size(utility::size<unsigned> const& new_size);
				event::origin<utility::size<unsigned>>& on_size_change();

				enum class state
				{
					windowed, fullscreen
 				};
				state get_state();
				void set_state(state new_state);
                event::origin<state>& on_state_change();

                std::shared_ptr<mouse> get_mouse_ptr();
                std::shared_ptr<keyboard> get_keyboard_ptr();
                std::shared_ptr<graphics::renderer> get_renderer_ptr();

			private:
				std::unique_ptr<detail::window_implementation> implementation;
		};
	}

#endif

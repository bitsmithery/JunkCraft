#ifndef APP_UI_HPP
	#define APP_UI_HPP

	#include <vector>
	#include <stdexcept>
	#include <string>

	#include "util/size.hpp"
	#include "event/origin.hpp"
	#include "util/point.hpp"
	#include "math/vector.hpp"

	namespace app
	{
		namespace ui
		{
			namespace window
			{
				std::vector<util::size<unsigned>> get_valid_fullscreen_sizes();

				struct invalid_fullscreen_size
					: public std::logic_error
				{
					invalid_fullscreen_size()
						: logic_error("invalid_fullscreen_size")
					{
					}
				};

				util::size<unsigned> get_size();
				void set_size(util::sizeu const& new_size);
				event::origin<util::size<unsigned>>& on_size_change();

				enum class state
				{
					windowed, fullscreen
 				};
				state get_state();
				void set_state(state new_state);
                event::origin<state>& on_state_change();

				void update();
			}

			namespace keyboard
			{
				event::origin<std::string>& on_key_press();
				event::origin<>& on_key_press(std::string const& key);
				event::origin<std::string>& on_key_release();
				event::origin<>& on_key_release(std::string const& key);

				event::origin<std::string>& on_text_input();
			}

			namespace mouse
			{
				event::origin<std::string>& on_button_press();
				event::origin<>& on_button_press(std::string const& button);
				event::origin<std::string>& on_button_release();
				event::origin<>& on_button_release(std::string const& button);

				event::origin<util::point<unsigned>>& on_enter();
				event::origin<math::vector<unsigned>>& on_move();
				event::origin<>& on_leave();

				event::origin<math::vector<float>>& on_scroll();
			}

			void dispatch_events();
		}
	}

	#include "ui.init.hpp"

#endif

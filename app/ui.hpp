#ifndef APP_UI_HPP
	#define APP_UI_HPP

	#include <vector>
	#include <stdexcept>
	#include <list>
	#include <unordered_map>
	#include <string>

	#include "util/size.hpp"

	namespace app
	{
		namespace ui
		{
			namespace window
			{
				std::vector<util::sizeu> get_valid_fullscreen_sizes();

				struct invalid_fullscreen_size
					: public std::logic_error
				{
					invalid_fullscreen_size()
						: logic_error("invalid_fullscreen_size")
					{
					}
				};

				util::sizeu get_size();
				void set_size(util::sizeu const& new_size);
				void on_size_change(std::function<bool(util::sizeu const& new_size)> const& handler);


				bool is_fullscreen();
				void set_fullscreen(bool new_fullscreen);
				void on_fullscreen_change(std::function<bool(bool new_fullscreen)> const& handler);

				void update();
			}

			namespace keyboard
			{
				bool is_key_pressed(std::string const& key);
				extern std::unordered_map<std::string, std::list<std::function<void()>>> on_key_press;
				extern std::unordered_map<std::string, std::list<std::function<void()>>> on_key_release;

				extern std::list<std::function<void(std::string const& text)>> on_text_input;
			}

			namespace mouse
			{
				bool is_button_pressed(std::string const& button);
				extern std::unordered_map<std::string, std::unordered_set<util::weak_function<void()>>> on_button_press;
				extern std::unordered_map<std::string, std::unordered_set<util::weak_function<void()>>> on_button_release;

				extern std::unordered_set<util::weak_function<void(util::pointu const& position)>> on_enter;
				extern std::unordered_set<util::weak_function<void(math::vectoru const& displacement)>> on_move;
				extern std::unordered_set<util::weak_function<void()>> on_leave;

				extern std::unordered_set<util::weak_function<void(float delta)>> on_scroll;
			}

			void dispatch_events();
		}
	}

	#include "ui.init.hpp"

#endif

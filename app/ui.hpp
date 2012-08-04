#ifndef APP_UI_HPP
	#define APP_UI_HPP

	#include <vector>
	#include <stdexcept>
	#include <functional>
	#include <map>
	#include <string>

	#include "util/size.hpp"
	#include "util/point.hpp"

	namespace app
	{
		namespace ui
		{
			namespace display
			{
				std::vector<util::sizeu> get_valid_sizes();

				class invalid_size
					: public std::logic_error
				{
					public:
						invalid_size()
							: logic_error("invalid_size")
						{
						}
				};

				namespace event
				{
					extern std::function<void(util::sizeu const& new_size)> size_change;
				}
				util::sizeu get_size();
				void set_size(util::sizeu const& new_size);

				void swap_buffers();
			}

			namespace keyboard
			{
				namespace event
				{
					extern std::map<std::string, std::function<void()>> key_press;
					extern std::map<std::string, std::function<void()>> key_release;
				}
				bool is_key_pressed(std::string const& key);

				namespace event
				{
					extern std::function<void(std::string const& text)> text_input;
				}
			}

			namespace mouse
			{
				namespace event
				{
					extern std::map<std::string, std::function<void()>> button_press;
					extern std::map<std::string, std::function<void()>> button_release;
				}
				bool is_button_pressed(std::string const& button);

				namespace event
				{
					extern std::function<void(util::pointu const& new_position)> position_change;
				}
				util::pointu get_position();
				void set_position(util::pointu const& new_position);

				namespace event
				{
					extern std::function<void(float delta)> scroll;
				}
			}

			bool dispatch_event();

			class initializer
			{
				public:
					initializer();
					initializer(initializer const& that) = delete;
					initializer& operator=(initializer const& that) = delete;
					initializer(initializer&& that) = delete;
					initializer& operator=(initializer&& that) = delete;
					~initializer();
			};
			static initializer const initializer_instance;
		}
	}

#endif // APP_UI_HPP

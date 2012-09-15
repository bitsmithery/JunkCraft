#ifndef BITSMITHERY_KEYBOARD_HPP
	#define BITSMITHERY_KEYBOARD_HPP

	#include <string>

	#include "event/origin.hpp"

	namespace bitsmithery
	{
		class keyboard
		{
			public:
				keyboard() = default;
				keyboard(keyboard const& that) = delete;
				keyboard& operator=(keyboard const& that) = delete;
				virtual ~keyboard() = default;

				event::origin<std::string>& on_key_press();
				event::origin<>& on_key_press(std::string const& key);
				event::origin<std::string>& on_key_release();
				event::origin<>& on_key_release(std::string const& key);

				event::origin<std::string>& on_text_input();
		};
	}

#endif

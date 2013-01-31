#ifndef BITSMITHERY_MOUSE_HPP
	#define BITSMITHERY_MOUSE_HPP

	#include <string>

	#include "event/origin.hpp"

	namespace bitsmithery
	{
		class mouse
		{
			public:
				mouse() = default;
				mouse(mouse const& that) = delete;
				mouse& operator=(mouse const& that) = delete;
				virtual ~mouse() = default;

				event::origin<std::string>& on_button_press();
				event::origin<>& on_button_press(std::string const& button);
				event::origin<std::string>& on_button_release();
				event::origin<>& on_button_release(std::string const& button);

				event::origin<utility::point<unsigned>>& on_enter();
				event::origin<math::vector<unsigned>>& on_move();
				event::origin<>& on_leave();

				event::origin<math::vector<float>>& on_scroll();
		};
	}

#endif

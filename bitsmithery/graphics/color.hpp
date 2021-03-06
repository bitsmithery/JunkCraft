#ifndef APP_GRAPHICS_COLOR_HPP
	#define APP_GRAPHICS_COLOR_HPP

	namespace app
	{
		namespace graphics
		{
			class color
			{
				public:
					float r, g, b, a;

					color() = default;
					color(color const&) = default;
					color(float r, float g, float b, float a = 1.0f);
					color& operator=(color const&) = default;
					~color() = default;
			};

			inline
			color::color(float r, float g, float b, float a)
				: r(r), g(g), b(b), a(a)
			{}
		}
	}

#endif

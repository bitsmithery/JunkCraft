#ifndef APP_GRAPHICS_GL_CONTEXT_INIT_HPP
	#define APP_GRAPHICS_GL_CONTEXT_INIT_HPP

	#include "../../ui.init.hpp"

	namespace app
	{
		namespace graphics
		{
			namespace gl
			{
				namespace context
				{
					static struct init {
						init();
						init(init const& that) = delete;
						init& operator=(init const& that) = delete;
						~init();
					} const init_instance;
				}
			}
		}
	}

#endif

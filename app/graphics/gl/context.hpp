#ifndef APP_GRAPHICS_GL_CONTEXT_HPP
	#define APP_GRAPHICS_GL_CONTEXT_HPP

	#include <gl/glew.h>
	#include <gl/gl.h>
	#include <gl/glext.h>
	#include <gl/glu.h>

	#include "../../ui.hpp"

	namespace app
	{
		namespace graphics
		{
			namespace gl
			{
				namespace context
				{
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
		}
	}

#endif

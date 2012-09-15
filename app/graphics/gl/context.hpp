#ifndef BITSMITHERY_GRAPHICS_GL_CONTEXT_HPP
	#define BITSMITHERY_GRAPHICS_GL_CONTEXT_HPP

	#include <functional>

	#include <GL/glew.h>
	#include <GL/gl.h>
	#include <GL/glext.h>
	#include <GL/glu.h>

	namespace bitsmithery
	{
		namespace graphics
		{
			namespace gl
			{
					// knows about underlying windowing system and context switching
				class context
				{
					public:
						context() = default;
						context(context const& that) = default;
						context& operator=(context const& that) = default;
						virtual ~context() = default;
				};
			}
		}
	}

#endif

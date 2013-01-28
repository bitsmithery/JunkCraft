#ifndef BITSMITHERY_GRAPHICS_GL_RENDER_HPP
	#define BITSMITHERY_GRAPHICS_GL_RENDER_HPP

	#include <functional>

	#include "context.hpp"
	#include "../scene.hpp"

	namespace bitsmithery
	{
		namespace graphics
		{
			namespace gl
			{
					//knows abput context and scene
				void render(std::shared_ptr<context> const& context_ptr, std::shared_ptr<scene> const& scene_ptr);
			}
		}
	}

#endif

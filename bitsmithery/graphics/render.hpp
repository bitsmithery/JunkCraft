#ifndef BITSMITHERY_GRAPHICS_RENDER_HPP
	#define BITSMITHERY_GRAPHICS_RENDER_HPP

	#include <functional>

	#include "context.hpp"
	#include "../scene.hpp"

	namespace bitsmithery
	{
		namespace graphics
		{
			void render(std::shared_ptr<context> const& context_ptr, std::shared_ptr<scene> const& scene_ptr);
		}
	}

#endif

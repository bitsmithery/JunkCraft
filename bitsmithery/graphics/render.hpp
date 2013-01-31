#ifndef BITSMITHERY_GRAPHICS_RENDERER_HPP
	#define BITSMITHERY_GRAPHICS_RENDERER_HPP

	#include "../scene.hpp"

	namespace bitsmithery
	{
		namespace graphics
		{
				// knows how to render a scene. obtained from rendering context (e.g. a window) all rendering code is therefore
				// an implementation detail of specific platform
			class renderer
			{
				public:
					renderer() = default;
					renderer(renderer const& that) = delete;
					renderer& operator=(renderer const& that) = delete;
					virtual ~renderer() = default;

					virtual void render(scene const& scene) = 0;
			};
		}
	}

#endif

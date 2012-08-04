#include <stdexcept>

#include "context.hpp"

namespace app
{
	namespace graphics
	{
		namespace gl
		{
			namespace context
			{
				static unsigned initialization_count = 0;

				initializer::initializer()
				{
					if (initialization_count++ == 0)
						if (glewInit() != GLEW_OK)
							throw std::runtime_error("Failed to initialize GLEW.");
				}

				initializer::~initializer()
				{
					if (--initialization_count == 0)
						; // do nothing, glew does not require deinitialization
				}
			}
		}
	}
}

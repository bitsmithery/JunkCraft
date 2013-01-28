#ifdef BITSMITHERY_WINDOWING_SYSTEM

	#define BITSMITHERY_WINDOW_STRINGIFY_TOKEN_IMPL(token) #token
	#define BITSMITHERY_WINDOW_STRINGIFY_TOKEN(token) BITSMITHERY_WINDOW_STRINGIFY_TOKEN_IMPL(token)

	#include BITSMITHERY_WINDOW_STRINGIFY_TOKEN(window.BITSMITHERY_WINDOWING_SYSTEM.impl)

	#undef BITSMITHERY_WINDOW_STRINGIFY_TOKEN
	#undef BITSMITHERY_WINDOW_STRINGIFY_TOKEN_IMPL

#else

	#error "BITSMITHERY_WINDOWING_SYSTEM is not defined."

#endif
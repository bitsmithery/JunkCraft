#ifndef BITSMITHERY_ASPECT_HPP
	#define BITSMITHERY_ASPECT_HPP

	namespace bitsmithery
	{
		class aspect
		{
			protected:
				aspect() = default;
				aspect(aspect const& that) = delete;
				aspect& operator=(aspect const& that) = delete;
				aspect(aspect&& that) = default;
				aspect& operator=(aspect&& that) = default;
				~aspect() = default;
		};
	}

#endif

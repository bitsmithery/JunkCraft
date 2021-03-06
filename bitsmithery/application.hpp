#ifndef BITSMITHERY_APPLICATION_HPP
	#define BITSMITHERY_APPLICATION_HPP

	namespace bitsmithery
	{
		class application
		{
			public:
				application(int argc, char* argv[]);
				application(application const& that) = delete;
				application& operator=(application const& that) = delete;
				virtual ~application() = default;

				virtual int run() = 0;
		};
	}

#endif

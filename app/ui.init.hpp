#ifndef APP_UI_INIT_HPP
	#define APP_UI_INIT_HPP

	namespace app
	{
		namespace ui
		{
			static struct init {
				init();
				init(init const& that) = delete;
				init& operator=(init const& that) = delete;
				~init();
			} const init_instance;
		}
	}

#endif

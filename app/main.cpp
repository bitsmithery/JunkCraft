#include "main.hpp"

namespace app
{
	static int main(int argc, char* argv[])
	{
		main({argv, argv + argc});
		return 0;
	}
}

int main(int argc, char* argv[])
{
	return app::main(argc, argv);
}

#include "application.hpp"

int main(int argc, char* argv[])
{
	bitsmithery::application application(argc, argv);
	application.run();
	return application.result();
}

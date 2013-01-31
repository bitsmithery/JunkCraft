#include "core/system.hpp"
#include "core/engine.hpp"
#include "util/thread_pool.hpp"

#include "application.hpp"

int main(int argc, char* argv[])
{
	return bitsmithery::application(argc, argv).run();
}

//#include <thread>
//
//#include "thread_pool.hpp"
//
//namespace bitsmithery
//{
//	namespace utility
//	{
//		namespace detail
//		{
//			void thread_function(std::shared_ptr<thread_pool_state> state) {
//				while (true) {
//					std::unique_lock<std::mutex> tasks_lock(state->tasks_mutex, std::defer_lock);
//					tasks_lock.lock();
//					while (state->tasks.empty()) {
//						state->tasks_pending.wait(tasks_lock);
//					}
//					auto task = std::move(state->tasks.front());
//					state->tasks.pop_front();
//					tasks_lock.unlock();
//					task->execute();
//				}
//			}
//		}
//
//		thread_pool::thread_pool()
//			: state(new detail::thread_pool_state)
//		{
//			auto thread_count = std::thread::hardware_concurrency();
//			for (auto thread_index = 0; thread_index < thread_count; ++thread_index) {
//				std::thread(detail::thread_function, state).detach();
//			}
//		}
//	}
//}

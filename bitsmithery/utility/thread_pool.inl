#include <utility>
#include <cassert>

namespace bitsmithery
{
	namespace utility
	{
		namespace detail
		{
			template <typename Task>
			class thread_pool_task final
				: public thread_pool_task_base
			{
				public:
					thread_pool_task(Task&& task);
					thread_pool_task(thread_pool_task const& that) = delete;
					thread_pool_task& operator=(thread_pool_task const& that) = delete;
					virtual ~thread_pool_task() override = default;

				private:
					Task task;

					virtual void execute() noexcept override;
			};

			template <typename Task>
			thread_pool_task<Task>::thread_pool_task(Task&& task)
				: task(std::forward<Task>(task))
			{}

			template <typename Task>
			void thread_pool_task<Task>::execute()
			{
				task();
			}
		}

		template <typename Task>
		thread_pool& thread_pool::operator<<(Task&& task)
		{
			std::unique_lock<std::mutex> tasks_lock(state->tasks_mutex);
			state->tasks.emplace_back(new detail::thread_pool_task<Task>(std::forward<Task>(task)));
			state->tasks_pending.notify_one();
			return *this;
		}
	}
}

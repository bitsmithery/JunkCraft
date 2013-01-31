#ifndef BITSMITHERY_UTIL_THREAD_POOL_HPP
	#define BITSMITHERY_UTIL_THREAD_POOL_HPP

	#include <list>
	#include <memory>
	#include <mutex>
	#include <condition_variable>

	namespace bitsmithery
	{
		namespace utility
		{
			class thread_pool;

			namespace detail
			{
				class thread_pool_task_base
				{
					friend class thread_pool;
					public:
						thread_pool_task_base() = default;
						thread_pool_task_base(thread_pool_task_base const& that) = delete;
						thread_pool_task_base& operator=(thread_pool_task_base const& that) = delete;
						virtual ~thread_pool_task_base() = default;

					private:
						virtual void execute() noexcept = 0;
				};

				struct thread_pool_state
				{
					std::list<std::unique_ptr<detail::thread_pool_task_base>> tasks;
					std::mutex tasks_mutex;
					std::condition_variable tasks_pending;
				};
			}

//			class thread_pool_task_failure_try_later final
//				: public std::exception
//			{
//				public:
//					thread_pool_task_failure_try_later() noexcept = default;
//					thread_pool_task_failure_try_later(thread_pool_task_failure_try_later const& that) noexcept = default;
//					thread_pool_task_failure_try_later& operator=(thread_pool_task_failure_try_later const& that) noexcept = default;
//					virtual ~thread_pool_task_failure_try_later() noexcept override = default;
//
//					virtual char const* what() const noexcept override;
//			};

			class thread_pool
			{
				public:
					thread_pool();
					thread_pool(thread_pool const& that) = delete;
					thread_pool(thread_pool&& that);
					thread_pool& operator=(thread_pool const& that) = delete;
					thread_pool& operator=(thread_pool&& that);
					~thread_pool() = default;

					template <typename Task>
					thread_pool& operator<<(Task&& task);

				private:
					std::shared_ptr<detail::thread_pool_state> state;
			};
		}
	}

	#include "thread_pool.inl"

#endif

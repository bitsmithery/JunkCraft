#ifndef BITSMITHERY_UTILITY_WORKER_HPP
	#define BITSMITHERY_UTILITY_WORKER_HPP

	namespace bitsmithery
	{
		namespace utility
		{
			class worker;

			namespace detail
			{
				class worker_task_base
				{
					friend class worker;
					public:
						worker_task_base() = default;
						worker_task_base(worker_task_base const& that) = delete;
						worker_task_base& operator=(worker_task_base const& that) = delete;
						virtual ~worker_task_base() = default;

					private:
						virtual void execute() noexcept = 0;
				};
			}

			class worker
			{
				public:
					worker() = default;
					worker(worker const& that) = delete;
					worker& operator=(worker const& that) = delete;
					~worker() = default;

				private:
					std::queue<std::unique_ptr<detail::worker_task_base>> tasks;
					std::mutex tasks_mutex;
			};
		}
	}

#endif

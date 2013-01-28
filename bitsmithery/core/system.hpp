#ifndef BITSMITHERY_CORE_SYSTEM_HPP
	#define BITSMITHERY_CORE_SYSTEM_HPP

	#include <unordered_set>
	#include <typeindex>
	#include <type_traits>

	namespace bitsmithery
	{
		namespace core
		{
			class engine;

			template <typename System>
			class system;

			namespace detail
			{
				class system_base
				{
					friend class engine;
					template <typename System>
					friend class system;
					public:
						system_base() = default;
						system_base(system_base const&) = delete;
						system_base(system_base&&) = default;
						system_base& operator=(system_base const&) = delete;
						system_base& operator=(system_base&&) = default;
						virtual ~system_base() = default;

					protected:
						double step_time_last;
						double step_time_this;
						double step_time_next;

					private:
						std::unordered_set<std::type_index> signature;
						std::unordered_set<std::type_index> signature_const;
						virtual void do_step(engine& engine) = 0;
				};
			}

			template <typename System>
			class system
				: public detail::system_base
			{
				protected:
					system();
					system(system const& that) = delete;
					system(system&& that) = default;
					system& operator=(system const& that) = delete;
					system& operator=(system&& that) = default;
					~system() = default;

				private:
					void do_step(engine& engine) override final;
			};

			template <typename Type>
			struct is_system
				: std::integral_constant<bool, std::is_base_of<Type, system<Type>>::value && !std::is_same<Type, system<Type>>::value>
			{};
		}
	}

	#include "system.inl"

#endif

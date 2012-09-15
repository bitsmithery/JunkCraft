#ifndef APP_UTIL_CACHE_HPP
	#define APP_UTIL_CACHE_HPP

	#include <memory>
	#include <map>
	#include <cstdint>
	#include <type_traits>

	namespace bitsmithery
	{
		namespace util
		{
			namespace detail
			{
				namespace cache
				{
					template <typename Type, typename... Arguments>
					class storage;

					template <typename Type, typename... Arguments>
					class storage<Type(Arguments...)>
						: public std::enable_shared_from_this<storage<Type(Arguments...)>>
					{
						public:
							storage() = default;
							storage(storage const& that) = delete;
							storage& operator=(storage const& that) = delete;
							storage(storage&& that) = delete;
							storage& operator=(storage&& that) = delete;
							~storage() = default;

							std::shared_ptr<Type const> get(Arguments const&... arguments);

						private:
							std::map<std::tuple<Arguments...>, std::weak_ptr<Type const>> objects;
					};

					template <typename Type>
					class storage<Type>
						: public std::enable_shared_from_this<storage<Type>>
					{
						public:
							storage() = default;
							storage(storage const& that) = delete;
							storage& operator=(storage const& that) = delete;
							storage(storage&& that) = delete;
							storage& operator=(storage&& that) = delete;
							~storage() = default;

							template <typename... Arguments>
							std::shared_ptr<Type const> get(Arguments const&... arguments);

						private:
							std::map<std::uintptr_t, std::weak_ptr<void>> substorages;
					};
				}
			}

			template <typename Type, typename... Arguments>
			class cache;

			template <typename Type, typename... Arguments>
			class cache<Type(Arguments...)>
			{
				public:
					cache() = default;
					cache(cache const& that) = delete;
					cache& operator=(cache const& that) = delete;
					cache(cache&& that) = default;
					cache& operator=(cache&& that) = default;
					~cache() noexcept = default;

					std::shared_ptr<Type const> get(Arguments const&... arguments);

				private:
					std::weak_ptr<detail::cache::storage<Type(Arguments...)>> storage_ptr;
			};

			template <typename Type>
			class cache<Type>
			{
				public:
					cache() = default;
					cache(cache const& that) = delete;
					cache& operator=(cache const& that) = delete;
					cache(cache&& that) = default;
					cache& operator=(cache&& that) = default;
					~cache() noexcept = default;

					template <typename... Arguments>
					std::shared_ptr<Type const> get(typename std::common_type<Arguments>::type const&... arguments);

				private:
					std::weak_ptr<detail::cache::storage<Type>> storage_ptr;
			};
		}
	}

	#include "cache.inl"

#endif // APP_UTIL_CACHE_HPP

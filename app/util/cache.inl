#include <tuple>

namespace bitsmithery
{
	namespace util
	{
		namespace detail
		{
			namespace cache
			{
				template <typename... Arguments>
				inline
				std::uintptr_t storage_id()
				{
					static char const dummy = '\0';
					return reinterpret_cast<std::uintptr_t>(&dummy);
				}

				template <typename Type, typename... Arguments>
				std::shared_ptr<Type const> storage<Type(Arguments...)>::get(Arguments const&... arguments)
				{
					// TODO: when mutexes are implemented remove this loop and add proper lock/erase/unlock to deleter
					for (auto it = objects.begin(); it != objects.end(); (it->second.lock() == nullptr) ? (it = objects.erase(it)) : (++it));

					auto key = std::tuple<Arguments...>(arguments...);
					auto value = objects[key].lock();
					if (value != nullptr)
						return value;
					auto storage_ptr = this->shared_from_this();
					auto object_it = objects.find(key);
					auto deleter = [storage_ptr, object_it](Type* ptr) mutable
					{
						delete ptr;
							// appearantely deleter (and by extension storage_ptr) lives as long as state shared by shared_ptr and weak_ptr lives,
							// thus forming circular dependency, so we have to explicitely reset it
						storage_ptr.reset();
					};
					value.reset(new Type(arguments...), deleter);
					object_it->second = value;
					return value;
				}

				template <typename Type>
				template <typename... Arguments>
				std::shared_ptr<Type const> storage<Type>::get(Arguments const&... arguments)
				{
					// TODO: when mutexes are implemented remove this loop and add proper lock/erase/unlock to deleter
					for (auto it = substorages.begin(); it != substorages.end(); (it->second.lock() == nullptr) ? (it = substorages.erase(it)) : (++it));

					auto key = storage_id<Arguments...>();
					auto value = std::static_pointer_cast<storage<Type(Arguments...)>>(substorages[key].lock());
					if (value != nullptr)
						return value->get(arguments...);
					auto storage_ptr = this->shared_from_this();
					auto substorage_it = substorages.find(key);
					auto deleter = [storage_ptr, substorage_it](storage<Type(Arguments...)>* ptr) mutable
					{
						delete ptr;
							// appearantely deleter (and by extension storage_ptr) lives as long as state shared by shared_ptr and weak_ptr lives,
							// thus forming circular dependency, so we have to explicitely reset it
						storage_ptr.reset();
					};
					value.reset(new storage<Type(Arguments...)>, deleter);
					substorage_it->second = value;
					return value->get(arguments...);
				}
			}
		}

		template <typename Type, typename... Arguments>
		std::shared_ptr<Type const> cache<Type(Arguments...)>::get(Arguments const&... arguments)
		{
			auto storage_ptr = this->storage_ptr.lock();
			if (storage_ptr == nullptr)
			{
				storage_ptr.reset(new detail::cache::storage<Type(Arguments...)>);
				this->storage_ptr = storage_ptr;
			}
			return storage_ptr->get(arguments...);
		}

		template <typename Type>
		template <typename... Arguments>
		std::shared_ptr<Type const> cache<Type>::get(typename std::common_type<Arguments>::type const&... arguments)
		{
			auto storage_ptr = this->storage_ptr.lock();
			if (storage_ptr == nullptr)
			{
				storage_ptr.reset(new detail::cache::storage<Type>);
				this->storage_ptr = storage_ptr;
			}
			return storage_ptr->get(arguments...);
		}
	}
}

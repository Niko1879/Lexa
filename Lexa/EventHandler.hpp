#pragma once

#include <vector>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <string>
#include <memory>


namespace Lexa
{
	template<class... Args>
	class EventHandler
	{
	public:
		using CallbackType = std::function<void(Args...)>;

		static EventHandler<Args...>& Instance(const std::string& inst)
		{
			static std::unordered_map<std::string, std::unique_ptr<EventHandler<Args...>>> instances;
			if (instances.find(inst) == instances.end())
			{
				std::unique_ptr<EventHandler<Args...>> p(new EventHandler<Args...>());
				instances.insert(std::make_pair(inst, std::move(p)));
			}
			
			return *instances.at(inst).get();
		}

		void operator()(Args... args)
		{
			for (Handler& c : m_callbacks)
				c.f(std::forward<Args>(args)...);
		}

		int Register(CallbackType c)
		{
			int id;
			if (m_releasedIds.size() > 0)
			{
				id = m_releasedIds.back();
				m_releasedIds.pop_back();
			}

			else
			{
				id = m_id++;
			}

			m_callbacks.push_back(Handler{ id, c });
			return id;
		}

		void Deregister(int id)
		{
			std::remove_if(m_callbacks.begin().m_callbacks.end(), [](Handler& c) {c.id == id; });
		}

	private:
		EventHandler() : m_id(1) {}

		EventHandler(const EventHandler<Args...>&) = delete;

		EventHandler(EventHandler<Args...>&&) = delete;

		EventHandler<Args...>& operator=(const EventHandler<Args...>&) = delete;

		EventHandler<Args...>& operator=(EventHandler<Args...>&&) = delete;

		struct Handler
		{
			int id;
			CallbackType f;
		};

		std::vector<Handler> m_callbacks;
		std::vector<int> m_releasedIds;
		int m_id;
	};

}


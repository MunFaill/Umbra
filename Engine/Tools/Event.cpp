#include "Tools/Event.hpp"

#include <print>

namespace Engine {
    template<class... ArgTypes>
    ListenerID Event<ArgTypes...>::AddListener(Callback callback) {
        ListenerID listener = m_AvaliableListenerID++;
        m_Callbacks.emplace(listener, callback);
		std::print("New listener added: {}\n", listener);
        return listener;
    }

    template<class... ArgTypes>
    ListenerID Event<ArgTypes...>::operator+=(Callback callback) {
        return AddListener(callback);
    }

	template<class... ArgTypes>
	bool Event<ArgTypes...>::RemoveListener(ListenerID listener)
	{
		std::print("Listener removed: {}\n", listener);
		return m_Callbacks.erase(listener) != 0;
	}

    	template<class... ArgTypes>
	bool Event<ArgTypes...>::operator-=(ListenerID listener)
	{
		return RemoveListener(listener);
	}

	template<class... ArgTypes>
	void Event<ArgTypes...>::RemoveAllListeners()
	{
		std::print("Listeners removed\n");
		m_Callbacks.clear();
	}

	template<class... ArgTypes>
	uint64_t Event<ArgTypes...>::GetListenerCount()
	{
		std::print("Number of listeners: {}\n", m_Callbacks.size());
		return m_Callbacks.size();
	}

	template<class... ArgTypes>
	void Event<ArgTypes...>::Invoke(ArgTypes... args)
	{
		for (auto const& [key, value] : m_Callbacks)
			value(args...);
	}
}
#include "Tools/Event.hpp"

namespace Engine {
    template<class... ArgTypes>
    ListenerID Event<ArgTypes...>::AddListener(Callback callback) {
        ListenerID listener = m_AvaliableListenerID++;
        m_Callbacks.emplace(listener, callback);
        return listener;
    }

    template<class... ArgTypes>
    ListenerID Event<ArgTypes...>::operator+=(Callback callback) {
        return AddListener(callback);
    }

	template<class... ArgTypes>
	bool Event<ArgTypes...>::RemoveListener(ListenerID listenerID)
	{
		return m_Callbacks.erase(listenerID) != 0;
	}

    	template<class... ArgTypes>
	bool Event<ArgTypes...>::operator-=(ListenerID p_listenerID)
	{
		return RemoveListener(p_listenerID);
	}

	template<class... ArgTypes>
	void Event<ArgTypes...>::RemoveAllListeners()
	{
		m_Callbacks.clear();
	}

	template<class... ArgTypes>
	uint64_t Event<ArgTypes...>::GetListenerCount()
	{
		return m_Callbacks.size();
	}

	template<class... ArgTypes>
	void Event<ArgTypes...>::Invoke(ArgTypes... args)
	{
		for (auto const& [key, value] : m_Callbacks)
			value(args...);
	}
}
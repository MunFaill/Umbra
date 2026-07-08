#pragma once

#include "Tools/Log.hpp"

#include <cstdint>
#include <functional>
#include <unordered_map>

namespace Engine {
    typedef uint64_t ListenerID;

    template<class... ArgTypes>
    class Event {
        public:
            typedef std::function<void(ArgTypes...)> Callback;
            
            inline ListenerID AddListener(Callback callback) {
                ListenerID listener = m_AvaliableListenerID++;
                m_Callbacks.emplace(listener, callback);
                Print("New listener added: {}", listener);
                return listener;
            }

            inline ListenerID operator+=(Callback callback) {
                return AddListener(callback);
            }

            inline bool RemoveListener(ListenerID listener)
            {
                Print("Listener removed: {}", listener);
                return m_Callbacks.erase(listener) != 0;
            }

            inline bool operator-=(ListenerID listener)
            {
                return RemoveListener(listener);
            }

            inline void RemoveAllListeners()
            {
                Print("Listeners removed");
                m_Callbacks.clear();
            }

            inline uint64_t GetListenerCount()
            {
                Print("Number of listeners: {}", m_Callbacks.size());
                return m_Callbacks.size();
            }

            inline void Invoke(ArgTypes... args)
            {
                for (auto const& [key, value] : m_Callbacks)
                    value(args...);
            }
        private:
            std::unordered_map<ListenerID, Callback> m_Callbacks;
            ListenerID m_AvaliableListenerID = 0;
    };
    
    struct Events {
        inline static Event<unsigned int, unsigned int> OnWindowResize;
    };
}
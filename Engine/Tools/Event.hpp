#pragma once

#include <cstdint>
#include <functional>
#include <print>
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
                std::println("New listener added: {}", listener);
                return listener;
            }

            inline ListenerID operator+=(Callback callback) {
                return AddListener(callback);
            }

            inline bool RemoveListener(ListenerID listener)
            {
                std::println("Listener removed: {}", listener);
                return m_Callbacks.erase(listener) != 0;
            }

            inline bool operator-=(ListenerID listener)
            {
                return RemoveListener(listener);
            }

            inline void RemoveAllListeners()
            {
                std::println("Listeners removed");
                m_Callbacks.clear();
            }

            inline uint64_t GetListenerCount()
            {
                std::println("Number of listeners: {}", m_Callbacks.size());
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
        inline static Event<> OnInit;
        inline static Event<float> OnUpdate;
        inline static Event<unsigned int, unsigned int> OnWindowResize;
    };
}
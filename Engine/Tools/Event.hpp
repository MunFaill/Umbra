#pragma once

#include <cstdint>
#include <functional>

namespace Engine {
    typedef uint64_t ListenerID;

    template<class... ArgTypes>
    class Event {
        public:
            typedef std::function<void(ArgTypes...)> Callback;
            ListenerID AddListener(Callback callback);
            ListenerID operator+=(Callback callback);
            bool RemoveListener(ListenerID listener);
            bool operator-=(ListenerID listener);
            void RemoveAllListeners();
            uint64_t GetListenerCount();
            void Invoke(ArgTypes... args);
        private:
            std::unordered_map<ListenerID, Callback> m_Callbacks;
            ListenerID m_AvaliableListenerID = 0;
    };
    
    struct Events {
        static Event<> OnInit;
        static Event<float> OnUpdate;
        static Event<unsigned int, unsigned int> OnWindowResize;
    };
}
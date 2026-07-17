#pragma once

#include <format>
#include <print>
#include <utility>

namespace Engine {

    inline const char* RESET = "\033[0m";
    inline const char* BLUE = "\033[34m";
    inline const char* YELLOW = "\033[33m";
    inline const char* RED = "\033[31m";

    enum LogType {
        Message = 0, Warning = 1, Error = 2
    };

    template<typename... Args>
    inline void Print(LogType type, std::format_string<Args...> message, Args&&... args)
    {
    #ifdef Debug

        std::string formatted_user_msg = std::format(message, std::forward<Args>(args)...);

        switch (type) {
            case Message:
                std::println("{}{}{}", BLUE, formatted_user_msg, RESET);
                break;
            case Warning:
                std::println("{}{}{}", YELLOW, formatted_user_msg, RESET);
                break;
            case Error:
                std::println("{}{}{}", RED, formatted_user_msg, RESET);
                break;
        }
    #endif
    }

}
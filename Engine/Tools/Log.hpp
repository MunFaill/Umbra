#pragma once

#include <format>
#include <print>
#include <utility>

namespace Engine {

template<typename... Args>
inline void Print(std::format_string<Args...> message, Args&&... args)
{
#ifdef Debug
    std::println(message, std::forward<Args>(args)...);
#endif
}

}
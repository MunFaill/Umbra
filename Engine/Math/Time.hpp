#pragma once

#include <chrono>

typedef std::chrono::time_point<std::chrono::steady_clock> TPoint;

class Time {
    public:
        inline static void InitTime() {
            LastTime = std::chrono::steady_clock::now();
        }
        inline static void CalculateTime() {
            TPoint CurrentTime = std::chrono::steady_clock::now();
            std::chrono::duration<float> elapsedTime = CurrentTime - LastTime;
            DeltaTime = elapsedTime.count();
            LastTime = CurrentTime;
        }
        inline static float DeltaTime;
    private:
        inline static TPoint LastTime;
};
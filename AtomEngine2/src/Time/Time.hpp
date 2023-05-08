#pragma once

#include <chrono>
#include <ctime>

namespace atom
{
    class Time
    {
    private:
        static float elapsedTime;
        static std::chrono::time_point<std::chrono::system_clock> time1;
        static std::chrono::time_point<std::chrono::system_clock> time2;

    public:
        static float timeScale;

        static void Init();
        static void Update();

        static float DeltaTime();
        static float ElapsedTime();

        static time_t GetTime();
    };
}

#include "Time.hpp"
#include <Debug/Log.hpp>

namespace atom
{
    float Time::elapsedTime = 0.0f;
    float Time::timeScale = 1.0f;
    std::chrono::time_point<std::chrono::system_clock> Time::time1;
    std::chrono::time_point<std::chrono::system_clock> Time::time2;

    void Time::Init()
    {
        time1 = time2 = std::chrono::system_clock::now();

        ATOM_CORE_LOG("[Atom]: Time subsystem initialized\n");
    }

    void Time::Update()
    {
        time2 = std::chrono::system_clock::now();
        std::chrono::duration<float> time = time2 - time1;
        elapsedTime = time.count();
        time1 = time2;
    }

    float Time::DeltaTime()
    {
        return elapsedTime * timeScale;
    }

    float Time::ElapsedTime()
    {
        return elapsedTime;
    }

    time_t Time::GetTime()
    {
        return time(nullptr);
    }
}

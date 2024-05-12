#ifndef TIME_H
#define TIME_H

#include <chrono>
#include <string>

class RoboimeTime
{
public:
    constexpr RoboimeTime()
        : timePoint{std::chrono::nanoseconds(0)}
        {};
    explicit RoboimeTime(std::chrono::high_resolution_clock::duration duration);
    explicit RoboimeTime(double seconds);
    explicit RoboimeTime(long nanoseconds) : timePoint{std::chrono::nanoseconds(nanoseconds)} {};
    static RoboimeTime now();


private:
    std::chrono::high_resolution_clock::duration timePoint;
};

#endif // TIME_H

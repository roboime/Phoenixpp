#ifndef TIME_H
#define TIME_H

#include <chrono>
#include <ctime>
#include <string>

class Time
{
public:
    constexpr Time()
        : timePoint{std::chrono::nanoseconds(0)}
        {};
    explicit Time(std::chrono::high_resolution_clock::duration duration);
    explicit Time(double seconds);
    explicit Time(long nanoseconds) : timePoint{std::chrono::nanoseconds(nanoseconds)} {};
    static Time now();


private:
    std::chrono::high_resolution_clock::duration timePoint;
};

#endif // TIME_H

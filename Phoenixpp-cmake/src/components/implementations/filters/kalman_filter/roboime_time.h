#ifndef ROBOIMETIME_H
#define ROBOIMETIME_H

#include <chrono>

class RoboimeTime
{
public:
    constexpr RoboimeTime()
        : timePoint{std::chrono::nanoseconds(0)}
        {};
    explicit RoboimeTime(std::chrono::high_resolution_clock::duration duration);
    explicit RoboimeTime(double seconds);
    explicit RoboimeTime(long nanoseconds);
    static RoboimeTime now();
    [[nodiscard]] long asNanoseconds() const;
    [[nodiscard]] double asSeconds() const;

    RoboimeTime operator+(const RoboimeTime &other) const;
    RoboimeTime operator-(const RoboimeTime &other) const;
    RoboimeTime &operator-=(const RoboimeTime &other);
    RoboimeTime &operator+=(const RoboimeTime &other);
    bool operator>(const RoboimeTime &other) const;
    bool operator>=(const RoboimeTime &other) const;
    bool operator<(const RoboimeTime &other) const;
    bool operator<=(const RoboimeTime &other) const;
    bool operator==(const RoboimeTime &other) const;
    bool operator!=(const RoboimeTime &other) const;


private:
    std::chrono::high_resolution_clock::duration timePoint;


};

#endif // ROBOIMETIME_H

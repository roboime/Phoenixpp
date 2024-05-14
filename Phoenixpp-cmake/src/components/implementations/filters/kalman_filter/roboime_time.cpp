#include "roboime_time.h"
#include <cmath>

RoboimeTime::RoboimeTime(std::chrono::nanoseconds time) : timePoint{time} {}

RoboimeTime RoboimeTime::now()
{
    return RoboimeTime(std::chrono::system_clock::now().time_since_epoch());
}

long RoboimeTime::asNanoseconds() const
{
    return std::chrono::duration<long, std::nano>(timePoint).count();
}

double RoboimeTime::asSeconds() const
{
    return std::chrono::duration<double>(timePoint).count();
}

RoboimeTime::RoboimeTime(double seconds)
    : timePoint{std::chrono::nanoseconds((long)std::round(seconds * 1e9))} {};

RoboimeTime::RoboimeTime(long nanoseconds)
    : timePoint{std::chrono::nanoseconds(nanoseconds)} {};

RoboimeTime RoboimeTime::operator+(const RoboimeTime &other) const { return RoboimeTime(timePoint + other.timePoint); }

RoboimeTime RoboimeTime::operator-(const RoboimeTime &other) const { return RoboimeTime(timePoint - other.timePoint); }

RoboimeTime &RoboimeTime::operator-=(const RoboimeTime &other) {
    timePoint -= other.timePoint;
    return *this;
}

RoboimeTime &RoboimeTime::operator+=(const RoboimeTime &other) {
    timePoint += other.timePoint;
    return *this;
}

bool RoboimeTime::operator>(const RoboimeTime &other) const { return timePoint > other.timePoint; }

bool RoboimeTime::operator>=(const RoboimeTime &other) const { return timePoint >= other.timePoint; }

bool RoboimeTime::operator<=(const RoboimeTime &other) const { return timePoint <= other.timePoint; }

bool RoboimeTime::operator<(const RoboimeTime &other) const { return timePoint < other.timePoint; }

bool RoboimeTime::operator==(const RoboimeTime &other) const { return timePoint == other.timePoint; }

bool RoboimeTime::operator!=(const RoboimeTime &other) const { return timePoint != other.timePoint; }


//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_TIMEUNIT_HPP
#define OKHTTPFORK_TIMEUNIT_HPP

#include <string>
#include <ctime>
#include "Config.hpp"

namespace ohf {
    class TimeUnit {
    public:
        enum class Type {
            SECONDS,
            MILLISECONDS,
            MICROSECONDS
        };

        static const TimeUnit ZERO;
        static const TimeUnit MINUS_ONE_SECOND;

        static TimeUnit seconds(float time);
        static TimeUnit milliseconds(Int32 time);
        static TimeUnit microseconds(Int64 time);

        TimeUnit(Int64 count, const TimeUnit::Type &type);

        std::time_t std_time() const;

        float seconds() const;
        Int32 milliseconds() const;
        Int64 microseconds() const;

        // for timeval
        long sec() const;
        long usec() const;

        // automatic conversion
        Int64 value() const;
        std::string toString() const;

        bool operator ==(const TimeUnit &right) const;
        bool operator !=(const TimeUnit &right) const;
        bool operator >=(const TimeUnit &right) const;
        bool operator <=(const TimeUnit &right) const;
        bool operator >(const TimeUnit &right) const;
        bool operator <(const TimeUnit &right) const;

        TimeUnit operator +(const TimeUnit &right) const;
        TimeUnit operator -(const TimeUnit &right) const;
        TimeUnit operator *(const TimeUnit &right) const;
        TimeUnit operator /(const TimeUnit &right) const;
        TimeUnit operator ^(const TimeUnit &right) const;
    private:
        TimeUnit(float seconds);

        Type mType;
        std::time_t mTime; // 2036
        Int64 mMicroseconds;
        long mSec;
        long mUSec;
    };
}

#endif //OKHTTPFORK_TIMEUNIT_HPP

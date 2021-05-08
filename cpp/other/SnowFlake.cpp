#include <iostream>
#ifdef WINDOWS
#include <ctime>
#include <windows.h>
#else
#include <sys/time.h>
#endif
using namespace std;

class SnowFlake {
public:
    SnowFlake(int dataCenterId, int workerId) : startTimeStamp(1356019200000L), timeStamp(0), dataCenterId(dataCenterId), workerId(workerId), sequence(0) {}

    long long uuid() {
        long long tick = getTick();
        if (tick < timeStamp) {
            return INT_MIN;
        }

        if (tick == timeStamp) {
            sequence = (sequence + 1) & (~(-1 << 12));
            if (!sequence) {
                while (tick == timeStamp) {
                    tick = getTick();
                }
            }
        } else {
            sequence = 0;
        }
        timeStamp = tick;
        return ((tick - startTimeStamp) << 22) | (dataCenterId << 17) | (workerId << 12) | sequence;
    }

private:
    const long long startTimeStamp;

    long long timeStamp;
    int dataCenterId;
    int workerId;
    int sequence;

    long long getTick() {
#ifdef WINDOWS
        SYSTEMTIME localTime;
        GetLocalTime(&localTime);

        struct tm time;
        time.tm_year = localTime.wYear - 1900;
        time.tm_mon = localTime.wMonth - 1;
        time.tm_mday = localTime.wDay;
        time.tm_hour = localTime.wHour;
        time.tm_min = localTime.wMinute;
        time.tm_sec = localTime.wSecond;
        return mktime(&time) * 1000 + localTime.wMilliseconds;
#else
        struct timeval time;
        gettimeofday(&time, nullptr);
        return time.tv_sec * 1000 + time.tv_usec / 1000;
#endif
    }
};

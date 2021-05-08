#include <stdio.h>
#ifdef WINDOWS
#include <time.h>
#include <windows.h>
#else
#include <sys/time.h>
#endif

typedef struct {
    long long timeStamp;
    int dataCenterId;
    int workerId;
    int sequence;
} SnowFlakeNode;

static const long long startTimeStamp = 1356019200000L;

static long long getTick();

void create(SnowFlakeNode *node, int dataCenterId, int workerId) {
    node->timeStamp = 0;
    node->dataCenterId = dataCenterId;
    node->workerId = workerId;
    node->sequence = 0;
}

long long uuid(SnowFlakeNode *node) {
    long long tick = getTick();
    if (tick < node->timeStamp) {
        return 1 << 31;
    }

    if (tick == node->timeStamp) {
        node->sequence = (node->sequence + 1) & (~(-1 << 12));
        if (!node->sequence) {
            while (tick == node->timeStamp) {
                tick = getTick();
            }
        }
    } else {
        node->sequence = 0;
    }
    node->timeStamp = tick;
    return ((tick - startTimeStamp) << 22) | (node->dataCenterId << 17) | (node->workerId << 12) | node->sequence;
}

static long long getTick() {
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
    return (long long) mktime(&time) * 1000 + localTime.wMilliseconds;
#else
    struct timeval time;
    gettimeofday(&time, NULL);
    return time.tv_sec * 1000 + time.tv_usec / 1000;
#endif
}

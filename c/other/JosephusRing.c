#include <stdio.h>

int josephusRing(int num, int interval) {
    int result = 0;
    for (int i = 1; i < num; ++i) {
        result = (result + interval) % (i + 1);
    }
    return result;
}

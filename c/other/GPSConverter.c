#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M_PI 3.1415926535898

typedef struct {
    double longitude;
    double latitude;
} GPSNode;

static const double earthRadius = 6378245;
static const double offset = 0.00669342162296594323;

void wgs84ToGcj02(GPSNode *gps, GPSNode *result) {
    double x = gps->longitude - 105;
    double y = gps->latitude - 35;
    double diffLongitude = 300 + x + 2 * y + 0.1 * x * x + 0.1 * x * y + 0.1 * sqrt(fabs(x))
            + (20 * sin(6 * x * M_PI) + 20 * sin(2 * x * M_PI)) * 2 / 3
            + (20 * sin(x * M_PI) + 40 * sin(x / 3 * M_PI)) * 2 / 3
            + (150 * sin(x / 12 * M_PI) + 300 * sin(x / 30 * M_PI)) * 2 / 3;
    double diffLatitude = -100 + 2 * x + 3 * y + 0.2 * y * y + 0.1 * x * y + 0.2 * sqrt(fabs(x))
            + (20 * sin(6 * x * M_PI) + 20 * sin(2 * x * M_PI)) * 2 / 3
            + (20 * sin(y * M_PI) + 40 * sin(y / 3 * M_PI)) * 2 / 3
            + (160 * sin(y / 12 * M_PI) + 320 * sin(y * M_PI / 30)) * 2 / 3;

    double latitudeRadian = gps->latitude / 180 * M_PI;
    double sinLatitude = sin(latitudeRadian);
    double magic = 1 - offset * sinLatitude * sinLatitude;
    double magicSqrt = sqrt(magic);
    result->longitude = gps->longitude + (diffLongitude * 180) / (earthRadius / magicSqrt * cos(latitudeRadian) * M_PI);
    result->latitude = gps->latitude + (diffLatitude * 180) / ((earthRadius * (1 - offset)) / (magicSqrt * magic) * M_PI);
}

void gcj02ToWgs84(GPSNode *gps, GPSNode *result) {
    double x = gps->longitude - 105;
    double y = gps->latitude - 35;
    double diffLongitude = 300 + x + 2 * y + 0.1 * x * x + 0.1 * x * y + 0.1 * sqrt(fabs(x))
            + (20 * sin(6 * x * M_PI) + 20 * sin(2 * x * M_PI)) * 2 / 3
            + (20 * sin(x * M_PI) + 40 * sin(x / 3 * M_PI)) * 2 / 3
            + (150 * sin(x / 12 * M_PI) + 300 * sin(x / 30 * M_PI)) * 2 / 3;
    double diffLatitude = -100 + 2 * x + 3 * y + 0.2 * y * y + 0.1 * x * y + 0.2 * sqrt(fabs(x))
            + (20 * sin(6 * x * M_PI) + 20 * sin(2 * x * M_PI)) * 2 / 3
            + (20 * sin(y * M_PI) + 40 * sin(y / 3 * M_PI)) * 2 / 3
            + (160 * sin(y / 12 * M_PI) + 320 * sin(y * M_PI / 30)) * 2 / 3;

    double latitudeRadian = gps->latitude / 180 * M_PI;
    double sinLatitude = sin(latitudeRadian);
    double magic = 1 - offset * sinLatitude * sinLatitude;
    double magicSqrt = sqrt(magic);
    result->longitude = gps->longitude - (diffLongitude * 180) / (earthRadius / magicSqrt * cos(latitudeRadian) * M_PI);
    result->latitude = gps->latitude - (diffLatitude * 180) / ((earthRadius * (1 - offset)) / (magicSqrt * magic) * M_PI);
}

void gcj02ToBd09(GPSNode *gps, GPSNode *result) {
    double x = gps->longitude;
    double y = gps->latitude;

    double radius = sqrt(x * x + y * y) + 0.00002 * sin(y * M_PI);
    double radian = atan2(y, x) + 0.000003 * cos(x * M_PI);
    result->longitude = radius * cos(radian) + 0.0065;
    result->latitude = radius * sin(radian) + 0.006;
}

void bd09ToGcj02(GPSNode *gps, GPSNode *result) {
    double x = gps->longitude - 0.0065;
    double y = gps->latitude - 0.006;

    double radius = sqrt(x * x + y * y) - 0.00002 * sin(y * M_PI);
    double radian = atan2(y, x) - 0.000003 * cos(x * M_PI);
    result->longitude = radius * cos(radian);
    result->latitude = radius * sin(radian);
}

void wgs84ToBd09(GPSNode *gps, GPSNode *result) {
    GPSNode *aux = (GPSNode *) malloc(sizeof(GPSNode));
    wgs84ToGcj02(gps, aux);
    gcj02ToBd09(aux, result);
}

void bd09ToWgs84(GPSNode *gps, GPSNode *result) {
    GPSNode *aux = (GPSNode *) malloc(sizeof(GPSNode));
    bd09ToGcj02(gps, aux);
    gcj02ToWgs84(aux, result);
}

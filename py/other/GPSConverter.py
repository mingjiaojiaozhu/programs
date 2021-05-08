#!/usr/bin/env python
# -*- coding:gbk -*-

import math

class GPSNode:
    def __init__(self, longitude: float, latitude: float):
        self.longitude, self.latitude = longitude, latitude

class GPSConverter:
    def __init__(self):
        self.__earthRadius, self.__offset = 6378245, 0.00669342162296594323

    def wgs84ToGcj02(self, gps: GPSNode) -> GPSNode:
        x, y = gps.longitude - 105, gps.latitude - 35
        diffLongitude = 300 + x + 2 * y + 0.1 * x * x + 0.1 * x * y + 0.1 * math.sqrt(math.fabs(x)) \
                        + (20 * math.sin(6 * x * math.pi) + 20 * math.sin(2 * x * math.pi)) * 2 / 3 \
                        + (20 * math.sin(x * math.pi) + 40 * math.sin(x / 3 * math.pi)) * 2 / 3 \
                        + (150 * math.sin(x / 12 * math.pi) + 300 * math.sin(x / 30 * math.pi)) * 2 / 3
        diffLatitude = -100 + 2 * x + 3 * y + 0.2 * y * y + 0.1 * x * y + 0.2 * math.sqrt(math.fabs(x)) \
                        + (20 * math.sin(6 * x * math.pi) + 20 * math.sin(2 * x * math.pi)) * 2 / 3 \
                        + (20 * math.sin(y * math.pi) + 40 * math.sin(y / 3 * math.pi)) * 2 / 3 \
                        + (160 * math.sin(y / 12 * math.pi) + 320 * math.sin(y * math.pi / 30)) * 2 / 3

        latitudeRadian = gps.latitude / 180 * math.pi
        sinLatitude = math.sin(latitudeRadian)
        magic = 1 - self.__offset * sinLatitude * sinLatitude
        magicSqrt = math.sqrt(magic)
        longitude = gps.longitude + (diffLongitude * 180) / (self.__earthRadius / magicSqrt * math.cos(latitudeRadian) * math.pi)
        latitude = gps.latitude + (diffLatitude * 180) / ((self.__earthRadius * (1 - self.__offset)) / (magicSqrt * magic) * math.pi)
        return GPSNode(longitude, latitude)

    def gcj02ToWgs84(self, gps: GPSNode) -> GPSNode:
        x, y = gps.longitude - 105, gps.latitude - 35
        diffLongitude = 300 + x + 2 * y + 0.1 * x * x + 0.1 * x * y + 0.1 * math.sqrt(math.fabs(x)) \
                        + (20 * math.sin(6 * x * math.pi) + 20 * math.sin(2 * x * math.pi)) * 2 / 3 \
                        + (20 * math.sin(x * math.pi) + 40 * math.sin(x / 3 * math.pi)) * 2 / 3 \
                        + (150 * math.sin(x / 12 * math.pi) + 300 * math.sin(x / 30 * math.pi)) * 2 / 3
        diffLatitude = -100 + 2 * x + 3 * y + 0.2 * y * y + 0.1 * x * y + 0.2 * math.sqrt(math.fabs(x)) \
                        + (20 * math.sin(6 * x * math.pi) + 20 * math.sin(2 * x * math.pi)) * 2 / 3 \
                        + (20 * math.sin(y * math.pi) + 40 * math.sin(y / 3 * math.pi)) * 2 / 3 \
                        + (160 * math.sin(y / 12 * math.pi) + 320 * math.sin(y * math.pi / 30)) * 2 / 3

        latitudeRadian = gps.latitude / 180 * math.pi
        sinLatitude = math.sin(latitudeRadian)
        magic = 1 - self.__offset * sinLatitude * sinLatitude
        magicSqrt = math.sqrt(magic)
        longitude = gps.longitude - (diffLongitude * 180) / (self.__earthRadius / magicSqrt * math.cos(latitudeRadian) * math.pi)
        latitude = gps.latitude - (diffLatitude * 180) / ((self.__earthRadius * (1 - self.__offset)) / (magicSqrt * magic) * math.pi)
        return GPSNode(longitude, latitude)

    def gcj02ToBd09(self, gps: GPSNode) -> GPSNode:
        x, y = gps.longitude, gps.latitude
        radius, radian = math.sqrt(x * x + y * y) + 0.00002 * math.sin(y * math.pi), math.atan2(y, x) + 0.000003 * math.cos(x * math.pi)
        return GPSNode(radius * math.cos(radian) + 0.0065, radius * math.sin(radian) + 0.006)

    def bd09ToGcj02(self, gps: GPSNode) -> GPSNode:
        x, y = gps.longitude - 0.0065, gps.latitude - 0.006
        radius, radian = math.sqrt(x * x + y * y) - 0.00002 * math.sin(y * math.pi), math.atan2(y, x) - 0.000003 * math.cos(x * math.pi)
        return GPSNode(radius * math.cos(radian), radius * math.sin(radian))

    def wgs84ToBd09(self, gps: GPSNode) -> GPSNode:
        return self.gcj02ToBd09(self.wgs84ToGcj02(gps))

    def bd09ToWgs84(self, gps: GPSNode) -> GPSNode:
        return self.gcj02ToWgs84(self.bd09ToGcj02(gps))

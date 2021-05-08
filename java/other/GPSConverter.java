package other;

public class GPSConverter {
    private static final double _earthRadius = 6378245;
    private static final double _offset = 0.00669342162296594323;

    public GPSNode wgs84ToGcj02(GPSNode gps) {
        double x = gps.longitude - 105;
        double y = gps.latitude - 35;
        double diffLongitude = 300 + x + 2 * y + 0.1 * x * x + 0.1 * x * y + 0.1 * Math.sqrt(Math.abs(x))
                + (20 * Math.sin(6 * x * Math.PI) + 20 * Math.sin(2 * x * Math.PI)) * 2 / 3
                + (20 * Math.sin(x * Math.PI) + 40 * Math.sin(x / 3 * Math.PI)) * 2 / 3
                + (150 * Math.sin(x / 12 * Math.PI) + 300 * Math.sin(x / 30 * Math.PI)) * 2 / 3;
        double diffLatitude = -100 + 2 * x + 3 * y + 0.2 * y * y + 0.1 * x * y + 0.2 * Math.sqrt(Math.abs(x))
                + (20 * Math.sin(6 * x * Math.PI) + 20 * Math.sin(2 * x * Math.PI)) * 2 / 3
                + (20 * Math.sin(y * Math.PI) + 40 * Math.sin(y / 3 * Math.PI)) * 2 / 3
                + (160 * Math.sin(y / 12 * Math.PI) + 320 * Math.sin(y * Math.PI / 30)) * 2 / 3;

        double latitudeRadian = gps.latitude / 180 * Math.PI;
        double sinLatitude = Math.sin(latitudeRadian);
        double magic = 1 - _offset * sinLatitude * sinLatitude;
        double magicSqrt = Math.sqrt(magic);
        double longitude = gps.longitude + (diffLongitude * 180) / (_earthRadius / magicSqrt * Math.cos(latitudeRadian) * Math.PI);
        double latitude = gps.latitude + (diffLatitude * 180) / ((_earthRadius * (1 - _offset)) / (magicSqrt * magic) * Math.PI);
        return new GPSNode(longitude, latitude);
    }

    public GPSNode gcj02ToWgs84(GPSNode gps) {
        double x = gps.longitude - 105;
        double y = gps.latitude - 35;
        double diffLongitude = 300 + x + 2 * y + 0.1 * x * x + 0.1 * x * y + 0.1 * Math.sqrt(Math.abs(x))
                + (20 * Math.sin(6 * x * Math.PI) + 20 * Math.sin(2 * x * Math.PI)) * 2 / 3
                + (20 * Math.sin(x * Math.PI) + 40 * Math.sin(x / 3 * Math.PI)) * 2 / 3
                + (150 * Math.sin(x / 12 * Math.PI) + 300 * Math.sin(x / 30 * Math.PI)) * 2 / 3;
        double diffLatitude = -100 + 2 * x + 3 * y + 0.2 * y * y + 0.1 * x * y + 0.2 * Math.sqrt(Math.abs(x))
                + (20 * Math.sin(6 * x * Math.PI) + 20 * Math.sin(2 * x * Math.PI)) * 2 / 3
                + (20 * Math.sin(y * Math.PI) + 40 * Math.sin(y / 3 * Math.PI)) * 2 / 3
                + (160 * Math.sin(y / 12 * Math.PI) + 320 * Math.sin(y * Math.PI / 30)) * 2 / 3;

        double latitudeRadian = gps.latitude / 180 * Math.PI;
        double sinLatitude = Math.sin(latitudeRadian);
        double magic = 1 - _offset * sinLatitude * sinLatitude;
        double magicSqrt = Math.sqrt(magic);
        double longitude = gps.longitude - (diffLongitude * 180) / (_earthRadius / magicSqrt * Math.cos(latitudeRadian) * Math.PI);
        double latitude = gps.latitude - (diffLatitude * 180) / ((_earthRadius * (1 - _offset)) / (magicSqrt * magic) * Math.PI);
        return new GPSNode(longitude, latitude);
    }

    public GPSNode gcj02ToBd09(GPSNode gps) {
        double x = gps.longitude;
        double y = gps.latitude;

        double radius = Math.sqrt(x * x + y * y) + 0.00002 * Math.sin(y * Math.PI);
        double radian = Math.atan2(y, x) + 0.000003 * Math.cos(x * Math.PI);
        return new GPSNode(radius * Math.cos(radian) + 0.0065, radius * Math.sin(radian) + 0.006);
    }

    public GPSNode bd09ToGcj02(GPSNode gps) {
        double x = gps.longitude - 0.0065;
        double y = gps.latitude - 0.006;

        double radius = Math.sqrt(x * x + y * y) - 0.00002 * Math.sin(y * Math.PI);
        double radian = Math.atan2(y, x) - 0.000003 * Math.cos(x * Math.PI);
        return new GPSNode(radius * Math.cos(radian), radius * Math.sin(radian));
    }

    public GPSNode wgs84ToBd09(GPSNode gps) {
        return gcj02ToBd09(wgs84ToGcj02(gps));
    }

    public GPSNode bd09ToWgs84(GPSNode gps) {
        return gcj02ToWgs84(bd09ToGcj02(gps));
    }

    public class GPSNode {
        public double longitude = 0;
        public double latitude = 0;

        public GPSNode(double longitude, double latitude) {
            this.longitude = longitude;
            this.latitude = latitude;
        }
    }
}

package other;

public class SnowFlake {
    private static final long _startTimeStamp = 1356019200000L;

    private long _timeStamp = 0;
    private int _dataCenterId = 0;
    private int _workerId = 0;
    private int _sequence = 0;

    public SnowFlake(int dataCenterId, int workerId) {
        _dataCenterId = dataCenterId;
        _workerId = workerId;
    }

    public long uuid() {
        long tick = System.currentTimeMillis();
        if (tick < _timeStamp) {
            return Integer.MIN_VALUE;
        }

        if (tick == _timeStamp) {
            _sequence = (_sequence + 1) & (~(-1 << 12));
            if (0 == _sequence) {
                while (tick == _timeStamp) {
                    tick = System.currentTimeMillis();
                }
            }
        } else {
            _sequence = 0;
        }
        _timeStamp = tick;
        return ((tick - _startTimeStamp) << 22) | (_dataCenterId << 17) | (_workerId << 12) | _sequence;
    }
}

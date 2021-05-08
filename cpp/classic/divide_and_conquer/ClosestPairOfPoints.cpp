#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class ClosestPairOfPoints {
public:
    vector<vector<int>> solution(vector<vector<int>> &points) {
        vector<vector<int>> result(2, vector<int>(0));
        match(points, result);
        return result;
    }

private:
    int match(vector<vector<int>> &points, vector<vector<int>> &result) {
        int length = points.size();
        if (length < 2) {
            return INT_MAX;
        }
        if (2 == length) {
            result[0] = points[0];
            result[1] = points[1];
            return getDistance(points[0], points[1]);
        }

        sort(points.begin(), points.end(), cmpOfX);

        int halfSize = length >> 1;
        vector<vector<int>> left(points.begin(), points.begin() + halfSize);
        vector<vector<int>> aux1(2, vector<int>(0));
        int distance1 = match(left, aux1);

        vector<vector<int>> right(points.begin() + halfSize, points.end());
        vector<vector<int>> aux2(2, vector<int>(0));
        int distance2 = match(right, aux2);

        int minDistance = min(distance1, distance2);
        if (distance1 < distance2) {
            result[0] = aux1[0];
            result[1] = aux1[1];
        } else {
            result[0] = aux2[0];
            result[1] = aux2[1];
        }

        int border1 = getBorder(left, 0, points[halfSize][0] - minDistance);
        int border2 = getBorder(right, 0, points[halfSize][0] + minDistance);
        if (border1 == left.size() || !border2) {
            return minDistance;
        }

        vector<vector<int>> aux(right.begin(), right.begin() + border2);
        sort(aux.begin(), aux.end(), cmpOfY);

        for (int i = border1; i < (int) left.size(); ++i) {
            int start = getBorder(aux, 1, left[i][1] - minDistance);
            int end = getBorder(aux, 1, left[i][1] + minDistance);
            for (int j = start; j < end; ++j) {
                int distance = getDistance(left[i], aux[j]);
                if (minDistance > distance) {
                    result[0] = left[i];
                    result[1] = aux[j];
                    minDistance = distance;
                }
            }
        }
        return minDistance;
    }

    int getBorder(vector<vector<int>> &points, int index, int target) {
        int start = 0;
        int end = points.size() - 1;
        while (start <= end) {
            int middle = start + ((end - start) >> 1);
            if (target < points[middle][index]) {
                end = middle - 1;
            } else {
                start = middle + 1;
            }
        }
        return start;
    }

    int getDistance(vector<int> &point1, vector<int> &point2) {
        return abs(point2[0] - point1[0]) + abs(point2[1] - point1[1]);
    }

    static bool cmpOfX(const vector<int> &node1, const vector<int> &node2) {
        return node1[0] < node2[0];
    }

    static bool cmpOfY(const vector<int> &node1, const vector<int> &node2) {
        return node1[1] < node2[1];
    }
};

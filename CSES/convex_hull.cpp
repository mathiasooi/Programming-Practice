#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct pt {
    long long x, y;
};

long long cross(pt p1, pt p2, pt p3) {
    // 2d cross of p1p2 and p2p3
    // signed area of triangle
    // < 0 cw
    // > 0 ccw
    return p1.x*(p2.y-p3.y) + p2.x*(p3.y-p1.y) + p3.x*(p1.y-p2.y);
}

int main() {
    vector<pt> points;
    long long n; cin >> n;
    for (long long i = 0; i < n; ++i) {
        long long x, y; cin >> x >> y;
        points.push_back(pt{x, y});
    }
    pt start = points[0];
    for (pt p : points) {
        if (p.y < start.y) {
            start = p;
        }
        if (p.y == start.y && p.x < start.x) {
            start = p;
        }
    }
    sort(points.begin(), points.end(), [&start](const pt& a, const pt& b) {
        long long dir = cross(start, a, b);
        // sort by distance to start if colinear
        if (dir == 0) return (start.x-a.x)*(start.x-a.x) + (start.y-a.y)*(start.y-a.y) 
                        < (start.x-b.x)*(start.x-b.x) + (start.y-b.y)*(start.y-b.y);
        return dir < 0;
    });

    vector<pt> st;
    for (long long i = 0; i < n; ++i) {
        while (st.size() > 1 && cross(st[st.size() - 2], st.back(), points[i]) > 0) {
            st.pop_back();
        }
        st.push_back(points[i]);
    }
    cout << st.size() << '\n';
    for (pt p: st) {
        cout << p.x << ' ' << p.y << '\n';
    }
}
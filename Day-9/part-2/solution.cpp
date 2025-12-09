#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <set>
#include <tuple>
#include <vector>
using namespace std;

template <class T> struct Point {
    T x;
    T y;
    Point(const T& x_ = 0, const T& y_ = 0) : x(x_), y(y_) {}

    template <class U> operator Point<U>() {
        return Point<U>(U(x), U(y));
    }
    Point& operator+=(const Point& p) & {
        x += p.x;
        y += p.y;
        return *this;
    }
    Point& operator-=(const Point& p) & {
        x -= p.x;
        y -= p.y;
        return *this;
    }
    Point& operator*=(const T& v) & {
        x *= v;
        y *= v;
        return *this;
    }
    Point& operator/=(const T& v) & {
        x /= v;
        y /= v;
        return *this;
    }
    Point operator-() const {
        return Point(-x, -y);
    }
    friend Point operator+(Point a, const Point& b) {
        return a += b;
    }
    friend Point operator-(Point a, const Point& b) {
        return a -= b;
    }
    friend Point operator*(Point a, const T& b) {
        return a *= b;
    }
    friend Point operator/(Point a, const T& b) {
        return a /= b;
    }
    friend Point operator*(const T& a, Point b) {
        return b *= a;
    }
    friend bool operator==(const Point& a, const Point& b) {
        return a.x == b.x and a.y == b.y;
    }
    friend std::istream& operator>>(std::istream& is, Point& p) {
        return is >> p.x >> p.y;
    }
    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
};

template <class T> struct Line {
    Point<T> a;
    Point<T> b;
    Line(const Point<T>& a_ = Point<T>(), const Point<T>& b_ = Point<T>()) : a(a_), b(b_) {}
};

template <class T> T cross(const Point<T>& a, const Point<T>& b) {
    return a.x * b.y - a.y * b.x;
}

template <class T> bool pointOnLineLeft(const Point<T>& p, const Line<T>& l) {
    return cross(l.b - l.a, p - l.a) > 0;
}

template <class T> bool pointOnSegment(const Point<T>& p, const Line<T>& l) {
    return cross(p - l.a, l.b - l.a) == 0 and std::min(l.a.x, l.b.x) <= p.x and p.x <= std::max(l.a.x, l.b.x) and
           std::min(l.a.y, l.b.y) <= p.y and p.y <= std::max(l.a.y, l.b.y);
}

template <class T> T dot(const Point<T>& a, const Point<T>& b) {
    return a.x * b.x + a.y * b.y;
}

template <class T> std::tuple<int, Point<T>, Point<T>> segmentIntersection(const Line<T>& l1, const Line<T>& l2) {
    if (std::max(l1.a.x, l1.b.x) < std::min(l2.a.x, l2.b.x)) {
        return {0, Point<T>(), Point<T>()};
    }
    if (std::min(l1.a.x, l1.b.x) > std::max(l2.a.x, l2.b.x)) {
        return {0, Point<T>(), Point<T>()};
    }
    if (std::max(l1.a.y, l1.b.y) < std::min(l2.a.y, l2.b.y)) {
        return {0, Point<T>(), Point<T>()};
    }
    if (std::min(l1.a.y, l1.b.y) > std::max(l2.a.y, l2.b.y)) {
        return {0, Point<T>(), Point<T>()};
    }
    if (cross(l1.b - l1.a, l2.b - l2.a) == 0) {
        if (cross(l1.b - l1.a, l2.a - l1.a) != 0) {
            return {0, Point<T>(), Point<T>()};
        } else {
            auto maxx1 = std::max(l1.a.x, l1.b.x);
            auto minx1 = std::min(l1.a.x, l1.b.x);
            auto maxy1 = std::max(l1.a.y, l1.b.y);
            auto miny1 = std::min(l1.a.y, l1.b.y);
            auto maxx2 = std::max(l2.a.x, l2.b.x);
            auto minx2 = std::min(l2.a.x, l2.b.x);
            auto maxy2 = std::max(l2.a.y, l2.b.y);
            auto miny2 = std::min(l2.a.y, l2.b.y);
            Point<T> p1(std::max(minx1, minx2), std::max(miny1, miny2));
            Point<T> p2(std::min(maxx1, maxx2), std::min(maxy1, maxy2));
            if (not pointOnSegment(p1, l1)) {
                std::swap(p1.y, p2.y);
            }
            if (p1 == p2) {
                return {3, p1, p2};
            } else {
                return {2, p1, p2};
            }
        }
    }
    auto cp1 = cross(l2.a - l1.a, l2.b - l1.a);
    auto cp2 = cross(l2.a - l1.b, l2.b - l1.b);
    auto cp3 = cross(l1.a - l2.a, l1.b - l2.a);
    auto cp4 = cross(l1.a - l2.b, l1.b - l2.b);

    if ((cp1 > 0 and cp2 > 0) or (cp1 < 0 and cp2 < 0) or (cp3 > 0 and cp4 > 0) or (cp3 < 0 and cp4 < 0)) {
        return {0, Point<T>(), Point<T>()};
    }

    Point<T> p = Point<T>();
    if (cp1 != 0 and cp2 != 0 and cp3 != 0 and cp4 != 0) {
        return {1, p, p};
    } else {
        return {3, p, p};
    }
}

template <class T> bool segmentInPolygon(const Line<T>& l, const std::vector<Point<T>>& p) {
    int n = p.size();
    if (not pointInPolygon(l.a, p)) {
        return false;
    }
    if (not pointInPolygon(l.b, p)) {
        return false;
    }
    for (int i = 0; i < n; i++) {
        auto u = p[i];
        auto v = p[(i + 1) % n];
        auto w = p[(i + 2) % n];
        auto [t, p1, p2] = segmentIntersection(l, Line<T>(u, v));

        if (t == 1) {
            return false;
        }
        if (t == 0) {
            continue;
        }
        if (t == 2) {
            if (pointOnSegment(v, l) and v != l.a and v != l.b) {
                if (cross(v - u, w - v) > 0) {
                    return false;
                }
            }
        } else {
            if (p1 != u and p1 != v) {
                if (pointOnLineLeft(l.a, Line<T>(v, u)) or pointOnLineLeft(l.b, Line<T>(v, u))) {
                    return false;
                }
            } else if (p1 == v) {
                if (l.a == v) {
                    if (pointOnLineLeft(u, l)) {
                        if (pointOnLineLeft(w, l) and pointOnLineLeft(w, Line<T>(u, v))) {
                            return false;
                        }
                    } else {
                        if (pointOnLineLeft(w, l) or pointOnLineLeft(w, Line<T>(u, v))) {
                            return false;
                        }
                    }
                } else if (l.b == v) {
                    if (pointOnLineLeft(u, Line<T>(l.b, l.a))) {
                        if (pointOnLineLeft(w, Line<T>(l.b, l.a)) and pointOnLineLeft(w, Line<T>(u, v))) {
                            return false;
                        }
                    } else {
                        if (pointOnLineLeft(w, Line<T>(l.b, l.a)) or pointOnLineLeft(w, Line<T>(u, v))) {
                            return false;
                        }
                    }
                } else {
                    if (pointOnLineLeft(u, l)) {
                        if (pointOnLineLeft(w, Line<T>(l.b, l.a)) or pointOnLineLeft(w, Line<T>(u, v))) {
                            return false;
                        }
                    } else {
                        if (pointOnLineLeft(w, l) or pointOnLineLeft(w, Line<T>(u, v))) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

template <class T> bool pointInPolygon(const Point<T>& a, const std::vector<Point<T>>& p) {
    int n = p.size();
    for (int i = 0; i < n; i++) {
        if (pointOnSegment(a, Line(p[i], p[(i + 1) % n]))) {
            return true;
        }
    }

    int t = 0;
    for (int i = 0; i < n; i++) {
        auto u = p[i];
        auto v = p[(i + 1) % n];
        if (u.x < a.x and v.x >= a.x and pointOnLineLeft(a, Line(v, u))) {
            t ^= 1;
        }
        if (u.x >= a.x and v.x < a.x and pointOnLineLeft(a, Line(u, v))) {
            t ^= 1;
        }
    }

    return t == 1;
}

#define int long long
#define all(x) (x).begin(), (x).end()

bool rectangleInside(
    const vector<Point<int>>& poly, int x1, int y1, int x2, int y2, const vector<int>& X, const vector<int>& Y) {
    if (x1 > x2) swap(x1, x2);
    if (y1 > y2) swap(y1, y2);

    if (not pointInPolygon(Point<int>(x1, y1), poly) or not pointInPolygon(Point<int>(x1, y2), poly) or
        not pointInPolygon(Point<int>(x2, y1), poly) or not pointInPolygon(Point<int>(x2, y2), poly) or
        not pointInPolygon(Point<int>((x1 + x2) / 2, (y1 + y2) / 2), poly))
        return false;

    for (int x : X)
        if (x1 < x and x < x2)
            if (not pointInPolygon(Point<int>(x, y1), poly) or not pointInPolygon(Point<int>(x, y2), poly))
                return false;

    for (int y : Y)
        if (y1 < y and y < y2)
            if (not pointInPolygon(Point<int>(x1, y), poly) or not pointInPolygon(Point<int>(x2, y), poly))
                return false;

    return true;
}

signed main() {
    cin.tie(0)->sync_with_stdio(false);
    int x, y;
    char c;
    vector<array<int, 2>> poi;
    while (cin >> x >> c >> y) poi.push_back({x, y});
    vector<Point<int>> poly;
    for (auto [px, py] : poi) poly.push_back(Point<int>(px, py));
    int n = poly.size(), val = 0;
    set<int> Tx, Ty;
    for (auto& p : poly) Tx.insert(p.x), Ty.insert(p.y);
    vector<int> X(all(Tx)), Y(all(Ty));
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            int x1 = poly[i].x, y1 = poly[i].y, x2 = poly[j].x, y2 = poly[j].y;
            if (rectangleInside(poly, x1, y1, x2, y2, X, Y)) val = max(val, (abs(x2 - x1) + 1) * (abs(y2 - y1) + 1));
        }
    cout << val << '\n';
    return 0;
}

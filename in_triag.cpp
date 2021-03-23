#include <iostream>
#include <cmath>

template <typename T>
struct Vec3
{
    T x, y, z;
    Vec3(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}

    Vec3 cross(const Vec3 &b)
    {
        return Vec3(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
    }

    T norm()
    {
        return sqrt(x * x + y * y + z * z);
    }

    Vec3 normalized()
    {
        return (*this) / norm();
    }

    T dot(const Vec3 &b)
    {
        return x * b.x + y * b.y + z * b.z;
    }

    Vec3 operator+(const Vec3 &v)
    {
        return {x + v.x, y + v.y, z + v.z};
    }

    Vec3 operator/(T val)
    {
        double v = static_cast<double>(val);
        return {x / v, y / v, z / v};
    }

    friend Vec3 operator-(const Vec3 &a, const Vec3 &b)
    {
        return {a.x - b.x, a.y - b.y, a.z - b.z};
    }

    friend std::ostream &operator<<(std::ostream &out, const Vec3 &v)
    {
        out << v.x << "," << v.y << "," << v.z;
        return out;
    }
};

typedef Vec3<double> Vec3d;

using namespace std;

void test1()
{
    Vec3d p0(-1, 0, 0), p1(1, 0, 0), p2(0, 1, 0), M(-0.5, 0.2, 0);
    Vec3d p6 = (p0 + p1 + p2) / 3;

    Vec3d p3 = (p0 + p1) / 2;
    Vec3d p4 = (p1 + p2) / 2;
    Vec3d p5 = (p2 + p0) / 2;

    Vec3d p20 = p0 - p2;
    Vec3d p21 = p1 - p2;
    Vec3d n = p20.cross(p21).normalized();
    Vec3d n0 = (p3 - p6).cross(n);
    Vec3d n1 = (p4 - p6).cross(n);
    Vec3d n2 = (p5 - p6).cross(n);

    Vec3d p6M = M - p6;
    cout << n0 << " " << p6M.dot(n0) << endl;
    cout << n1 << " " << p6M.dot(n1) << endl;
    cout << n2 << " " << p6M.dot(n2) << endl;
}

void test2()
{
    Vec3d p0(-1, 0, 0), p1(1, 0, 0), p2(0, sqrt(3), 0), M(-0.5, 0.2, 0);
    Vec3d p6 = (p0 + p1 + p2) / 3;
    cout << "p6=" << p6 << endl;

    Vec3d p3 = (p0 + p1) / 2;
    Vec3d p4 = (p1 + p2) / 2;
    Vec3d p5 = (p2 + p0) / 2;

    Vec3d p20 = p0 - p2;
    Vec3d p21 = p1 - p2;
    Vec3d n = p20.cross(p21).normalized();
    Vec3d n0 = (p3 - p6).cross(n);
    Vec3d n1 = (p4 - p6).cross(n);
    Vec3d n2 = (p5 - p6).cross(n);

    Vec3d p6M = M - p6;
    cout << n0 << " " << p6M.dot(n0) << endl;
    cout << n1 << " " << p6M.dot(n1) << endl;
    cout << n2 << " " << p6M.dot(n2) << endl;
}

int main()
{
    // test1();
    test2();
    return 0;
}
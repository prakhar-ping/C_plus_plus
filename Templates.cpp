#include <iostream>

template <typename T>
struct Vector2
{
    T x, y;

    Vector2(T newX, T newY) : x(newX), y(newY)
    {
    }

    T DotProduct(const Vector2<T> &other)
    {
        return (x * other.x) + (y * other.y);
    }

    Vector2<T> operator+(const Vector2<T> &rhs) const
    {
        return Vector2<T>(x + rhs.x, y + rhs.y);
    }

    Vector2<T> operator*(const T &val) const
    {
        return Vector2<T>(x * val, y * val);
    }
};

int main()
{
    Vector2<int> v1(2, 3);
    Vector2<int> v2(4, 5);
    Vector2<float> v3(2.3, 3.2);
    Vector2<float> v4(4.5, 5.4);

    Vector2<int> v5 = v1 + v2;
    v5 = v5 * 2;
    std::cout << v5.x << std::endl;
    std::cout << v5.y << std::endl;
    std::cout << v3.DotProduct(v4) << std::endl;
    return 0;
}
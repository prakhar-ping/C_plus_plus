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
};

int main()
{
    Vector2<int> v1(2, 3);
    Vector2<int> v2(4, 5);
    Vector2<float> v3(2.3, 3.2);
    Vector2<float> v4(4.5, 5.4);

    std::cout << v1.DotProduct(v2) << std::endl;
    std::cout << v3.DotProduct(v4) << std::endl;
    return 0;
}
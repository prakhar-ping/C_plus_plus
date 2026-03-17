#include <iostream>

// alignas(16) forces the OS to place this struct at a memory address
// that is a perfect multiple of 16 bytes. This is a strict hardware requirement
// for the CPU to load all 4 floats into a SIMD register simultaneously.
struct alignas(16) Vector4
{
    float x, y, z, w;
    Vector4() {};
    Vector4(float _x, float _y, float _z, float _w = 1.0f) : x(_x), y(_y), z(_z), w(_w)
    {
    }
};

// The Default Constructor builds the Blank Canvas: The Identity Matrix.
// We place 1.0f on the diagonal slots (0, 5, 10, 15) and 0.0f everywhere else.
struct alignas(16) Matrix4X4
{
    float m[16];

    Matrix4X4()
    {
        for (int i = 0; i < 16; i++)
            m[i] = 0.0f;

        m[0] = 1.0f;
        m[5] = 1.0f;
        m[10] = 1.0f;
        m[15] = 1.0f;
    }

    Vector4 operator*(const Vector4 &v) const
    {
        Vector4 result;
        result.x = (m[0] * v.x) + (m[1] * v.y) + (m[2] * v.z) + (m[3] * v.w);
        result.y = (m[4] * v.x) + (m[5] * v.y) + (m[6] * v.z) + (m[7] * v.w);
        result.z = (m[8] * v.x) + (m[9] * v.y) + (m[10] * v.z) + (m[11] * v.w);
        result.w = (m[12] * v.x) + (m[13] * v.y) + (m[14] * v.z) + (m[15] * v.w);
        return result;
    };
};

int main()
{
    Vector4 spaceShip(0, 0, 0, 1.0f);
    Matrix4X4 targetMatrix;
    targetMatrix.m[3] = 10.0f;
    targetMatrix.m[7] = 0.0f;
    targetMatrix.m[11] = 50.0f;

    Vector4 targetMovement = targetMatrix * spaceShip;
    std::cout << "BeforMovement -> " << spaceShip.x << "," << spaceShip.y << "," << spaceShip.z << "," << spaceShip.w << std::endl;
    std::cout << "AfterMovement -> " << targetMovement.x << "," << targetMovement.y << "," << targetMovement.z << "," << targetMovement.w << std::endl;
    return 0;
}
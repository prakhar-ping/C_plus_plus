#include <iostream>
#include <cmath>

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
    }

    Matrix4X4 operator*(const Matrix4X4 &mat) const
    {
        Matrix4X4 result;
        for (int row = 0; row < 4; ++row)
        {
            for (int col = 0; col < 4; ++col)
            {
                result.m[(row * 4) + col] =
                    (m[(row * 4) + 0] * mat.m[(0 * 4) + col]) +
                    (m[(row * 4) + 1] * mat.m[(1 * 4) + col]) +
                    (m[(row * 4) + 2] * mat.m[(2 * 4) + col]) +
                    (m[(row * 4) + 3] * mat.m[(3 * 4) + col]);
            }
        }
        return result;
    }

    static Matrix4X4 ScaleMatrix(float x, float y, float z)
    {
        Matrix4X4 result;
        result.m[0] = x;
        result.m[5] = y;
        result.m[10] = z;
        return result;
    }
    static Matrix4X4 TranslateMatrix(float x, float y, float z)
    {
        Matrix4X4 result;
        result.m[3] = x;
        result.m[7] = y;
        result.m[11] = z;
        return result;
    }

    static Matrix4X4 RotateY(float radians)
    {
        Matrix4X4 result; // Starts as Identity Matrix
        float c = std::cos(radians);
        float s = std::sin(radians);

        result.m[0] = c;
        result.m[2] = s;
        result.m[8] = -s;
        result.m[10] = c;

        return result;
    }
};

void PrintMatrix(const Matrix4X4 &mat)
{
    for (int i = 0; i < 16; i++)
    {
        if (i % 4 == 0)
        {
            std::cout << std::endl;
        }
        std::cout << mat.m[i] << ",";
    }
}

int main()
{
    Vector4 vertex(1.0f, 0.0f, 0.0f, 1.0f);
    float ang = 3.14159f;
    Matrix4X4 targetMatrix = Matrix4X4::TranslateMatrix(10.0f, 0.0f, 50.0f);
    Matrix4X4 scaleTargetMatrix = Matrix4X4::ScaleMatrix(2.0f, 1.0f, 1.0f);
    Matrix4X4 rotateMatrix = Matrix4X4::RotateY(ang);

    Matrix4X4 superMatrix = targetMatrix * rotateMatrix * scaleTargetMatrix;
    Vector4 newVector = superMatrix * vertex;
    PrintMatrix(targetMatrix);
    std::cout << std::endl;
    PrintMatrix(scaleTargetMatrix);
    std::cout << std::endl;
    PrintMatrix(rotateMatrix);
    std::cout << std::endl;
    PrintMatrix(superMatrix);
    std::cout << std::endl;
    std::cout << "Final vector ->" << newVector.x << "," << newVector.y << "," << newVector.z << "," << newVector.w << std::endl;
    return 0;
}
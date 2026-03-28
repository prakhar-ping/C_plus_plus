#include <iostream>
#include <vector>
#include <math.h>

struct alignas(16) Vector4
{
    float x, y, z, w;
    Vector4()
    {
    }

    Vector4(float _x, float _y, float _z) : x(_x), y(_y), z(_z), w(1)
    {
    }

    Vector4 operator-(const Vector4 &other) const
    {
        return Vector4(x - other.x, y - other.y, z - other.z);
    }

    static float Dot(const Vector4 &a, const Vector4 &b)
    {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
    }

    static Vector4 Cross(const Vector4 &a, const Vector4 &b)
    {
        Vector4 result;
        result.x = (a.y * b.z) - (a.z * b.y);
        result.y = (a.x * b.z) - (a.z * b.x);
        result.z = (a.x * b.y) - (a.y * b.x);
        return result;
    }

    static void Normalize(const Vector4 &a)
    {
        Vector4 result;
        float squaredLength = (a.x * a.x) + (a.y * a.y) + (a.z * a.z);

        if (squaredLength > 0.000001)
        {
            float length = std::sqrt(squaredLength);
            result.x /= length;
            result.y /= length;
            result.z /= length;
        }
    }
};

struct alignas(16) Matrix4x4
{
    float matrix[16];
    // Create a default indentical matrix4x4 constructor;
    Matrix4x4()
    {

        for (int i = 0; i < 16; i++)
        {
            matrix[i] = 0.0f;
        }
        matrix[0] = 1.0f;
        matrix[5] = 1.0f;
        matrix[10] = 1.0f;
        matrix[15] = 1.0f;
    }
    // Matrix * Vector
    Vector4 &operator*(const Vector4 &vec) const
    {
        Vector4 result;
        result.x = (matrix[0] * vec.x) + (matrix[1] * vec.y) + (matrix[2] * vec.z) + (matrix[3] * vec.w);
        result.y = (matrix[4] * vec.x) + (matrix[5] * vec.y) + (matrix[6] * vec.z) + (matrix[7] * vec.w);
        result.z = (matrix[8] * vec.x) + (matrix[9] * vec.y) + (matrix[10] * vec.z) + (matrix[11] * vec.w);
        result.w = (matrix[12] * vec.x) + (matrix[13] * vec.y) + (matrix[14] * vec.z) + (matrix[15] * vec.w);
        return result;
    }
    // Matrix * Matrix
    Matrix4x4 &operator*(const Matrix4x4 &mat) const
    {
        Matrix4x4 result;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                result.matrix[(i * 4) + j] =
                    (matrix[(i * 4) + 0] * mat.matrix[(0 * 4) + j]) +
                    (matrix[(i * 4) + 1] * mat.matrix[(1 * 4) + j]) +
                    (matrix[(i * 4) + 2] * mat.matrix[(2 * 4) + j]) +
                    (matrix[(i * 4) + 3] * mat.matrix[(3 * 4) + j]);
            }
        }

        for (int i = 0; i < 16; i++)
        {
            std::cout << result.matrix[i] << std::endl;
        }
        return result;
    }

    static Matrix4x4 ScaleMatrix(const Vector4 &vec)
    {
        Matrix4x4 mat;
        mat.matrix[0] = vec.x;
        mat.matrix[5] = vec.y;
        mat.matrix[10] = vec.z;

        return mat;
    }

    static Matrix4x4 RotateY(float radian)
    {
        float c = std::cos(radian);
        float s = std::sin(radian);
        Matrix4x4 result;
        result.matrix[0] = c;
        result.matrix[2] = s;
        result.matrix[8] = -s;
        result.matrix[10] = c;
        return result;
    }

    static Matrix4x4 TranslateMatrix(const Vector4 &vec)
    {
        Matrix4x4 result;
        result.matrix[3] = vec.x;
        result.matrix[7] = vec.y;
        result.matrix[11] = vec.z;

        return result;
    }
};

static Matrix4x4 LookAt(const Vector4 &eye, const Vector4 &target, const Vector4 &up)
{
    Vector4 forwardVec = target - eye;
    Vector4::Normalize(forwardVec);
    Vector4 rightVec = Vector4::Cross(forwardVec, up);
    Vector4::Normalize(rightVec);
    Vector4 upVec = Vector4::Cross(rightVec, forwardVec);
    Matrix4x4 view;

    view.matrix[0] = rightVec.x;
    view.matrix[1] = rightVec.y;
    view.matrix[2] = rightVec.z;
    view.matrix[3] = 0.0f;
    view.matrix[4] = upVec.x;
    view.matrix[5] = upVec.y;
    view.matrix[6] = upVec.z;
    view.matrix[7] = 0.0f;
    view.matrix[8] = forwardVec.x;
    view.matrix[9] = forwardVec.y;
    view.matrix[10] = forwardVec.z;
    view.matrix[11] = 0.0f;
    view.matrix[12] = -Vector4::Dot(eye, rightVec);
    view.matrix[13] = -Vector4::Dot(eye, upVec);
    view.matrix[14] = -Vector4::Dot(eye, forwardVec);
    view.matrix[15] = 1;

    return view;
}

int main()
{

    return 0;
}
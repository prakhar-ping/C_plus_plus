#include <iostream>
#include <vector>
#include <math.h>
#include "../Headers/ThreadPool.hpp"

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

    void Normalize()
    {
        float squaredLength = (x * x) + (y * y) + (z * z);
        if (squaredLength > 0.000001)
        {
            float length = std::sqrt(squaredLength);
            x /= length;
            y /= length;
            z /= length;
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
    Vector4 operator*(const Vector4 &vec) const
    {
        Vector4 result;
        result.x = (matrix[0] * vec.x) + (matrix[4] * vec.y) + (matrix[8] * vec.z) + (matrix[12] * vec.w);
        result.y = (matrix[1] * vec.x) + (matrix[5] * vec.y) + (matrix[9] * vec.z) + (matrix[13] * vec.w);
        result.z = (matrix[2] * vec.x) + (matrix[6] * vec.y) + (matrix[10] * vec.z) + (matrix[14] * vec.w);
        result.w = (matrix[3] * vec.x) + (matrix[7] * vec.y) + (matrix[11] * vec.z) + (matrix[15] * vec.w);
        return result;
    }
    // Matrix * Matrix
    Matrix4x4 operator*(const Matrix4x4 &mat) const
    {
        Matrix4x4 result;
        for (int col = 0; col < 4; col++)
        {
            for (int row = 0; row < 4; row++)
            {
                // strict Column-Major indexing
                result.matrix[col * 4 + row] =
                    (matrix[0 * 4 + row] * mat.matrix[col * 4 + 0]) +
                    (matrix[1 * 4 + row] * mat.matrix[col * 4 + 1]) +
                    (matrix[2 * 4 + row] * mat.matrix[col * 4 + 2]) +
                    (matrix[3 * 4 + row] * mat.matrix[col * 4 + 3]);
            }
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
        result.matrix[12] = vec.x;
        result.matrix[13] = vec.y;
        result.matrix[14] = vec.z;

        return result;
    }
};

static Matrix4x4 LookAt(const Vector4 &eye, const Vector4 &target, const Vector4 &up)
{
    Vector4 forwardVec = target - eye;
    forwardVec.Normalize();
    Vector4 rightVec = Vector4::Cross(forwardVec, up);
    rightVec.Normalize();
    Vector4 upVec = Vector4::Cross(rightVec, forwardVec);
    Matrix4x4 view;

    view.matrix[0] = rightVec.x;
    view.matrix[4] = rightVec.y;
    view.matrix[8] = rightVec.z;
    view.matrix[3] = 0.0f;
    view.matrix[1] = upVec.x;
    view.matrix[5] = upVec.y;
    view.matrix[9] = upVec.z;
    view.matrix[7] = 0.0f;
    view.matrix[2] = forwardVec.x;
    view.matrix[6] = forwardVec.y;
    view.matrix[10] = forwardVec.z;
    view.matrix[11] = 0.0f;
    view.matrix[12] = -Vector4::Dot(eye, rightVec);
    view.matrix[13] = -Vector4::Dot(eye, upVec);
    view.matrix[14] = -Vector4::Dot(eye, forwardVec);
    view.matrix[15] = 1;

    return view;
}

static Matrix4x4 PerpecticeMatrix(const float &FOV, const float &aspectRatio, const float &nearPlane, float &farPlane)
{
    Matrix4x4 result;
    float radian = FOV * (3.14159f / 180.0f);
    float f = 1 / std::tan(radian / 2.0f);

    result.matrix[0] = 1 / aspectRatio * f;
    result.matrix[1] = 0.0f;
    result.matrix[2] = 0.0f;
    result.matrix[3] = 0.0f;
    result.matrix[4] = 0.0f;
    result.matrix[5] = f;
    result.matrix[6] = 0.0f;
    result.matrix[7] = 0.0f;
    result.matrix[8] = 0.0f;
    result.matrix[9] = 0.0f;
    result.matrix[10] = farPlane / (farPlane - nearPlane);
    result.matrix[11] = 1.0f;
    result.matrix[12] = 0.0f;
    result.matrix[13] = 0.0f;
    result.matrix[14] = -(nearPlane * farPlane) / (farPlane - nearPlane);
    result.matrix[15] = 0.0f;

    return result;
}

void ProcessVertexChunk(std::vector<Vector4> &vertices, const Matrix4x4 &superMat, int start, int end)
{
    for (int i = start; i < end; i++)
    {
        vertices[i] = superMat * vertices[i];

        // The Hardware Perspective Divide
        vertices[i].x = vertices[i].x / vertices[i].w;
        vertices[i].y = vertices[i].y / vertices[i].w;
        vertices[i].z = vertices[i].z / vertices[i].w;
    }
}

int main()
{
    std::vector<Vector4> vertices(100000, Vector4(1.0f, 1.0f, 1.0f));

    // Model Matrix: Scale by (2, 2, 2), RotateY by π (3.14159f),
    // Translate by (10, 0, 50). Multiply them in strict S-R-T order.

    Vector4 scaleBy(2, 2, 2);
    Vector4 translateBy(10, 0, 50);
    float rotateBy(3.14159f);

    Matrix4x4 scaleMat = Matrix4x4::ScaleMatrix(scaleBy);
    Matrix4x4 rotateMat = Matrix4x4::RotateY(rotateBy);
    Matrix4x4 translationMat = Matrix4x4::TranslateMatrix(translateBy);

    Matrix4x4 modelMat = translationMat * rotateMat * scaleMat;

    // Place the camera Eye at (0.0f, 5.0f, -10.0f), looking
    // at Target (0.0f, 0.0f, 0.0f), with Up as (0.0f, 1.0f, 0.0f).
    Vector4 eye(0.0f, 5.0f, -10.0f);
    Vector4 target(0.0f, 0.0f, 0.0f);
    Vector4 up(0.0f, 1.0f, 0.0f);

    Matrix4x4 viewMat = LookAt(eye, target, up);

    // 90 Vertical FOV (Convert 90.0f degrees to radians!), Aspect Ratio 1.777f, Near 0.1f, Far 1000.0f
    float FOVdegree = 90.0f;
    float aspRatio = 1.777f;
    float near = 0.1f;
    float far = 1000.0f;

    Matrix4x4 projectionMat = PerpecticeMatrix(FOVdegree, aspRatio, near, far);

    Matrix4x4 superMat = projectionMat * viewMat * modelMat;
    {
        size_t numThreads = std::thread::hardware_concurrency();
        int chunckSize = 100000 / numThreads;
        Threadpool pool(numThreads);
        for (int i = 0; i < numThreads; i++)
        {

            int start = i * chunckSize;
            int end;
            end = (i + 1) * chunckSize;
            if (i == numThreads - 1)
            {
                end = 100000;
            }

            pool.Enqueue([&vertices, &superMat, start, end]
                         { ProcessVertexChunk(vertices, superMat, start, end); });
        }
    }
    std::cout << "Final Vertex -> " << vertices[99999].x << "," << vertices[99999].y << "," << vertices[99999].z << std::endl;
    return 0;
}
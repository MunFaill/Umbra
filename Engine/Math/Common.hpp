#pragma once

#include "glm/detail/qualifier.hpp"
#include "glm/geometric.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

typedef glm::mat<4, 4, float, (glm::qualifier)0U> Matrix;
typedef glm::mat2 Matrix2D;
typedef glm::mat3 Matrix3D;
typedef glm::mat4 Matrix4D;
typedef glm::vec<3, float, (glm::qualifier)0U> Vector;
typedef glm::vec2 Vector2;
typedef glm::vec3 Vector3;
typedef glm::vec4 Vector4;

#define PI = 3.14159265358979

inline Vector3 Vector3UP = Vector3(0.0f, 1.0f, 0.0f);
inline Vector3 Vector3Down = Vector3(0.0f, -1.0f, 0.0f);
inline Vector3 Vector3Zero = Vector3(0.0f);

inline Matrix Transform(Matrix4D matrix, Vector3 Pos) {
  return glm::translate(matrix, Pos);
}

inline Matrix LookAt(Vector3 Eye, Vector3 Center, Vector3 UP) {
  return glm::lookAt(Eye, Center, UP);
}

inline float DegToRadians(float Deg) { return glm::radians(Deg); }

inline Vector Normalize(Vector x) { return glm::normalize(x); }

inline Matrix Perspective(float Fovy, float AspectRatio, float Near, float Far) {
  return glm::perspective(DegToRadians(Fovy), AspectRatio, Near, Far);
}

inline Matrix4D Translate(const Matrix4D &matrix, const Vector3 &translation) {
  return glm::translate(matrix, translation);
}

inline Matrix4D Rotate(const Matrix4D &matrix, float angleInDegrees, const Vector3 &axis) {
  return glm::rotate(matrix, angleInDegrees, axis);
}

inline Matrix4D Scale(const Matrix4D &matrix, const Vector3 &scale) {
  return glm::scale(matrix, scale);
}

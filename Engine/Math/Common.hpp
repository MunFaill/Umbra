#pragma once

#include <glm/glm.hpp>
#include "glm/ext/matrix_float2x2.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/ext/vector_float4.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_transform.hpp>

typedef glm::mat<4, 4, float, (glm::qualifier)0U> Matrix;
typedef glm::mat2 Matrix2D;
typedef glm::mat3 Matrix3D;
typedef glm::mat4 Matrix4D;
typedef glm::vec2 Vector2;
typedef glm::vec3 Vector3;
typedef glm::vec4 Vector4;

Matrix Transform(Matrix4D matrix, Vector3 Pos) {
    return glm::translate(matrix, Pos);
}
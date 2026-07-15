#pragma once

#include "Math/Common.hpp"

namespace Engine {
class Transform {
  public:
    Vector3 Position = Vector3(0.0f, 0.0f, 0.0f);
    Vector3 Rotation = Vector3(0.0f, 0.0f, 0.0f);
    Vector3 Scale = Vector3(1.0f, 1.0f, 1.0f);

    Transform() = default;
    Transform(Vector3 position, Vector3 rotation = Vector3Zero, Vector3 scale = Vector3(1.0f));

    Matrix4D GetModelMatrix() const;

  };
} // namespace Engine

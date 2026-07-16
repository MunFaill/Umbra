#pragma once

#include "Math/Common.hpp"
#include "Math/Transform.hpp"
#include "Objects/Object3D.hpp"
#include "Penumbra/PShader.hpp"
#include "Tools/Asset.hpp"

namespace Engine {
	class Camera3D : public Object3D {
	    public:
	    	float Fovy;
			float Near = 0.1f;
			float Far = 100.0f;
	    	bool Current;
			Vector3 Up = Vector3UP;

	    	inline Camera3D(const std::string& name, float fovy, bool current) : Fovy(fovy), Current(current), Object3D(name) {transform.Rotation = Vector3(0.0f, -90.0f, 0.0f);}

	    	inline void Render(const std::string& ShaderID, unsigned int Width, unsigned int Height) {
				if (Current) {
	    			Shader& shader = Assets::Shaders.Get(ShaderID);

					float pitch = transform.Rotation.x;
					float yaw = transform.Rotation.y;

					Vector3 direction;
					direction.x = cos(DegToRadians(yaw)) * cos(DegToRadians(pitch));
					direction.y = sin(DegToRadians(pitch));
					direction.z = sin(DegToRadians(yaw)) * cos(DegToRadians(pitch));
					Vector3 orientation = Normalize(direction);

					Matrix4D view = LookAt(transform.Position, transform.Position + orientation, Up);
					Matrix4D projection = Perspective(Fovy, (float)Width / Height, Near, Far);

					shader.SetMat4("view", view);
					shader.SetMat4("projection", projection);
					}
	    	}
	};
}

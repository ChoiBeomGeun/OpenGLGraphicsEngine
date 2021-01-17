#pragma once
#include "Component.h"
#include <glm/glm.hpp>
class Transform : public Component {

public:
	Transform() : Component()
	{
		position = glm::vec3(0, 0, 0);
		rotation = glm::vec3(0, 0, 0);
		scale = glm::vec3(1, 1, 1);
		angle = 0.0f;
		u_v = glm::vec2(1.f, 1.f);
	}
	glm::vec3 GetPosition() { return position; }
	glm::vec3 GetRotation() { return rotation; }
	glm::vec3 GetScale() { return scale; }

	void SetPosition(const glm::vec3& pos) { position = pos; }
	void SetRotation(const glm::vec3& Rot) { rotation = Rot; }
	void SetScale(const glm::vec3& Scale) { scale = Scale; }

	float angle;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::vec2 u_v;
private:

};

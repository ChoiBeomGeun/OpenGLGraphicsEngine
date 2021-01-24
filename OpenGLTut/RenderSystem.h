#pragma once
#include "Types.h"
#include "System.hpp"
#include "Shader.h"
#include "Transform.h"
#include "Camera.h"
#include "ModelE.h"
#include <memory>
class RenderSystem : public System
{
public:
	void Init();

	void Update(float dt);

private:

	std::unique_ptr<Shader> shader;

	Entity mMainCamera;

	GLuint mVao{};
	GLuint mVboVertices{};
	GLuint mVboNormals{};
};

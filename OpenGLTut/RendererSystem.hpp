#pragma once
#include "Types.hpp"
#include "Shader.hpp"
#include "System.hpp"
#include "Model.hpp"
#include <memory>
class RendererSystem : public System
{
public:
	void Init();

	void Update(float dt);

private:
	Entity mMainCamera;

};

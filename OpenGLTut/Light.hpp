#pragma once
#include <glm/glm.hpp>
#include <memory>
#include "Shader.hpp"

struct Light
{
	glm::vec3 color = glm::vec3(1, 1, 1);
	glm::vec3 ambient = glm::vec3(1, 1, 1);
	glm::vec3 diffuse = glm::vec3(1, 1, 1);
	glm::vec3 specular = glm::vec3(1, 1, 1);
	std::unique_ptr<Shader> shader;
};
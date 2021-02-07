#include "RendererSystem.hpp"
#include "Model.hpp"
#include "System.hpp"
#include "Transform.hpp"
#include "Camera.hpp"
#include "Coordinator.hpp"
#include "IMGUISystem.hpp"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/common.hpp>
#include <stb_image.h>
extern Coordinator coordinator;

Camera  * mainCam= new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
Transform* mainCamTrans;

void RendererSystem::Init()
{
	stbi_set_flip_vertically_on_load(true);

	mMainCamera = coordinator.CreateEntity("Camera");
	auto tr =new Transform{
		glm::vec3(0,0,0),
	   glm::vec3(0,0,0),
	   glm::vec3(1,1,1)
	}; 

	coordinator.AddComponent(mMainCamera, tr);
	coordinator.AddComponent(mMainCamera, mainCam);

	mainCamTrans = tr;

	coordinator.AddEntityToSystem<IMGUISystem>(mMainCamera);
}

void RendererSystem::Update(float dt)
{
	
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (auto const& entity : mEntities)
	{
		const auto transform = coordinator.GetComponent<Transform>(entity);
		auto modele = coordinator.GetComponent<Model>(entity);

		if (modele != nullptr)
		{
			modele->shader->use();
			glm::mat4 projection = glm::perspective(glm::radians(mainCam->Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
			glm::mat4 view = mainCam->GetViewMatrix(mainCamTrans->position);
			modele->shader->setMat4("projection", projection);
			modele->shader->setMat4("view", view);
			glm::quat eulerToQuat(transform->rotation);
			// render the loaded model
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, transform->position);
			model *= glm::toMat4(eulerToQuat);
			model = glm::scale(model, transform->scale);
			modele->shader->setMat4("model", model);
			modele->Draw();
		}
	}
}





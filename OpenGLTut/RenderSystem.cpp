#include "RenderSystem.hpp"
#include "Coordinator.hpp"
//#include "Camera.h"

extern Coordinator gCoordinator;

//Camera mainCam;
//CLASS;;;;WOW

//void RenderSystem::Init()
//{
//	shader =std::make_unique<Shader>("Resources/vertexShader.vs", "Resources/fragmentShader.fs"); 
//
//	mMainCamera = gCoordinator.CreateEntity();
//
//	gCoordinator.AddComponent(
//		mMainCamera,
//		Transform{
//			glm::vec3(0,0,0),
//		   glm::vec3(0,0,0),
//		   glm::vec3(0,0,0)
//		});
//
//	gCoordinator.AddComponent(
//		mMainCamera,
//		Camera{
//
//		});
//
//	mainCam = gCoordinator.GetComponent<Camera>(mMainCamera);
//
//}
//
//void RenderSystem::Update(float dt)
//{
//	for (auto const& entity : mEntities)
//	{
//		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		auto const& transform = gCoordinator.GetComponent<Transform>(entity);
//		auto modele = gCoordinator.GetComponent<ModelE>(entity);
//
//		shader->use();
//
//		glm::mat4 projection = glm::perspective(glm::radians(mainCam.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
//		glm::mat4 view = mainCam.GetViewMatrix();
//		shader->setMat4("projection", projection);
//		shader->setMat4("view", view);
//
//		// render the loaded model
//		glm::mat4 model = glm::mat4(1.0f);
//		model = glm::translate(model, transform.position); // translate it down so it's at the center of the scene
//		model = glm::scale(model, transform.scale);	// it's a bit too big for our scene, so scale it down
//		shader->setMat4("model", model);
//		modele.Draw(*shader);
//	}
//}
//
//

void RenderSystem::Init()
{
	mEntities.insert(0);
}

void RenderSystem::Update(float dt)
{
}

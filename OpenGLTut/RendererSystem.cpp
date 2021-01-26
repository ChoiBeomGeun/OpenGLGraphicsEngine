#include "RendererSystem.hpp"
#include "Model.hpp"
#include "System.hpp"
#include "Transform.hpp"
#include "Camera.hpp"
#include "Coordinator.hpp"
extern Coordinator coordinator;

Camera  * mainCam= new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

void RendererSystem::Init()
{
	this->shader = std::make_unique<Shader>("Resources/vertexShader.vs", "Resources/fragmentShader.fs"); 

	mMainCamera = coordinator.CreateEntity();
	auto tr = Transform{
		glm::vec3(0,0,0),
	   glm::vec3(0,0,0),
	   glm::vec3(1,1,1)
	};
	coordinator.AddComponent(mMainCamera, &tr);

	coordinator.AddComponent(mMainCamera,&mainCam);
	
//	mainCam = coordinator.GetComponent<Camera>(mMainCamera);

}

void RendererSystem::Update(float dt)
{
	for (auto const& entity : mEntities)
	{
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		const auto transform = coordinator.GetComponent<Transform>(entity);
		auto modele = coordinator.GetComponent<Model>(entity);
	
		shader->use();

		if (modele != nullptr)
		{
			glm::mat4 projection = glm::perspective(glm::radians(mainCam->Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
			glm::mat4 view = mainCam->GetViewMatrix();
			shader->setMat4("projection", projection);
			shader->setMat4("view", view);

			// render the loaded model
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, transform->position); // translate it down so it's at the center of the scene
			model = glm::scale(model, transform->scale);	// it's a bit too big for our scene, so scale it down
			shader->setMat4("model", model);
			modele->Draw(*shader);
		}
	}
}





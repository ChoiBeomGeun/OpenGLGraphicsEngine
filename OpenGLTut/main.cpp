
#include <glad/glad.h>
#include <filesystem>
#include <iostream>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Transform.hpp"
#include "Coordinator.hpp"
#include "Camera.hpp"

#include "IMGUISystem.hpp"

Coordinator coordinator;

void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

int main()
{
    	glfwInit();
    	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
     
    	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    	if (window == NULL)
    	{
    		std::cout << "Failed to create GLFW window" << std::endl;
    		glfwTerminate();
    		return -1;
    	}
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);
        // tell GLFW to capture our mouse
        
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        // glad: load all OpenGL function pointers
    // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }
        // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    
        //stbi_set_flip_vertically_on_load(true);
    
        // configure global opengl state
        // -----------------------------
        
        glEnable(GL_DEPTH_TEST);
    
        gladLoadGL();
        
        coordinator.Init();
        coordinator.RegisterComponent<Camera>();
        coordinator.RegisterComponent<Transform>();
        coordinator.RegisterComponent<Model>();
        Entity entity = coordinator.CreateEntity();
        Transform tr = Transform{
            glm::vec3(0,0,0),
            glm::vec3(0,0,0),
            glm::vec3(1,1,1)
        };
    
        Model md = Model("Resources/backpack/backpack.obj");
        coordinator.AddComponent(entity, &md);
        coordinator.AddComponent(entity, &tr);
    
        auto renderSystem = coordinator.RegisterSystem<RendererSystem>();
        auto imguiSystem = coordinator.RegisterSystem<IMGUISystem>();
    
        coordinator.AddEntityToSystem<RendererSystem>(entity);
        coordinator.AddEntityToSystem<IMGUISystem>(entity);
        renderSystem->Init();
    
    #if _DEBUG
        imguiSystem->Init(window, "#version 130");
    #endif
    	while (!glfwWindowShouldClose(window))
    	{
    
    		processInput(window);
    
    
    
    
            glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            renderSystem->Update(1.0f);
    #if _DEBUG
            imguiSystem->Update(0.1f);
    #endif
            glfwSwapBuffers(window);
    
    
            glfwPollEvents();
    	}
    
    
    
        glfwTerminate();
    
    
    
      
    	return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

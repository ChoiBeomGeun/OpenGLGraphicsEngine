#if _DEBUG
#include "IMGUISystem.hpp"
#include "external/imgui/imgui.h"
#include "external/imgui/imgui_impl_opengl3.h"
#include "Transform.hpp"
#include "Coordinator.hpp"

extern Coordinator coordinator;
void IMGUISystem::Init(GLFWwindow* window, const char* version)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(version);
}

void IMGUISystem::Update(float dt)
{
    for (auto const& entity : mEntities)
    {
        // Poll and handle events (inputs, window resize, etc.)
         // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
         // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
         // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
         // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        bool show_demo_window = true;
        bool show_another_window = false;
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);
        const auto transform = coordinator.GetComponent<Transform>(entity);
        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            if (transform != nullptr)
            {
                auto a = std::to_string(entity);
                ImGui::Text(a.c_str());
                float vec3f[3] = { transform->position.x,transform->position.y,transform->position.z };
              
                ImGui::DragFloat3("Position", vec3f, 1, -1000000, 1000000);

                transform->position = glm::vec3(vec3f[0], vec3f[1], vec3f[2]);
            }

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        // Rendering
        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}


#endif
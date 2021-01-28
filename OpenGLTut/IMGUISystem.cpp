#if _DEBUG
#include "IMGUISystem.hpp"
#include "external/imgui/imgui.h"
#include "external/imgui/imgui_impl_opengl3.h"
#include "Transform.hpp"
#include "Coordinator.hpp"

extern Coordinator coordinator;

void GlmVecDragFloat3View(const char * text,glm::vec3& vec);
void TransformView(Transform& tr);
void MainMenuView();
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
    bool show_demo_window = true;
    bool show_another_window = false;
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);
    MainMenuView();
    ImGui::Begin("Object");
    if (ImGui::CollapsingHeader("ObjectList"))
    {
        char searchText[128] = "";
        ImGui::InputText("Search", searchText, ((int)(sizeof(searchText) / sizeof(*(searchText)))));

        for (auto const& entity : mEntities)
        {
            std::string entityName = coordinator.GetEntityName(entity);
            if (searchText != "")
            {
                if (entityName.find(searchText) == std::string::npos)
                    continue;
            }

            auto transform = coordinator.GetComponent<Transform>(entity);

            if (ImGui::TreeNode(entityName.c_str()))
            {
                if (transform != nullptr)
                {
                    TransformView(*transform);
                }
                ImGui::TreePop();
            }
        }
    }

    if (ImGui::CollapsingHeader("DebugInfos"))
    {
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }

    ImGui::End();
    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void MainMenuView()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {}
            if (ImGui::MenuItem("Copy", "CTRL+C")) {}
            if (ImGui::MenuItem("Paste", "CTRL+V")) {}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void TransformView(Transform & tr)
{
    GlmVecDragFloat3View("Position", tr.position);
    GlmVecDragFloat3View("Scale", tr.scale);
    GlmVecDragFloat3View("Rotation", tr.rotation);
}


void GlmVecDragFloat3View(const char * text,glm::vec3 & vec)
{
    float vec3f[3] = { vec.x,vec.y,vec.z };

    ImGui::DragFloat3(text, vec3f, 0.01f, -1000000, 1000000);

    vec = glm::vec3(vec3f[0], vec3f[1], vec3f[2]);
}

#endif
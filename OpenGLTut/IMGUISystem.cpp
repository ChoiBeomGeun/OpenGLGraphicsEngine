#if _DEBUG
#include "IMGUISystem.hpp"
#include "external/imgui/imgui.h"
#include "external/imgui/imgui_impl_opengl3.h"
#include "Transform.hpp"
#include "Coordinator.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include <filesystem>


struct ImguiModelViewData
{
public:
    void (*cilckAction)(string filePath);
    std::string fileName = "";
    std::string filePath = "";
};

struct ImguiLightViewData
{
public:
    void (*cilckAction)();
    std::string lightName = "";
};
extern Coordinator coordinator;

void GlmVecDragFloat3View(const char* text, glm::vec3& vec);
void TransformView(Transform& tr);
void MainMenuView();
void LightView(Light& light);
void ModelListViewInit();
void LoadModel(string filePath);
void ModelListView();
void LightListView();
void CameraView(Camera& cm);
std::vector<ImguiModelViewData> modeldataList;

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

    ModelListViewInit();
}
ImVec4 color;
void IMGUISystem::Update(float dt)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    MainMenuView();
    ImGui::Begin("Object");

 
    ImGuiColorEditFlags flags = ImGuiColorEditFlags_::ImGuiColorEditFlags_NoAlpha;
    ImGui::ColorEdit4("MyColor##4", (float*)&color, flags);
     
    if (ImGui::CollapsingHeader("ObjectList"))
    {
        char searchText[128] = "";
        ImGui::InputText("Search", searchText, ((int)(sizeof(searchText) / sizeof(*(searchText)))));

        for (auto const& entity : mEntities)
        {
            std::string entityName = std::to_string(entity)+"."+ coordinator.GetEntityName(entity);
            if (searchText != "")
            {
                if (entityName.find(searchText) == std::string::npos)
                    continue;
            }

            auto transform = coordinator.GetComponent<Transform>(entity);
            auto cm = coordinator.GetComponent<Camera>(entity);
            auto light = coordinator.GetComponent<Light>(entity);
            if (ImGui::TreeNode(entityName.c_str()))
            {
                if (light != nullptr)
                {
                    LightView(*light);
                }
                
                if (transform != nullptr)
                {
                    TransformView(*transform);
                }

                if (cm != nullptr)
                {
                    CameraView(*cm);
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
        if (ImGui::BeginMenu("Models"))
        {
            ModelListView();
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Lights"))
        {
            LightListView();
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}



void ModelListViewInit()
{
    modeldataList.clear();
    string path = "Resources/models";
    for (const auto& file : std::filesystem::directory_iterator(path))
    {
        for (const auto& inFile : std::filesystem::directory_iterator(file.path()))
        {
            std::string filePath = inFile.path().string();
            size_t objNamePos = filePath.find(".obj");
            if (objNamePos != std::string::npos)
            {
                std::replace(filePath.begin(), filePath.end(), '\\', '/');
                ImguiModelViewData data;
                data.fileName = filePath.substr(file.path().string().size()+1,objNamePos);
                data.cilckAction = LoadModel;
                data.filePath = filePath;
                modeldataList.push_back(data);
            }
            cout << inFile.path() << endl;
        }
        cout << file.path() << endl;
    }
}

void ModelListView()
{
    int count = 0;
    for (auto item : modeldataList)
    {
        if (ImGui::MenuItem(item.fileName.c_str()))
        {
            item.cilckAction(item.filePath);
        }
    }
}

void LightListView()
{
    int count = 0;
    for (auto item : modeldataList)
    {
        if (ImGui::MenuItem(item.fileName.c_str()))
        {
            item.cilckAction(item.filePath);
        }
    }
}


void LoadModel(string filePath)
{
    Entity entity = coordinator.CreateEntity("Model");

    Model * md =new Model(filePath);
    md->shader = std::make_unique<Shader>("Resources/vertexShader.vs", "Resources/fragmentShader.fs");
    coordinator.AddComponent(entity, md);
    coordinator.AddComponent(entity, new Transform());

    coordinator.AddEntityToSystem<RendererSystem>(entity);
    coordinator.AddEntityToSystem<IMGUISystem>(entity);
}

void LoadLight()
{
    Entity entity = coordinator.CreateEntity("Model");

    Model* md = new Model("Resources/models/backpack/backpack.obj");
    md->shader = std::make_unique<Shader>("Resources/vertexShader.vs", "Resources/fragmentShader.fs");
    coordinator.AddComponent(entity, md);
    coordinator.AddComponent(entity, new Transform());
    
    Light* light = new Light();
    light->shader = std::make_unique<Shader>("Resources/basic_lighting.vs", "Resources/basic_lighting.fs");
    coordinator.AddComponent(entity,light);

    coordinator.AddEntityToSystem<RendererSystem>(entity);
    coordinator.AddEntityToSystem<IMGUISystem>(entity);
}

void TransformView(Transform & tr)
{
    if (ImGui::TreeNode("Transform"))
    {
        GlmVecDragFloat3View("Position", tr.position);
        GlmVecDragFloat3View("Scale", tr.scale);
        GlmVecDragFloat3View("Rotation", tr.rotation);
        ImGui::TreePop();
    }
}

void CameraView(Camera & cm)
{
    if (ImGui::TreeNode("Camera"))
    {
        ImGui::DragFloat("Yaw", &cm.Yaw, 0.01f, -1000000, 1000000);
        ImGui::DragFloat("Pitch", &cm.Pitch, 0.01f, -1000000, 1000000);
        ImGui::DragFloat("Zoom", &cm.Zoom, 0.01f, -1000000, 1000000);
        cm.updateCameraVectors();
        ImGui::TreePop();
    }
}

void LightView(Light& light)
{
    ImGuiColorEditFlags flags = ImGuiColorEditFlags_::ImGuiColorEditFlags_NoAlpha;

    if (ImGui::TreeNode("Light"))
    {
        ImVec4 color(light.color.x, light.color.y, light.color.z,1.0f);
        ImGui::ColorEdit3("color", (float*)&color, flags);
        light.color = glm::vec3(color.x,color.y,color.z);

        ImVec4 diffuse(light.diffuse.x, light.diffuse.y, light.diffuse.z, 1.0f);
        ImGui::ColorEdit3("diffuse", (float*)&diffuse, flags);
        light.diffuse = glm::vec3(diffuse.x, diffuse.y, diffuse.z);

        ImVec4 specular(light.specular.x, light.specular.y, light.specular.z, 1.0f);
        ImGui::ColorEdit3("specular", (float*)&specular, flags);
        light.specular = glm::vec3(specular.x, specular.y, specular.z);

        ImVec4 ambient(light.ambient.x, light.ambient.y, light.ambient.z, 1.0f);
        ImGui::ColorEdit3("ambient", (float*)&ambient, flags);
        light.ambient = glm::vec3(ambient.x, ambient.y, ambient.z);

        ImGui::TreePop();
    }
}

void GlmVecDragFloat3View(const char * text,glm::vec3 & vec)
{
    float vec3f[3] = { vec.x,vec.y,vec.z };

    ImGui::DragFloat3(text, vec3f, 0.01f, -1000000, 1000000);

    vec = glm::vec3(vec3f[0], vec3f[1], vec3f[2]);
}

#endif
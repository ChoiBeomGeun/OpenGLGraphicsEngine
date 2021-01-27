#include "System.hpp"
#include "external/imgui/imgui_impl_glfw.h"

#if _DEBUG
class IMGUISystem : public System
{
public:
	void Init(GLFWwindow* window, const char* version);

	void Update(float dt);
};

#endif
#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <map>
#include <string>

class UI
{
public:
	ImGuiIO& io;
	ImGuiStyle& style;
	bool* isopen;
	std::map<std::string, ImFont*> fonts;
	UI(ImGuiIO& io, ImGuiStyle& style,bool* isopen);
};
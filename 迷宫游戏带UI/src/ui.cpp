#include "ui.h"
#include "alifont.hpp"
#include <map>
UI::UI(ImGuiIO& io, ImGuiStyle& style, bool* isopen)
	:io(io), style(style), isopen(isopen)
{
	ImFont* Font0 = this->io.Fonts->AddFontFromMemoryTTF((void*)alifont_data, alifont_size, 24.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
	ImFont* Font1 = this->io.Fonts->AddFontFromMemoryTTF((void*)alifont_data, alifont_size, 32.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
	ImFont* Font2 = this->io.Fonts->AddFontFromMemoryTTF((void*)alifont_data, alifont_size, 54.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
	this->fonts["small"] = Font0;
	this->fonts["middle"] = Font1;
	this->fonts["big"] = Font2;

	//���ô��ڵ�paddingΪ0��ͼƬ�ؼ���������
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	//���ô���Ϊ�ޱ߿�
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
}

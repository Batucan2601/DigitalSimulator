#include "GUI/GUIEditor.h"
#include <rlImGui.h>
namespace GUIEditor
{
	
	struct Editor
	{
		RenderTexture renderTexture; 
		EditorWindow window;
	};
	
	static Editor editor;
	void Init(int width, int height)
	{
		editor.renderTexture = LoadRenderTexture(width,height);
	}
	void BeginOffscreenDraw()
	{
		BeginTextureMode(editor.renderTexture);
		ClearBackground(WHITE);
	}
	void EndOffscreenDraw()
	{
		
		EndTextureMode();
		
	}
	void Draw()
	{
		if (ImGui::Begin("Editor", nullptr, ImGuiWindowFlags_NoScrollbar))
		{
			ImGui::Image((ImTextureID)&editor.renderTexture.texture,
				ImVec2((float)editor.renderTexture.texture.width, (float)editor.renderTexture.texture.height),
				ImVec2(0, 1), ImVec2(1, 0));  // Adjust UVs if necessary
			// update editor 
			ImVec2 windowPos = ImGui::GetWindowPos();
			ImVec2 windowSize = ImGui::GetWindowSize();
			ImVec2 imageMin = ImGui::GetItemRectMin(); // top-left of the drawn image in screen space
			ImVec2 imageMax = ImGui::GetItemRectMax();
			editor.window.window = {windowPos.x , windowPos.y , windowSize.x , windowSize.y};
			editor.window.borderWidth = ImGui::GetStyle().WindowBorderSize;
			editor.window.ImageMin = { imageMin.x ,imageMin.y};
			editor.window.ImageMax = { imageMax.x ,imageMax.y};
			ImGui::End();
		}
	}
	EditorWindow Window()
	{
		return editor.window;
	}
}
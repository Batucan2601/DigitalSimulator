#include "GUI/GUIEditor.h"
#include <rlImGui.h>
namespace GUIEditor
{
	struct Editor
	{
		RenderTexture renderTexture; 
		Rectangle window;
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
		if (ImGui::Begin("Editor"))
		{
			ImGui::Image((ImTextureID)&editor.renderTexture.texture,
				ImVec2((float)editor.renderTexture.texture.width, (float)editor.renderTexture.texture.height),
				ImVec2(0, 0), ImVec2(1, 1));  // Adjust UVs if necessary
			// update editor 
			ImVec2 windowPos = ImGui::GetWindowPos();
			ImVec2 windowSize = ImGui::GetWindowSize();
			editor.window = { windowPos.x,windowPos.y,windowSize.x, windowSize.y };

			ImGui::End();
		}
	}
}
#include "UIScene.h"
#include "Game.h"

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

#include <SDL.h>

UIScene::UIScene(Game* game) : IScene(game)
{
}

void UIScene::processEvents()
{
    SDL_Event event = { 0 };

    while (SDL_PollEvent(&event)) {
        // imgui handle event
        ImGui_ImplSDL2_ProcessEvent(&event);

        // handle quit
        if (event.type == SDL_QUIT) {
            getGameRef()->stopRunning();
        }
    }
}

void UIScene::UIDrawTextCentered(const std::string& text)
{
    auto window_width = ImGui::GetWindowSize().x;
    auto text_width = ImGui::CalcTextSize(text.c_str()).x;

    ImGui::SetCursorPosX((window_width - text_width) * 0.5f);
    ImGui::Text("%s", text.c_str());
}

bool UIScene::UIDrawButtonCentered(const std::string& text)
{
    auto window_width = ImGui::GetWindowSize().x;
    auto text_width = ImGui::CalcTextSize(text.c_str()).x;

    ImGui::SetCursorPosX((window_width - 200) * 0.5f);
    return ImGui::Button(text.c_str(), ImVec2(200, 30));
}

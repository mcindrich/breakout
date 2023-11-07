#include "HUDScene.h"
#include "LevelScene.h"
#include "Game.h"

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

HUDScene::HUDScene(Game* game, LevelScene* level_scene) : UIScene(game), m_levelScene(level_scene)
{
}

void HUDScene::update(float delta)
{
    // Start the Dear ImGui frame
    auto& io = ImGui::GetIO();

    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    auto viewport = ImGui::GetMainViewport();

    ImGui::SetNextWindowPos(ImVec2(viewport->WorkSize.x / 2 - 200, viewport->WorkSize.y / 2 - 100));
    ImGui::SetNextWindowSize(ImVec2(400, 200));

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground;

    ImGui::Begin("MainMenuWindow", nullptr, flags);

    auto title = "breakout";
    auto description = "Breakout Game C++ Implementation";

    // title + description
    UIDrawTextCentered(title);
    ImGui::SetCursorPosY(30);
    UIDrawTextCentered(description);

    // buttons
    ImGui::SetCursorPosY(60);

    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(32, 153, 64, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor(32 / 2, 153 / 2, 64 / 2, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor(16, 16, 16, 255));

    if (UIDrawButtonCentered("Play"))
    {
        getGameRef()->setCurrentScene("Level0Scene");
    }
    if (UIDrawButtonCentered("Quit"))
    {
        getGameRef()->stopRunning();
    }

    ImGui::PopStyleColor(3);
    ImGui::End();
}

void HUDScene::render(SDL_Renderer* renderer)
{
    // Rendering
    auto& io = ImGui::GetIO();

    ImGui::Render();
    SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
}

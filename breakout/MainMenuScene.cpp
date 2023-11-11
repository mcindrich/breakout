#include "MainMenuScene.h"
#include "Game.h"

#include <SDL.h>

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

MainMenuScene::MainMenuScene(Game& game) : UIScene(game)
{
}

void MainMenuScene::update(float delta)
{
    // Start the Dear ImGui frame
    auto& io = ImGui::GetIO();

    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    auto viewport = ImGui::GetMainViewport();

    ImGui::SetNextWindowPos(ImVec2(viewport->WorkSize.x / 2 - 200, viewport->WorkSize.y / 2 - 100));
    ImGui::SetNextWindowSize(ImVec2(400, 200));

    ImGui::Begin("MainMenuWindow", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoTitleBar);

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
        getGameRef().setCurrentScene("Level1Scene");
    }
    if (UIDrawButtonCentered("Quit"))
    {
        getGameRef().stopRunning();
    }
    
    ImGui::PopStyleColor(3);
    ImGui::End();
}

void MainMenuScene::render(SDL_Renderer* renderer)
{
    // Rendering
    auto& io = ImGui::GetIO();

    ImGui::Render();
    SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
    SDL_RenderClear(renderer);
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
}
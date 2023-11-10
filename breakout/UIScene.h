#pragma once

#include "Scene.h"

#include <string>

class UIScene :
    public Scene
{
public:
    UIScene(Game& game);

    virtual void processEvents() override;

protected:
    void UIDrawTextCentered(const std::string& text);
    bool UIDrawButtonCentered(const std::string& text);
};


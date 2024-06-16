/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Menu.h
Project:    CS230 Engine
Author:     Donghyeon Jo
Created:    March 14, 2024
*/

#pragma once
#include "..\Engine\GameState.h"
#include "..\Engine\Texture.h"

class Menu : public CS230::GameState {
public:
    Menu();
    void Load() override;
    void Update([[maybe_unused]] double dt) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override {
        return "Menu";
    }

private:
    CS230::Texture* title_texture;
    CS230::Texture* mode1_texture;
    CS230::Texture* mode2_texture;
    CS230::Texture* mode3_texture;
    CS230::Texture* exit_texture;
    int select;
    const int max_select=4;

    void update_select_text(int select, unsigned int color);
};
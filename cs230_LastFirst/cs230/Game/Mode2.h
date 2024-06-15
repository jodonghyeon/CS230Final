/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode2.h
Project:    CS230 Engine
Author:     Donghyeon Jo
Created:    March 14, 2024
*/

#pragma once
#include "../Engine/GameState.h"
#include "../Engine/Texture.h"
#include "../Engine/Sprite.h"
#include "../Engine/Window.h"
#include "Ship.h"

class Mode2 : public CS230::GameState {
public: 
    Mode2();
    void Load() override;  
    void Update([[maybe_unused]] double dt) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override {
        return "Mode2";
    }

    static constexpr double meteor_timer = 4.5;

private:
    Ship* ship;

    CS230::Texture* score_texture;
    int last_score;

    CS230::Texture* gameover_texture;
    CS230::Texture* restart_texture;
};
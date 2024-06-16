/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode1.h
Project:    CS230 Engine
Author:     Donghyeon Jo
Created:    March 14, 2024
*/

#pragma once
#include "..\Engine\GameState.h"
#include "..\Engine\Sprite.h"
#include "..\Engine\GameObjectManager.h"
#include "Background.h"

class Cat;

class Mode1 : public CS230::GameState {
public:
    Mode1();
    void Load() override;
    void Update([[maybe_unused]] double dt) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override {
        return "Mode1";
    }

    static constexpr double gravity = 800.0;
    static constexpr double floor = 80.0;
    static constexpr double timer_max = 60.0;

private:
    Cat* cat_ptr;
    CS230::Texture* timer_texture;
    int last_time;
    CS230::Texture* score_texture;
    int last_score;

    void update_timer_text(int value);
};
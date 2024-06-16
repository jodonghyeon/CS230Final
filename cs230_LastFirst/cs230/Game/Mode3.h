/*
File Name:  Mode3.h
Project:    CS230 Final
Author:     Donghyeon Jo
Created:    June 16, 2024
*/

#pragma once
#include "..\Engine\GameState.h"
#include "..\Engine\Sprite.h"
#include "..\Engine\GameObjectManager.h"

class Ball;

class Mode3 : public CS230::GameState {
public:
    Mode3();
    void Load() override;
    void Update([[maybe_unused]] double dt) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override {
        return "Mode3";
    }

    const int window_width = 1280;
    const int window_height = 720;
    const int map_width = 12800;
    const int map_height = 3120;
    const double dampingFactor = 0.9999;

    const double gravity = 800.0;

    const double stage1_floor = 0.0;
    const double stage2_floor = 600.0;
    const double stage3_floor = 1200.0;
    const double stage4_floor = 1800.0;
    const double stage5_floor = 2400.0;

private:
    Ball* ball_ptr;
};
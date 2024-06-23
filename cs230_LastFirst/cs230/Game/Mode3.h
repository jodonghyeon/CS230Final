/*
File Name:  Mode3.h
Project:    CS230 Final
Author:     Donghyeon Jo
Created:    June 16, 2024
*/

#pragma once
#include "..\Engine\GameState.h"
#include "..\Engine\GameObjectManager.h"
#include "..\Engine\GameAudio.h"

class Ball;
class BigPin;

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

    static constexpr int window_width = 1280;
    static constexpr int window_height = 720;
    static constexpr int map_width = 12840;
    static constexpr int map_height = 3120;
    static constexpr double dampingFactor = 0.9;
    static constexpr double camera_offset1Y = 200.0;
    static constexpr double camera_offset1X = -90.0;
    static constexpr double camera_offsetX_level_diff = 5.3;

    static constexpr double gravity = 800.0;

    static constexpr int stage_height = 600;
    static constexpr int unit_block_side = 60;

    static constexpr double tutorial_time = 2.0;
    static constexpr double ending_time = 5.0;

    bool tutorial;
    double timer;
    bool game_ending;
    bool game_clear;

private:
    Ball* ball_ptr;
    BigPin* big_pin_ptr;
    CS230::GameMusic* bgm;
    CS230::GameSound* ending_sound;
    CS230::Texture* tutorial_text;
    CS230::Texture* game_ending_text;
};
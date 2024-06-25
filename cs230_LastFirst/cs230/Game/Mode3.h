/*
This is a game that is the final project of the cs230 course
We added a game called 'Unstoppable BB' using the cs230 game engine.
This game is a side-scrolling platformer running action game. ¡°The unstoppable bowling ball goes on an adventure to the ends of the sky!¡±

Aim by moving the mouse cursor.
Press the space bar to dash in the aimed direction.

You can attack, jump, do everything with just a dash!
Dashing consumes stamina, and without stamina you cannot dash.
Bowling balls have levels. The speed increases with level.
You can dash and catch mobs of the same or lower level and gain experience points. When your experience points are full, you level up.
If you collide with a mob while not in dash mode, or if you collide with a higher level mob, you will take damage and the bowling ball's level will drop.
If you take damage at level 1 or fall into a pit, it's game over. The game will restart.
*/


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
    bool game_clear;

private:
    Ball* ball_ptr;
    BigPin* big_pin_ptr;
    CS230::GameMusic* bgm;
    CS230::Texture* tutorial_text;
};
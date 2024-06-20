/*
File Name:  StatusBar.h
Project:    CS230 Final
Author:     Donghyeon Jo
Created:    June 19, 2024
*/

#pragma once
#include "..\Engine\Component.h"
#include "..\Engine\Vec2.h"
#include "..\Engine\Texture.h"
#include "Level.h"
#include "Stamina.h"

class StatusBar : public CS230::Component {
public:
    StatusBar(Math::vec2 level_position, Math::vec2 exp_position, Math::vec2 stamina_position, Level* given_level_ptr, Stamina* given_stamina_ptr);
    void Draw();
private:
    CS230::Texture* level1_text;
    CS230::Texture* level2_text;
    CS230::Texture* level3_text;
    CS230::Texture* level4_text;
    CS230::Texture* level5_text;

    CS230::Texture* level1;
    CS230::Texture* level2;
    CS230::Texture* level3;
    CS230::Texture* level4;
    CS230::Texture* level5;

    CS230::Texture* exp_back_texture;
    CS230::Texture* exp_front_texture;
    CS230::Texture* stamina_back_texture;
    CS230::Texture* stamina_front_texture;

    Math::vec2 level_position;
    Math::vec2 exp_position;
    Math::vec2 stamina_position;

    Level* level_ptr;
    Stamina* stamina_ptr;
};
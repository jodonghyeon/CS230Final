/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Meteor.h
Project:    CS230 Engine
Author:     Donghyeon Jo
Created:    May 1, 2024
*/

#pragma once
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

class Meteor : public CS230::GameObject {
public:
    Meteor();
    Meteor(Math::ivec2 window_size);
    Meteor(Meteor* parent);
    void Update(double dt)override;

    GameObjectType Type() override { return GameObjectType::Meteor; }
    std::string TypeName() override { return "Meteor"; }

    void ResolveCollision(GameObject* other_object)override;

private:
    enum class Animations {
        None,
        Fade
    };

    double health;
    int size;
    static constexpr double default_velocity = 100;
    static constexpr double default_size = 2.0;
    static constexpr double default_healths[] = { 3, 5, 8 };
    static constexpr double default_scales[] = { 0.5, 0.75, 1.0 };
};


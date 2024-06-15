/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Ship.h
Project:    CS230 Engine
Author:     Donghyeon Jo
Created:    March 31, 2024
*/

#pragma once
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

class Ship : public CS230::GameObject{
public:
    Ship(Math::vec2 position, double rotation, Math::vec2 scale);
    void Update(double dt)override;
    void Draw(Math::TransformationMatrix camera_matrix)override;

    GameObjectType Type() override { return GameObjectType::Ship; }
    std::string TypeName() override { return "Ship"; }
    bool CanCollideWith(GameObjectType other_object_type)override;
    void ResolveCollision(GameObject* other_object)override;

    bool Exploded();

    enum class Animations {
        None,
        Explosion
    };

    enum Flame_Animations {
        Off,
        On
    };

private:
    CS230::Sprite flame_left;
    CS230::Sprite flame_right;

    static constexpr double speed = 700;
    static constexpr double drag = 1;
    static constexpr double rotation_speed = 10;
    bool ignition;
    bool exploded;
};

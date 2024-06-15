/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Laser.h
Project:    CS230 Engine
Author:     Donghyeon Jo
Created:    June 2, 2024
*/

#pragma once
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

class Laser : public CS230::GameObject {
public:
    Laser(Math::vec2 pos, double rot, Math::vec2 scale, Math::vec2 vel);
    GameObjectType Type() override { return GameObjectType::Laser; }
    std::string TypeName() override { return "Laser"; }
    void Update(double dt) override;
    bool CanCollideWith(GameObjectType other_object_type) override;
    void ResolveCollision(GameObject* other_object) override;

    static constexpr double DefaultVelocity = 600;
};

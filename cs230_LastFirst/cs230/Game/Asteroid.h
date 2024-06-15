/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Asteroid.h
Project:    CS230 Engine
Author:     Donghyeon Jo
Created:    March 31, 2024
*/

#pragma once
#include "GameObjectTypes.h"

class Asteroid : public CS230::GameObject {
public:
    Asteroid(Math::vec2 start_position);

    GameObjectType Type() override { return GameObjectType::Asteroid; }
    std::string TypeName() override { return "Asteroid"; }
    bool CanCollideWith(GameObjectType other_object_type) override;
    void ResolveCollision(GameObject* other_object) override;

private:
    enum class Animations {
        Bounce,
        Land
    };

    class State_Bounce : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "bounce"; }
    };

    State_Bounce state_bounce;

    class State_Land : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "land"; }
    };

    State_Land state_land;

    static constexpr double bounce_velocity = 500;
};

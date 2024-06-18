/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Robot.h
Project:    CS230 Engine
Author:     Donghyeon Jo
Created:    May 1, 2024
*/

#pragma once
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"
#include "Cat.h"

class Robot : public CS230::GameObject {
public:
    Robot(Math::vec2 position, Cat* cat, double left_boundary, double right_boundary);

    GameObjectType Type() override { return GameObjectType::Robot; }
    std::string TypeName() override { return "Robot"; }
    void ResolveCollision(GameObject* other_object)override;

    static constexpr double walking_speed = 75.0;
    static constexpr double angry_speed = 105.0;

private:
    enum class Animations {
        None,
        Dead,
        Walking,
        Angry
    };

    class State_Dead : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "dead"; }
    };

    State_Dead state_dead;

    class State_Walking : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "walking"; }
    };

    State_Walking state_walking;

    class State_Angry : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "angry"; }
    };

    State_Angry state_angry;

    Cat* cat_ptr;
    const double left_boundary;
    const double right_boundary;
};

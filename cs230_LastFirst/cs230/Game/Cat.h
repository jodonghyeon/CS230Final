/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Cat.h
Project:    CS230 Engine
Author:     Donghyeon Jo
Created:    March 31, 2024
*/

#pragma once
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"
#include "..\Engine\Timer.h"

class Cat : public CS230::GameObject {
public:
    Cat(Math::vec2 start_position);
    void Update(double dt) override;
    void Draw(Math::TransformationMatrix camera_matrix) override;

    GameObjectType Type() override { return GameObjectType::Cat; }
    std::string TypeName() override { return "Cat"; }
    bool CanCollideWith(GameObjectType other_object_type) override;
    void ResolveCollision(GameObject* other_object) override;

    const Math::vec2& GetPosition() const { return GameObject::GetPosition(); }

    static constexpr double LargeFallHeight = 250.0;

private:
    static constexpr double x_acceleration = 200;
    static constexpr double x_drag = 450;
    static constexpr double max_velocity = 400;
    static constexpr double jump_velocity = 650;
    bool stopped = false;

    static constexpr double hurt_time = 2.0;
    static constexpr double hurt_velocity = 350;
    static constexpr double hurt_acceleration = 300;
    static constexpr double bounce_velocity = 700;
    static constexpr double pop_velocity = 400;

    CS230::Timer* hurt_timer;
    CS230::GameObject* standing_on;

    void update_x_velocity(double dt);

    enum class Animations {
        Idle,
        Running,
        Jumping,
        Falling,
        Skidding
    };

    class State_Jumping : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Jumping"; }
    };

    State_Jumping state_jumping;

    class State_Idle : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Idle"; }
    };

    State_Idle state_idle;

    class State_Falling : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Falling"; }
    };

    State_Falling state_falling;

    class State_Running : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Running"; }
    };

    State_Running state_running;

    class State_Skidding : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Skidding"; }
    };

    State_Skidding state_skidding;

};


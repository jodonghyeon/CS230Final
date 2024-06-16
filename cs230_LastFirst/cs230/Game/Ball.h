/*
File Name:  Ball.h
Project:    CS230 Final
Author:     Donghyeon Jo
Created:    June 16, 2024
*/

#pragma once
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

class Ball : public CS230::GameObject {
public:
    Ball(Math::vec2 start_position);
    void Update(double dt) override;
    void Draw(Math::TransformationMatrix camera_matrix) override;

    GameObjectType Type() override { return GameObjectType::Ball; }
    std::string TypeName() override { return "Ball"; }
    bool CanCollideWith(GameObjectType other_object_type) override;
    void ResolveCollision(GameObject* other_object) override;

    const Math::vec2& GetPosition() const { return GameObject::GetPosition(); }

    const int GetPowerLevel()const { return power_level; }

private:
    static constexpr int max_power_level = 5;
    static constexpr double velocity_rolling1 = 400.0;
    static constexpr double velocity_diff = 100.0;
    static constexpr double dash_velocity_rate = 5.0;

    int power_level;
    CS230::GameObject* standing_on;

    void update_x_velocity(double dt);

    enum class Animations {
        Rolling1,
        Rolling2,
        Rolling3,
        Rolling4,
        Rolling5,
        Dashing,
        Dead
    };

    class State_Rolling : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Rolling"; }
    };

    State_Rolling state_rolling;

    class State_Dashing : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Dashing"; }
    };

    State_Dashing state_dashing;

    class State_Dead : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Dead"; }
    };

    State_Dead state_dead;

};
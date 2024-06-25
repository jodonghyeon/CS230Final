/*
File Name:  Ball.h
Project:    CS230 Final
Author:     Donghyeon Jo
Created:    June 16, 2024
*/

#pragma once
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"
#include "..\Engine\GameAudio.h"

class Ball : public CS230::GameObject {
public:
    Ball(Math::vec2 start_position, int start_level);
    void Update(double dt) override;
    void Draw(Math::TransformationMatrix camera_matrix) override;

    GameObjectType Type() override { return GameObjectType::Ball; }
    std::string TypeName() override { return "Ball"; }
    bool CanCollideWith(GameObjectType other_object_type) override;
    void ResolveCollision(GameObject* other_object) override;

    const Math::vec2& GetPosition() const { return GameObject::GetPosition(); }

    void PlayLevelAnimation();


private:

    static constexpr int max_level = 5;
    static constexpr double exp_max1 = 100.0;
    static constexpr double exp_max_level_diff = 100.0;
    static constexpr double stamina_max1 = 1.0;
    static constexpr double velocity_rolling1 = 400.0;
    static constexpr double velocity_level_diff = 100.0;
    static constexpr double dash_velocity_rate = 2.2;
    static constexpr double stamina_charge = 0.3;
    static constexpr double stamina_consumption1 = 1.5;
    static constexpr double stamina_consumption_level_diff = 0.2;
    static constexpr double stamina_recovery1 = 1.0;
    static constexpr double stamina_recovery_level_diff = 0.2;
    static constexpr int dead_height = -120;

    CS230::GameObject* standing_on;
    CS230::GameObject* previous_enemy;

    CS230::GameSound* dashing_sound;
    CS230::GameSound* breaking_sound;
    CS230::GameSound* damaged_sound;
    CS230::GameSound* game_over_sound;

    Math::vec2 get_dash_velocity();

    enum class Animations {
        Rolling1,
        Rolling2,
        Rolling3,
        Rolling4,
        Rolling5,
        Dashing1,
        Dashing2,
        Dashing3,
        Dashing4,
        Dashing5,
        Falling1,
        Falling2,
        Falling3,
        Falling4,
        Falling5,
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

    class State_Falling : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Falling"; }
    };

    State_Falling state_falling;

    class State_Dead : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Dead"; }
    };

    State_Dead state_dead;

};
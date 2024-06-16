/*
File Name:  Ball.cpp
Project:    CS230 Final
Author:     Donghyeon Jo
Created:    June 16, 2024
*/

#include "..\Engine\Camera.h"
#include "Gravity.h"
#include "..\Engine\GameObject.h"
#include "Ball.h"
#include "..\Engine\Sprite.h"
#include "..\Engine\Input.h"
#include "..\Engine\Vec2.h"
#include "..\Engine\Matrix.h"
#include "..\Engine\Engine.h"
#include "..\Engine\Collision.h"

Ball::Ball(Math::vec2 start_position) 
    : GameObject(start_position), power_level(1), standing_on(nullptr)
{
    AddGOComponent(new CS230::Sprite("Assets/Ball.spt", this));
    current_state = &state_rolling;
    current_state->Enter(this);
}

void Ball::Update(double dt)
{
    GameObject::Update(dt);
    Engine::GetLogger().LogDebug("x: " + std::to_string(GetVelocity().x));
    CS230::DampingCamera* camera = Engine::GetGameStateManager().GetGSComponent<CS230::DampingCamera>();
    CS230::RectCollision* collider = GetGOComponent<CS230::RectCollision>();
    if (GetPosition().x - collider->WorldBoundary().Size().x / 2 < camera->GetPosition().x) {
        UpdatePosition({ camera->GetPosition().x + collider->WorldBoundary().Size().x / 2 - GetPosition().x, 0 });
    }
    if (GetPosition().x + collider->WorldBoundary().Size().x / 2 > camera->GetPosition().x + Engine::GetWindow().GetSize().x) {
        UpdatePosition({ camera->GetPosition().x + Engine::GetWindow().GetSize().x - collider->WorldBoundary().Size().x / 2 - GetPosition().x, 0 });
    }
}

void Ball::Draw(Math::TransformationMatrix camera_matrix)
{
    GameObject::Draw(camera_matrix);
}

bool Ball::CanCollideWith(GameObjectType other_object_type)
{
    if (other_object_type == GameObjectType::Particle) {
        return false;
    }
    return true;
}

void Ball::ResolveCollision(GameObject* other_object)
{
}

void Ball::update_x_velocity(double dt)
{
}

void Ball::State_Rolling::Enter(GameObject* object)
{
    Ball* ball = static_cast<Ball*>(object);
    ball->SetVelocity({ Ball::velocity_rolling1 + (ball->GetPowerLevel()-1) * Ball::velocity_diff,0 });
    ball->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Rolling1));
}

void Ball::State_Rolling::Update(GameObject* object, double dt)
{
    Ball* ball = static_cast<Ball*>(object);
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Space)) {
        ball->SetVelocity({ dash_velocity_rate *Ball::velocity_rolling1 + (ball->GetPowerLevel() - 1) * Ball::velocity_diff,0 });
    }
    else {
        ball->SetVelocity({ Ball::velocity_rolling1 + (ball->GetPowerLevel() - 1) * Ball::velocity_diff, 0 });
    }
}

void Ball::State_Rolling::CheckExit(GameObject* object)
{
}

void Ball::State_Dashing::Enter(GameObject* object)
{
}

void Ball::State_Dashing::Update(GameObject* object, double dt)
{
}

void Ball::State_Dashing::CheckExit(GameObject* object)
{
}

void Ball::State_Dead::Enter(GameObject* object)
{
}

void Ball::State_Dead::Update(GameObject* object, double dt)
{
}

void Ball::State_Dead::CheckExit(GameObject* object)
{
}
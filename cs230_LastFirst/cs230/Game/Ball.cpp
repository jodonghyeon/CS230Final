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
#include "Level.h"
#include "Stamina.h"

Ball::Ball(Math::vec2 start_position) 
    : GameObject(start_position),standing_on(nullptr)
{
    AddGOComponent(new CS230::Sprite("Assets/Ball.spt", this));
    AddGOComponent(new Level(*this, exp_max1));
    AddGOComponent(new Stamina(*this, stamina_max1));
    current_state = &state_falling;
    current_state->Enter(this);
}

void Ball::Update(double dt)
{
    Engine::GetLogger().LogDebug("stamina: " + std::to_string(GetGOComponent<Stamina>()->GetStamina()));

    GetGOComponent<Level>()->ResetIsLevelUpdated();
    GameObject::Update(dt);
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
    Math::rect ball_rect = GetGOComponent<CS230::RectCollision>()->WorldBoundary();
    Math::rect other_rect = other_object->GetGOComponent<CS230::RectCollision>()->WorldBoundary();
    switch (other_object->Type())
    {
    case GameObjectType::Platform:
        if (GetPosition().x > other_rect.Left() && GetPosition().x < other_rect.Right()) {
            if (ball_rect.Top() > other_rect.Top()) {
                SetPosition({ GetPosition().x, other_rect.Top() });
                standing_on = other_object;
                current_state->CheckExit(this);
                return;
            }
        }
        if (GetPosition().x > other_rect.Left() && GetPosition().x < other_rect.Right()) {
            if (ball_rect.Bottom() < other_rect.Bottom()) {
                SetPosition({ GetPosition().x, other_rect.Bottom() - ball_rect.Size().y });
                SetVelocity(Math::vec2(GetVelocity().x, 0));
                current_state->CheckExit(this);
                return;
            }
        }
        if (ball_rect.Left() < other_rect.Left()) {
            UpdatePosition(Math::vec2{ (other_rect.Left() - ball_rect.Right()), 0.0 });
            SetVelocity({ 0, GetVelocity().y });
        }
        else {
            UpdatePosition(Math::vec2{ (other_rect.Right() - ball_rect.Left()), 0.0 });
            SetVelocity({ 0, GetVelocity().y });
        }
    default:
        break;
    }
}

Math::vec2 Ball::get_dash_velocity()
{
    Math::vec2 direction_vector = { Engine::GetGameStateManager().GetGSComponent<CS230::DampingCamera>()->GetPosition().x + Engine::GetInput().GetMousePosition().x - GetPosition().x,
        Engine::GetGameStateManager().GetGSComponent<CS230::DampingCamera>()->GetPosition().y + Engine::GetInput().GetMousePosition().y - GetPosition().y };

    Math::vec2 unit_direction_vector = direction_vector.Normalize();

    unit_direction_vector *= dash_velocity_rate;

    return Math::vec2{ unit_direction_vector.x * GetVelocity().x, unit_direction_vector.y * GetVelocity().x };
}

void Ball::State_Rolling::Enter(GameObject* object)
{
    Ball* ball = static_cast<Ball*>(object);
    ball->SetVelocity({ Ball::velocity_rolling1 + (ball->GetGOComponent<Level>()->GetLevel() - 1) * Ball::velocity_level_diff,0});
    ball->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Rolling1));
}

void Ball::State_Rolling::Update(GameObject* object, double dt)
{
    Ball* ball = static_cast<Ball*>(object);
    ball->GetGOComponent<Stamina>()->UpdateStamina((Ball::stamina_recovery1+Ball::stamina_recovery_level_diff*(ball->GetGOComponent<Level>()->GetLevel() -1)) * dt);
}

void Ball::State_Rolling::CheckExit(GameObject* object)
{
    Ball* ball = static_cast<Ball*>(object);
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Space) &&
        Engine::GetGameStateManager().GetGSComponent<CS230::DampingCamera>()->GetPosition().x + Engine::GetInput().GetMousePosition().x > ball->GetPosition().x) {
        ball->change_state(&ball->state_dashing);
        ball->GetGOComponent<Level>()->LevelUp();
    }
    else if (ball->standing_on != nullptr && ball->standing_on->IsCollidingWith(ball->GetPosition()) == false) {
        ball->standing_on = nullptr;
        ball->change_state(&ball->state_falling);
    }
}

void Ball::State_Dashing::Enter(GameObject* object)
{
    Ball* ball = static_cast<Ball*>(object);
    ball->UpdateVelocity(ball->get_dash_velocity());
    ball->GetGOComponent<Stamina>()->UpdateStamina(-Ball::stamina_charge);
    ball->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Dashing));
}

void Ball::State_Dashing::Update(GameObject* object, double dt)
{
    Ball* ball = static_cast<Ball*>(object);
    ball->GetGOComponent<Stamina>()->UpdateStamina(-(Ball::stamina_consumption1+Ball::stamina_consumption_level_diff*(ball->GetGOComponent<Level>()->GetLevel()-1)) * dt);
}

void Ball::State_Dashing::CheckExit(GameObject* object)
{
    Ball* ball = static_cast<Ball*>(object);
    Engine::GetLogger().LogDebug("st:   "+std::to_string(Ball::stamina_consumption1 + Ball::stamina_consumption_level_diff * (ball->GetGOComponent<Level>()->GetLevel() - 1)));
    if (!Engine::GetInput().KeyDown(CS230::Input::Keys::Space)||  ball->GetGOComponent<Stamina>()->GetStamina() <= 0.0) {
        if (ball->standing_on != nullptr && ball->standing_on->IsCollidingWith(ball->GetPosition()) == false) {
            ball->standing_on = nullptr;
            ball->change_state(&ball->state_falling);
        }
        else {
            ball->change_state(&ball->state_rolling);
        }
    }
}

void Ball::State_Falling::Enter(GameObject* object)
{
    Ball* ball = static_cast<Ball*>(object);
    ball->SetVelocity({ Ball::velocity_rolling1 + (ball->GetGOComponent<Level>()->GetLevel() - 1) * Ball::velocity_level_diff,0 });
    ball->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Falling));
}

void Ball::State_Falling::Update(GameObject* object, double dt)
{
    Ball* ball = static_cast<Ball*>(object);
    ball->UpdateVelocity({ 0,-Engine::GetGameStateManager().GetGSComponent<Gravity>()->GetValue() * dt });
}

void Ball::State_Falling::CheckExit(GameObject* object)
{
    Ball* ball = static_cast<Ball*>(object);
    if (ball->standing_on != nullptr) {
        ball->change_state(&ball->state_rolling);
    }

    if (ball->GetPosition().y < Ball::dead_height) {
        Engine::GetGameStateManager().ReloadState();
    }
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

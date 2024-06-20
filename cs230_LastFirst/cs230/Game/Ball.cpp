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
#include "Pin.h"
#include "Dumbbell.h"
#include "Cone.h"
#include "Drone.h"
#include "Orb.h"
#include "BigPin.h"
#include "..\Engine\GameAudio.h"
#include "StatusBar.h"
#include "Mode3.h"
#include "..\Engine\Particle.h"
#include "Particles.h"

Ball::Ball(Math::vec2 start_position) 
    : GameObject(start_position),standing_on(nullptr),previous_enemy(nullptr)
{
    AddGOComponent(new CS230::Sprite("Assets/Ball.spt", this));
    Level* level = new Level(*this, exp_max1, max_level);
    AddGOComponent(level);

    Stamina* stamina = new Stamina(*this, stamina_max1);
    AddGOComponent(stamina);

    AddGOComponent(new StatusBar({ (double)Engine::GetWindow().GetSize().x / 20, (double)Engine::GetWindow().GetSize().y * 8 / 10 }, { (double)Engine::GetWindow().GetSize().x / 9, (double)Engine::GetWindow().GetSize().y * 19 / 20 }, { (double)Engine::GetWindow().GetSize().x / 9, (double)Engine::GetWindow().GetSize().y * 17 / 20 }, level, stamina));
    
    current_state = &state_falling;
    current_state->Enter(this);
    dashing_sound = Engine::GetGameAudioManager().LoadSound("Assets/DashingSound.mp3");
    breaking_sound = Engine::GetGameAudioManager().LoadSound("Assets/BreakingSound.mp3");
    damaged_sound = Engine::GetGameAudioManager().LoadSound("Assets/DamagedSound.mp3");
    game_over_sound = Engine::GetGameAudioManager().LoadSound("Assets/GameOverSound.mp3");
}

void Ball::Update(double dt)
{
    //Engine::GetLogger().LogDebug("stamina: " + std::to_string(GetGOComponent<Stamina>()->GetStamina()));
    //Engine::GetLogger().LogDebug("Level: "+std::to_string(GetGOComponent<Level>()->GetLevel()));
    GameObject::Update(dt);
}

void Ball::Draw(Math::TransformationMatrix camera_matrix)
{
    GameObject::Draw(camera_matrix);
    GetGOComponent<StatusBar>()->Draw();
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
    if (previous_enemy == other_object) {
        return;
    }

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
        break;
    case GameObjectType::Portal:
        SetPosition(Math::vec2{ -Mode3::unit_block_side*5,GetPosition().y });
        UpdatePosition(Math::vec2{ 0,Mode3::stage_height });
        break;
    case GameObjectType::Pin:
        previous_enemy = other_object;
        if (current_state == &state_dashing && GetGOComponent<Level>()->GetLevel() >= Pin::level_default) {
            GetGOComponent<Level>()->UpdateEXP(Pin::exp_give);
            GetGOComponent<Level>()->SetEXPMax(exp_max1 + exp_max_level_diff * (GetGOComponent<Level>()->GetLevel() - 1));
            other_object->ResolveCollision(this);
            Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::ParticleRed>>()->Emit(15, GetPosition(), { 0, 0 }, { GetVelocity().x, 0 }, PI / 6);
            breaking_sound->Play();
        }
        else {
            GetGOComponent<Level>()->LevelDown();
            if (GetGOComponent<Level>()->GetLevel() != 0) {
                GetGOComponent<Level>()->SetEXPMax(exp_max1 + exp_max_level_diff * (GetGOComponent<Level>()->GetLevel() - 1));
            }
            damaged_sound->Play();
            PlayLevelAnimation();
        }
        break;
    case GameObjectType::Dumbbell:
        previous_enemy = other_object;
        if (current_state == &state_dashing && GetGOComponent<Level>()->GetLevel() >= Dumbbell::level_default) {
            GetGOComponent<Level>()->UpdateEXP(Dumbbell::exp_give);
            GetGOComponent<Level>()->SetEXPMax(exp_max1 + exp_max_level_diff * (GetGOComponent<Level>()->GetLevel() - 1));
            other_object->ResolveCollision(this);
            Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::ParticleYellow>>()->Emit(15, GetPosition(), { 0, 0 }, { GetVelocity().x, 0 }, PI / 6);
            breaking_sound->Play();
        }
        else {
            GetGOComponent<Level>()->LevelDown();
            if (GetGOComponent<Level>()->GetLevel() != 0) {
                GetGOComponent<Level>()->SetEXPMax(exp_max1 + exp_max_level_diff * (GetGOComponent<Level>()->GetLevel() - 1));
            }
            damaged_sound->Play();
            PlayLevelAnimation();
        }
        break;
    case GameObjectType::Cone:
        previous_enemy = other_object;
        if (current_state == &state_dashing && GetGOComponent<Level>()->GetLevel() >= Cone::level_default) {
            GetGOComponent<Level>()->UpdateEXP(Cone::exp_give);
            GetGOComponent<Level>()->SetEXPMax(exp_max1 + exp_max_level_diff * (GetGOComponent<Level>()->GetLevel() - 1));
            other_object->ResolveCollision(this);
            Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::ParticleGreen>>()->Emit(15, GetPosition(), { 0, 0 }, { GetVelocity().x, 0 }, PI / 6);
            breaking_sound->Play();
        }
        else {
            GetGOComponent<Level>()->LevelDown();
            if (GetGOComponent<Level>()->GetLevel() != 0) {
                GetGOComponent<Level>()->SetEXPMax(exp_max1 + exp_max_level_diff * (GetGOComponent<Level>()->GetLevel() - 1));
            }
            damaged_sound->Play();
            PlayLevelAnimation();
        }
        break;
    case GameObjectType::Drone:
        previous_enemy = other_object;
        if (current_state == &state_dashing && GetGOComponent<Level>()->GetLevel() >= Drone::level_default) {
            GetGOComponent<Level>()->UpdateEXP(Drone::exp_give);
            GetGOComponent<Level>()->SetEXPMax(exp_max1 + exp_max_level_diff * (GetGOComponent<Level>()->GetLevel() - 1));
            other_object->ResolveCollision(this);
            Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::ParticleBlue>>()->Emit(15, GetPosition(), { 0, 0 }, { GetVelocity().x, 0 }, PI / 6);
            breaking_sound->Play();
        }
        else {
            GetGOComponent<Level>()->LevelDown();
            if (GetGOComponent<Level>()->GetLevel() != 0) {
                GetGOComponent<Level>()->SetEXPMax(exp_max1 + exp_max_level_diff * (GetGOComponent<Level>()->GetLevel() - 1));
            }
            damaged_sound->Play();
            PlayLevelAnimation();
        }
        break;
    case GameObjectType::Orb:
        previous_enemy = other_object;
        if (current_state == &state_dashing && GetGOComponent<Level>()->GetLevel() >= Orb::level_default) {
            GetGOComponent<Level>()->UpdateEXP(Orb::exp_give);
            GetGOComponent<Level>()->SetEXPMax(exp_max1 + exp_max_level_diff * (GetGOComponent<Level>()->GetLevel() - 1));
            other_object->ResolveCollision(this);
            Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::ParticleGrey>>()->Emit(15, GetPosition(), { 0, 0 }, { GetVelocity().x, 0 }, PI / 6);
            breaking_sound->Play();
        }
        else {
            GetGOComponent<Level>()->LevelDown();
            if (GetGOComponent<Level>()->GetLevel() != 0) {
                GetGOComponent<Level>()->SetEXPMax(exp_max1 + exp_max_level_diff * (GetGOComponent<Level>()->GetLevel() - 1));
            }
            damaged_sound->Play();
            PlayLevelAnimation();
        }
        break;
    case GameObjectType::BigPin:
        if (current_state == &state_dashing && GetGOComponent<Level>()->GetLevel() >= BigPin::level_default) {
            other_object->ResolveCollision(this);
            SetVelocity({ 0,0 });
        }
        else {
            GetGOComponent<Level>()->UpdateLevel(-GetGOComponent<Level>()->GetLevel());
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
    Engine::GetLogger().LogDebug(std::to_string(ball->GetGOComponent<Level>()->GetLevel()));
    ball->PlayLevelAnimation();
}

void Ball::State_Rolling::Update(GameObject* object, double dt)
{
    Ball* ball = static_cast<Ball*>(object);
    ball->GetGOComponent<Stamina>()->UpdateStamina((Ball::stamina_recovery1+Ball::stamina_recovery_level_diff*(ball->GetGOComponent<Level>()->GetLevel() -1)) * dt);
}

void Ball::State_Rolling::CheckExit(GameObject* object)
{
    Ball* ball = static_cast<Ball*>(object);
    if (ball->GetGOComponent<Level>()->GetLevel() <= 0) {
        ball->change_state(&ball->state_dead);
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Space) &&
        Engine::GetGameStateManager().GetGSComponent<CS230::DampingCamera>()->GetPosition().x + Engine::GetInput().GetMousePosition().x > ball->GetPosition().x) {
        ball->change_state(&ball->state_dashing);
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
    ball->PlayLevelAnimation();
    ball->dashing_sound->Play();
    switch (ball->GetGOComponent<Level>()->GetLevel())
    {
    case 1:
        Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::SmogeRed>>()->Emit(1, ball->GetPosition(), -ball->GetVelocity()/10, {0, 0}, PI / 2);
        break;
    case 2:
        Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::SmogeYellow>>()->Emit(1, ball->GetPosition(), -ball->GetVelocity()/10, { 0, 0 }, PI / 2);
        break;
    case 3:
        Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::SmogeGreen>>()->Emit(1, ball->GetPosition(), -ball->GetVelocity() / 10, { 0, 0 }, PI / 2);
        break;
    case 4:
        Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::SmogeBlue>>()->Emit(1, ball->GetPosition(), -ball->GetVelocity() / 10, { 0, 0 }, PI / 2);
        break;
    case 5:
        Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::SmogeGrey>>()->Emit(1, ball->GetPosition(), -ball->GetVelocity() / 10, { 0, 0 }, PI / 2);
        break;
    default:
        break;
    }
    
}

void Ball::State_Dashing::Update(GameObject* object, double dt)
{
    Ball* ball = static_cast<Ball*>(object);
    ball->GetGOComponent<Stamina>()->UpdateStamina(-(Ball::stamina_consumption1+Ball::stamina_consumption_level_diff*(ball->GetGOComponent<Level>()->GetLevel()-1)) * dt);
}

void Ball::State_Dashing::CheckExit(GameObject* object)
{
    Ball* ball = static_cast<Ball*>(object);
    if (ball->GetGOComponent<Level>()->GetLevel() <= 0) {
        ball->change_state(&ball->state_dead);
    }else if (!Engine::GetInput().KeyDown(CS230::Input::Keys::Space)||  ball->GetGOComponent<Stamina>()->GetStamina() <= 0.0) {
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
    ball->PlayLevelAnimation();
}

void Ball::State_Falling::Update(GameObject* object, double dt)
{
    Ball* ball = static_cast<Ball*>(object);
    ball->UpdateVelocity({ 0,-Engine::GetGameStateManager().GetGSComponent<Gravity>()->GetValue() * dt });
}

void Ball::State_Falling::CheckExit(GameObject* object)
{
    Ball* ball = static_cast<Ball*>(object);

    if (ball->GetGOComponent<Level>()->GetLevel() <= 0|| ball->GetPosition().y < Ball::dead_height) {
        ball->change_state(&ball->state_dead);
    }else if (ball->standing_on != nullptr) {
        ball->change_state(&ball->state_rolling);
    }
}

void Ball::State_Dead::Enter(GameObject* object)
{
    Ball* ball = static_cast<Ball*>(object);
    ball->SetVelocity({ 0.0,0.0 });
    ball->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Dead));
    ball->game_over_sound->Play();
}

void Ball::State_Dead::Update(GameObject* object, double dt)
{

}

void Ball::State_Dead::CheckExit(GameObject* object)
{
    Ball* ball = static_cast<Ball*>(object);
    if (ball->GetGOComponent<CS230::Sprite>()->AnimationEnded()) {
        Engine::GetGameStateManager().ReloadState();
    }
}

void Ball::PlayLevelAnimation() {
    int level = GetGOComponent<Level>()->GetLevel();
    if (current_state == &state_rolling) {
        switch (level)
        {
        case 1:
            GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Rolling1));
            break;
        case 2:
            GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Rolling2));
            break;
        case 3:
            GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Rolling3));
            break;
        case 4:
            GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Rolling4));
            break;
        case 5:
            GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Rolling5));
            break;
        default:
            break;
        }
    }
    else if (current_state == &state_dashing) {
        switch (level)
        {
        case 1:
            GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Dashing1));
            break;
        case 2:
            GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Dashing2));
            break;
        case 3:
            GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Dashing3));
            break;
        case 4:
            GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Dashing4));
            break;
        case 5:
            GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Dashing5));
            break;
        default:
            break;
        }
    }
    else if (current_state == &state_falling) {
        switch (level)
        {
        case 1:
            GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Falling1));
            break;
        case 2:
            GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Falling2));
            break;
        case 3:
            GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Falling3));
            break;
        case 4:
            GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Falling4));
            break;
        case 5:
            GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Falling5));
            break;
        default:
            break;
        }
    }
    else if (current_state == &state_dead) {
        GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Dead));
    }
}
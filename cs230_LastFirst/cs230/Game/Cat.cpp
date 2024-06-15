/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Cat.cpp
Project:    CS230 Engine
Author:     Donghyeon Jo
Created:    March 31, 2024
*/

#include "..\Engine\Camera.h"
#include "Gravity.h"
#include "..\Engine\GameObject.h"
#include "Cat.h"
#include "Mode1.h"
#include "..\Engine\Sprite.h"
#include "..\Engine\Input.h"
#include "..\Engine\Vec2.h"
#include "..\Engine\Matrix.h"
#include "..\Engine\Engine.h"
#include "..\Engine\Collision.h"
#include "States.h"
#include "Score.h"
#include "Portal.h"
#include "..\Engine\Particle.h"
#include "Particles.h"

Cat::Cat(Math::vec2 start_position) :
    GameObject(start_position), standing_on(nullptr)
{
    AddGOComponent(new CS230::Sprite("Assets/Cat.spt", this));
    current_state = &state_idle;
    current_state->Enter(this);
    hurt_timer = new CS230::Timer(0.0);
    AddGOComponent(hurt_timer);
}

void Cat::Update(double dt) {
    GameObject::Update(dt);
    CS230::Camera* camera = Engine::GetGameStateManager().GetGSComponent<CS230::Camera>();
    CS230::RectCollision* collider = GetGOComponent<CS230::RectCollision>();
    // Boundary Check
    if (GetPosition().x - collider->WorldBoundary().Size().x / 2 < camera->GetPosition().x) {
        UpdatePosition({ camera->GetPosition().x + collider->WorldBoundary().Size().x / 2 - GetPosition().x, 0 });
        SetVelocity({ 0, GetVelocity().y });
    }
    if (GetPosition().x + collider->WorldBoundary().Size().x / 2 > camera->GetPosition().x + Engine::GetWindow().GetSize().x) {
        UpdatePosition({ camera->GetPosition().x + Engine::GetWindow().GetSize().x - collider->WorldBoundary().Size().x / 2 - GetPosition().x, 0 });
        SetVelocity({ 0, GetVelocity().y });
    }
}

void Cat::Draw(Math::TransformationMatrix camera_matrix)
{
    if (hurt_timer->Remaining() == 0.0 || hurt_timer->TickTock() == true) {
        CS230::GameObject::Draw(camera_matrix);
    }
}

bool Cat::CanCollideWith(GameObjectType other_object_type)
{
    if (other_object_type == GameObjectType::Particle) {
        return false;
    }
    return true;
}

void Cat::ResolveCollision(GameObject* other_object)
{
    Math::rect cat_rect = GetGOComponent<CS230::RectCollision>()->WorldBoundary();
    Math::rect other_rect = other_object->GetGOComponent<CS230::RectCollision>()->WorldBoundary();
    switch (other_object->Type())
    {
    case GameObjectType::Floor: [[fallthrough]];
    case GameObjectType::Platform: [[fallthrough]];
    case GameObjectType::Crates:
        if (current_state == &state_falling && GetPosition().x > other_rect.Left() && GetPosition().x < other_rect.Right()) {
            if (cat_rect.Top() > other_rect.Top()) {
                SetPosition({ GetPosition().x, other_rect.Top() });
                standing_on = other_object;
                current_state->CheckExit(this);
                return;
            }
        }
        if (current_state == &state_jumping && GetPosition().x > other_rect.Left() && GetPosition().x < other_rect.Right()) {
            if (cat_rect.Bottom() < other_rect.Bottom()) {
                SetPosition({ GetPosition().x, other_rect.Bottom() - cat_rect.Size().y});
                SetVelocity(Math::vec2(GetVelocity().x, 0));
                current_state->CheckExit(this);
                return;
            }
        }
        if (cat_rect.Left() < other_rect.Left()) {
            UpdatePosition(Math::vec2{ (other_rect.Left() - cat_rect.Right()), 0.0 });
            SetVelocity({ 0, GetVelocity().y });
        }
        else {
            UpdatePosition(Math::vec2{ (other_rect.Right() - cat_rect.Left()), 0.0 });
            SetVelocity({ 0, GetVelocity().y });
        }
        break;
    case GameObjectType::Robot:
        if (current_state == &state_falling && cat_rect.Top() > other_rect.Top() && hurt_timer->Remaining() == 0) {
            Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::Smoke>>()->Emit(2, GetPosition(), { 0, 0 }, { 0, 100 }, PI / 2);
            SetPosition({ GetPosition().x, other_rect.Top() });
            SetVelocity({ GetVelocity().x, pop_velocity });
            other_object->ResolveCollision(this);
            Engine::GetGameStateManager().GetGSComponent<Score>()->Add(1);
        }
        else {
            if (cat_rect.Left() < other_rect.Left()) {
                SetVelocity({ -hurt_acceleration, hurt_velocity });
            }
            else {
                SetVelocity({ hurt_acceleration, hurt_velocity });
            }
            change_state(&state_falling);
            hurt_timer->Set(hurt_time);
        }
        standing_on = nullptr;
        break;
    case GameObjectType::Asteroid:
        if (current_state == &state_falling && cat_rect.Top() > other_rect.Top() && hurt_timer->Remaining() == 0) {
            SetPosition({ GetPosition().x, other_rect.Top() });
            SetVelocity({ GetVelocity().x, bounce_velocity });
        }
        else {
            if (cat_rect.Left() < other_rect.Left()) {
                SetVelocity({ -hurt_acceleration, hurt_velocity });
            }
            else {
                SetVelocity({ hurt_acceleration, hurt_velocity });
            }
            change_state(&state_falling);
            hurt_timer->Set(hurt_time);
        }
        standing_on = nullptr;
        break;
    case GameObjectType::Portal:
        static_cast<Portal*>(other_object)->GoToState();
        break;
    default:
        break;
    }
}

void Cat::update_x_velocity(double dt) {
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Right)) {
        UpdateVelocity({ x_acceleration * dt,0 });
        if (GetVelocity().x > max_velocity) {
            SetVelocity({max_velocity,GetVelocity().y});
        }
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left)) {
        UpdateVelocity({ -x_acceleration * dt,0 });
        if (GetVelocity().x < -max_velocity) {
            SetVelocity({ -max_velocity,GetVelocity().y });
        }
    }
    else {
        if (GetVelocity().x > x_drag * dt) {
            UpdateVelocity({-x_drag*dt,0});
        }
        else if (GetVelocity().x < -x_drag * dt) {
            UpdateVelocity({ x_drag * dt,0 });
        }
        else {
            SetVelocity({ 0,GetVelocity().y });
        }
    }
}


void Cat::State_Jumping::Enter(GameObject* object) {
    Cat* cat = static_cast<Cat*>(object);
    cat->SetVelocity({ cat->GetVelocity().x,Cat::jump_velocity });
    cat->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Jumping));
    cat->standing_on = nullptr;
}
void Cat::State_Jumping::Update(GameObject* object, double dt) {
    Cat* cat = static_cast<Cat*>(object);
    cat->UpdateVelocity({ 0,-Engine::GetGameStateManager().GetGSComponent<Gravity>()->GetValue() * dt });
    cat->update_x_velocity(dt);
}
void Cat::State_Jumping::CheckExit(GameObject* object) {
    Cat* cat = static_cast<Cat*>(object);
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Up) == false || cat->GetVelocity().y <= 0) {
        cat->SetVelocity({ cat->GetVelocity().x,0 });
        cat->change_state(&cat->state_falling);
    }
}

void Cat::State_Idle::Enter(GameObject* object) {
    Cat* cat = static_cast<Cat*>(object);
    cat->SetVelocity({ 0,0 });
    cat->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
}
void Cat::State_Idle::Update(GameObject*, double) {

}
void Cat::State_Idle::CheckExit(GameObject* object) {
    Cat* cat = static_cast<Cat*>(object);
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left) ||
        Engine::GetInput().KeyDown(CS230::Input::Keys::Right)) {
        cat->SetVelocity({ 0,0 });
        cat->change_state(&cat->state_running);
    }
    else if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Up)) {
        Cat* cat = static_cast<Cat*>(object);
        cat->SetVelocity({ 0,0 });
        cat->change_state(&cat->state_jumping);
    }
}

void Cat::State_Falling::Enter(GameObject* object) {
    Cat* cat = static_cast<Cat*>(object);
    cat->SetVelocity({ cat->GetVelocity().x, cat->GetVelocity().y });
    cat->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Falling));
}
void Cat::State_Falling::Update(GameObject* object, double dt) {
    Cat* cat = static_cast<Cat*>(object);
    cat->UpdateVelocity({ 0,-Engine::GetGameStateManager().GetGSComponent<Gravity>()->GetValue() * dt });
    cat->update_x_velocity(dt);
}
void Cat::State_Falling::CheckExit(GameObject* object) {
    Cat* cat = static_cast<Cat*>(object);
    if (cat->standing_on != nullptr) {
        if (cat->GetVelocity().y * cat->GetVelocity().y >=  2.0 * LargeFallHeight * Engine::GetGameStateManager().GetGSComponent<Gravity>()->GetValue() ) {
            Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::Smoke>>()->Emit(2, cat->GetPosition(), { 0, 0 }, { 0, 100 }, PI / 2);
        }
        if (cat->GetVelocity().x > 0) {
            if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left)) {
                cat->change_state(&cat->state_skidding);
            }
            else {
                cat->change_state(&cat->state_running);
            }
        }
        else if (cat->GetVelocity().x < 0) {
            if (Engine::GetInput().KeyDown(CS230::Input::Keys::Right)) {
                cat->change_state(&cat->state_skidding);
            }
            else {
                cat->change_state(&cat->state_running);
            }
        }
        else {
            cat->change_state(&cat->state_idle);
        }

        cat->SetVelocity({ cat->GetVelocity().x, 0 });
    }

    if (cat->GetPosition().y < -500) {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Menu));
    }
}


void Cat::State_Running::Enter(GameObject* object) {
    Cat* cat = static_cast<Cat*>(object);
    cat->SetVelocity({ cat->GetVelocity().x,0 });
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left)) {
        cat->SetScale({ -1,1 });
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Right)) {
        cat->SetScale({ 1,1 });
    }
    cat->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Running));
}
void Cat::State_Running::Update(GameObject* object, double dt) {
    Cat* cat = static_cast<Cat*>(object);
    cat->update_x_velocity(dt);
}
void Cat::State_Running::CheckExit(GameObject* object) {
    Cat* cat = static_cast<Cat*>(object);
    if (cat->GetVelocity().x == 0) {
        cat->SetVelocity({ 0,0 });
        cat->change_state(&cat->state_idle);
    }
    else if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Up)) {
        cat->SetVelocity({ cat->GetVelocity().x,0 });
        cat->change_state(&cat->state_jumping);
    }
    else if ((Engine::GetInput().KeyDown(CS230::Input::Keys::Left) && cat->GetVelocity().x > 0) ||
        (Engine::GetInput().KeyDown(CS230::Input::Keys::Right) && cat->GetVelocity().x < 0)) {
        cat->SetVelocity({ cat->GetVelocity().x,0 });
        cat->change_state(&cat->state_skidding);
    }
    if (cat->standing_on != nullptr && cat->standing_on->IsCollidingWith(cat->GetPosition()) == false) {
        cat->standing_on = nullptr;
        cat->change_state(&cat->state_falling);
    }
}

void Cat::State_Skidding::Enter(GameObject* object) {
    Cat* cat = static_cast<Cat*>(object);
    cat->SetVelocity({ cat->GetVelocity().x,0 });
    cat->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Skidding));
    Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::Smoke>>()->Emit(2, cat->GetPosition(), { 0, 0 }, { 2 * cat->GetVelocity().x, 0 }, PI / 6);
}
void Cat::State_Skidding::Update(GameObject* object, double dt) {
    Cat* cat = static_cast<Cat*>(object);
    if (cat->GetVelocity().x > 0) {
        cat->UpdateVelocity({ -(x_drag + x_acceleration) * dt, 0 });
    }
    else if (cat->GetVelocity().x < 0) {
        cat->UpdateVelocity({ (x_drag + x_acceleration) * dt, 0 });
    }
}
void Cat::State_Skidding::CheckExit(GameObject* object) {
    Cat* cat = static_cast<Cat*>(object);
    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Up)) {
        cat->SetVelocity({ cat->GetVelocity().x,0 });
        cat->change_state(&cat->state_jumping);
    }
    else if ((cat->GetScale().x == 1 && cat->GetVelocity().x < 0) ||
        (cat->GetScale().x == -1 && cat->GetVelocity().x > 0) ||
        !((Engine::GetInput().KeyDown(CS230::Input::Keys::Left)) ||
            (Engine::GetInput().KeyDown(CS230::Input::Keys::Right))) ||
        cat->GetVelocity().x == 0) {
        cat->SetVelocity({ cat->GetVelocity().x,0 });
        cat->change_state(&cat->state_running);
    }
}
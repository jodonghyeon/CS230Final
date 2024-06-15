/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Meteor.cpp
Project:    CS230 Engine
Author:     Donghyeon Jo
Created:    May 1, 2024
*/

#include "Mode2.h"
#include "Meteor.h"
#include "..\Engine\Collision.h"
#include "..\Engine\Engine.h"
#include "..\Engine\GameObjectManager.h"
#include "ScreenWrap.h"
#include "..\Engine\Particle.h"
#include "Particles.h"
#include "Score.h"

Meteor::Meteor() : Meteor(nullptr) {}

Meteor::Meteor(Math::ivec2 window_size) :
    GameObject({ window_size.x * rand() / (RAND_MAX + 1.0),window_size.y * rand() / (RAND_MAX + 1.0) }, 2 * PI * rand() / (RAND_MAX + 1.0), { 1,1 })
{
    AddGOComponent(new CS230::Sprite("Assets/Meteor.spt", this));
    SetVelocity({ -default_velocity + (2 * default_velocity * rand() / (RAND_MAX + 1.0)),-default_velocity + (2 * default_velocity * rand() / (RAND_MAX + 1.0)) });
    GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::None));
    size = default_size;
    health = default_healths[size];
    AddGOComponent(new ScreenWrap(*this));
}

Meteor::Meteor(Meteor* parent) : CS230::GameObject({ 0, 0 }) {
    AddGOComponent(new CS230::Sprite("Assets/Meteor.spt", this));
    if (parent == nullptr) {
        int generating_side = rand()%2;
        switch (generating_side)
        {
        case 0:
            SetPosition({
            ((double)rand() / RAND_MAX) * Engine::GetWindow().GetSize().x,
            -(double)GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2
                });
            break;
        case 1:
            SetPosition({
            -(double)GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2,
            ((double)rand() / RAND_MAX) * Engine::GetWindow().GetSize().y
                });
            break;
        default:
            break;
        }
        SetVelocity(Math::vec2{
            ((double)rand() / RAND_MAX) * default_velocity * 2 - default_velocity,
            ((double)rand() / RAND_MAX) * default_velocity * 2 - default_velocity
            });
        /*SetPosition({
            ((double)rand() / RAND_MAX) * Engine::GetWindow().GetSize().x,
            ((double)rand() / RAND_MAX) * Engine::GetWindow().GetSize().y
            });*/
        SetRotation(((double)rand() / RAND_MAX) * 2 * PI);

        size = default_size;
    }
    else {
        SetVelocity(parent->GetVelocity());
        SetPosition(parent->GetPosition());
        SetRotation(parent->GetRotation());

        size = parent->size - 1;
    }
    health = default_healths[size];
    SetScale(Math::vec2{ default_scales[size], default_scales[size] });
    AddGOComponent(new ScreenWrap(*this));
}

void Meteor::Update(double dt)
{
    GameObject::Update(dt);
    if (GetGOComponent<CS230::Sprite>()->CurrentAnimation() == static_cast<int>(Animations::Fade) && GetGOComponent<CS230::Sprite>()->AnimationEnded()) {
        Destroy();
    }
}

void Meteor::ResolveCollision(GameObject* other_object) {
    UpdateVelocity(0.01 * other_object->GetVelocity());
    Math::vec2 normalized_direction = ((Math::vec2)other_object->GetPosition() - (Math::vec2)GetPosition()).Normalize();
    Math::vec2 hit_position = (Math::vec2)GetPosition()+GetGOComponent<CS230::CircleCollision>()->GetRadius() * normalized_direction;
    Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::Hit>>()->Emit(1, hit_position, GetVelocity(), {0, 0}, 0);
    Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::MeteorBit>>()->Emit(5, hit_position, GetVelocity(), default_velocity * normalized_direction, PI / 3);
    health -= 1;
    if (health < 0) {
        Engine::GetGameStateManager().GetGSComponent<Score>()->Add(10);
        RemoveGOComponent<CS230::Collision>();
        GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Fade));
        if (size > 0) {
            Meteor* meteor_1 = new Meteor(this);
            meteor_1->SetVelocity(Math::RotationMatrix(PI / 6) * GetVelocity());

            Meteor* meteor_2 = new Meteor(this);
            meteor_2->SetVelocity(Math::RotationMatrix(-PI / 6) * GetVelocity());

            Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(meteor_1);
            Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(meteor_2);
        }
    }
}

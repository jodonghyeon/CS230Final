/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Asteroid.cpp
Project:    CS230 Engine
Author:     Donghyeon Jo
Created:    March 31, 2024
*/

#include "Mode1.h"
#include "Asteroid.h"
#include "..\Engine\GameObject.h"
#include "..\Engine\Sprite.h"
#include "..\Engine\Vec2.h"
#include "..\Engine\Rect.h"
#include "..\Engine\Matrix.h"
#include "..\Engine\Engine.h"
#include "..\Engine\Collision.h"

Asteroid::Asteroid(Math::vec2 start_position) :
    GameObject(start_position)
{
    AddGOComponent(new CS230::Sprite("Assets/Asteroid.spt", this));
    current_state = &state_land;
    current_state->Enter(this);
}

bool Asteroid::CanCollideWith(GameObjectType other_object_type)
{
    if (other_object_type == GameObjectType::Floor) {
        return true;
    }
    return false;
}

void Asteroid::ResolveCollision(GameObject* other_object)
{
    Math::rect other_rect = other_object->GetGOComponent<CS230::RectCollision>()->WorldBoundary();

    if (other_object->Type() == GameObjectType::Floor &&GetVelocity().y<0) {
        SetPosition({ GetPosition().x,other_rect.Top() });
        SetVelocity({ 0,0 });
        change_state(&state_land);
    }
}

void Asteroid::State_Bounce::Enter(GameObject* object) {
    Asteroid* asteroid = static_cast<Asteroid*>(object);
    asteroid->SetVelocity({ 0,bounce_velocity });
    asteroid->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Bounce));
}
void Asteroid::State_Bounce::Update(GameObject* object, double dt) {
    Asteroid* asteroid = static_cast<Asteroid*>(object);
    asteroid->UpdateVelocity({ 0,-Mode1::gravity * dt });
}
void Asteroid::State_Bounce::CheckExit(GameObject*) {
    
}

void Asteroid::State_Land::Enter(GameObject* object){
    Asteroid* asteroid = static_cast<Asteroid*>(object);
    asteroid->SetVelocity({ 0,0 });
    asteroid->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Land));
}
void Asteroid::State_Land::Update(GameObject*, double){ 
}
void Asteroid::State_Land::CheckExit(GameObject* object){
    Asteroid* asteroid = static_cast<Asteroid*>(object);
    if (asteroid->GetGOComponent<CS230::Sprite>()->AnimationEnded()) {
        asteroid->SetVelocity({ 0,bounce_velocity });
        asteroid->change_state(&asteroid->state_bounce);
    }
}
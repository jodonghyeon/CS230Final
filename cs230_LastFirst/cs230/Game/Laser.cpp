/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Laser.h
Project:    CS230 Engine
Author:     Donghyeon Jo
Created:    June 2, 2024
*/

#include "Laser.h"
#include "..\Engine\Engine.h"

Laser::Laser(Math::vec2 pos, double rot, Math::vec2 scale, Math::vec2 vel) :GameObject(pos, rot, scale)
{
    SetVelocity(vel);
    AddGOComponent(new CS230::Sprite("Assets/Laser.spt", this));
}

void Laser::Update(double dt)
{
    GameObject::Update(dt);
    Math::ivec2 frame_size = GetGOComponent<CS230::Sprite>()->GetFrameSize();
    Math::vec2 position = GetPosition();
    if (position.y > Engine::GetWindow().GetSize().y + frame_size.y / 2.0) {
        Destroy();
    }
    else if (position.y < 0 - frame_size.y / 2.0) {
        Destroy();
    }
    if (position.x > Engine::GetWindow().GetSize().x + frame_size.x / 2.0) {
        Destroy();
    }
    else if (position.x < 0 - frame_size.x / 2.0) {
        Destroy();
    }
}

bool Laser::CanCollideWith(GameObjectType other_object_type)
{
    if (other_object_type == GameObjectType::Meteor) {
        return true;
    }
    return false;
}

void Laser::ResolveCollision(GameObject* other_object)
{
    if (other_object->Type() == GameObjectType::Meteor) {
        Destroy();
        other_object->ResolveCollision(this);
    }
}

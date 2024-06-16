/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Camera.cpp
Project:    CS230 Engine
Author:     Donghyeon Jo
Created:    April 6, 2024
*/

#include "Camera.h"
#include "Collision.h"
#include "Rect.h"
#include "Engine.h"

CS230::Camera::Camera(Math::rect player_zone) :
    position({ 0,0 })
{
    Camera::player_zone = player_zone;
}

void CS230::Camera::SetPosition(Math::vec2 new_position)
{
    position = new_position;
}

const Math::vec2& CS230::Camera::GetPosition() const
{
    return position;
}

void CS230::Camera::SetLimit(Math::irect new_limit)
{
    limit = new_limit;
}

const Math::irect& CS230::Camera::GetLimit() const
{
    return limit;
}


void CS230::Camera::Update(const Math::vec2& player_position) {
    if (player_position.x > player_zone.Right() + position.x) {
        position.x = player_position.x - player_zone.Right();
    }
    if (player_position.x < player_zone.Left() + position.x) {
        position.x = player_position.x - player_zone.Left();
    }

    if (player_position.y > player_zone.Top() + position.y) {
        position.y = player_position.y - player_zone.Top();
    }
    if (player_position.y < player_zone.Bottom() + position.y) {
        position.y = player_position.y - player_zone.Bottom();
    }

    if (position.x < limit.Left()) {
        position.x = limit.Left();
    }
    if (position.x > limit.Right()) {
        position.x = limit.Right();
    }
    if (position.y < limit.Bottom()) {
        position.y = limit.Bottom();
    }
    if (position.y > limit.Top()) {
        position.y = limit.Top();
    }
}

Math::TransformationMatrix CS230::Camera::GetMatrix() {
    return Math::TranslationMatrix(-position);
}

CS230::DampingCamera::DampingCamera(Math::irect limit, double dampingFactor)
    :limit(limit), position({ 0,0 }), dampingFactor(dampingFactor)
{
}

void CS230::DampingCamera::SetPosition(Math::vec2 new_position)
{
    position = new_position;
}

const Math::vec2& CS230::DampingCamera::GetPosition() const
{
    return position;
}

void CS230::DampingCamera::SetLimit(Math::irect new_limit)
{
    limit = new_limit;
}

const Math::irect& CS230::DampingCamera::GetLimit() const
{
    return limit;
}

void CS230::DampingCamera::SetDampingFactor(double new_dampingFactor)
{
    dampingFactor = new_dampingFactor;
}

void CS230::DampingCamera::Update(CS230::GameObject* player, double dt)
{
    Math::rect player_collison_box = player->GetGOComponent<CS230::RectCollision>()->WorldBoundary();
    Math::vec2 distance = { player_collison_box.Left() - position.x, player_collison_box.Bottom() - position.y};

    position.x += distance.x * dampingFactor * dt;
    position.y += distance.y * dampingFactor * dt;

    if (player_collison_box.Left() < position.x) {
        position.x = player_collison_box.Left();
    }
    if (player_collison_box.Right() > position.x + Engine::GetWindow().GetSize().x) {
        position.x = player_collison_box.Right() - Engine::GetWindow().GetSize().x;
    }

    if (position.x < limit.Left()) {
        position.x = limit.Left();
    }
    if (position.x > limit.Right()) {
        position.x = limit.Right();
    }
    if (position.y < limit.Bottom()) {
        position.y = limit.Bottom();
    }
    if (position.y > limit.Top()) {
        position.y = limit.Top();
    }
}

Math::TransformationMatrix CS230::DampingCamera::GetMatrix()
{
    return Math::TranslationMatrix(-position);
}

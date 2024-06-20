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

CS230::DampingCamera::DampingCamera(Math::irect limit, Math::rect target_limit, Math::vec2 target_offset, double dampingFactor, Math::vec2 start_position)
    : limit(limit), target_limit(target_limit),target_offset(target_offset),dampingFactor(dampingFactor),position(start_position)
{ }

void CS230::DampingCamera::Update(CS230::GameObject* player, double dt)
{
    Math::rect player_collison_box = player->GetGOComponent<CS230::RectCollision>()->WorldBoundary();
    Math::vec2 distance = { player_collison_box.Left() - position.x - target_offset.x, player_collison_box.Bottom() - position.y - target_offset.y };

    position.x += distance.x * dampingFactor * dt;
    position.y += distance.y * dampingFactor * dt;

    if (player_collison_box.Left() < position.x + target_limit.Left() * Engine::GetWindow().GetSize().x ) {
        position.x = player_collison_box.Left() - target_limit.Left() * Engine::GetWindow().GetSize().x;
    }
    if (player_collison_box.Right() > position.x + target_limit.Right() * Engine::GetWindow().GetSize().x) {
        position.x = player_collison_box.Right() - target_limit.Right() * Engine::GetWindow().GetSize().x;
    }
    if (player_collison_box.Bottom() < position.y + target_limit.Bottom() * Engine::GetWindow().GetSize().y) {
        position.y = player_collison_box.Bottom() - target_limit.Bottom() * Engine::GetWindow().GetSize().y;
    }
    if (player_collison_box.Top() > position.y + target_limit.Top() * Engine::GetWindow().GetSize().y) {
        position.y = player_collison_box.Top() - target_limit.Top() * Engine::GetWindow().GetSize().y;
    }

    if (position.x < limit.Left()) {
        position.x = limit.Left();
    }
    if (position.x > limit.Right()-Engine::GetWindow().GetSize().x) {
        position.x = limit.Right() - Engine::GetWindow().GetSize().x;
    }
    if (position.y < limit.Bottom()) {
        position.y = limit.Bottom();
    }
    if (position.y > limit.Top() - Engine::GetWindow().GetSize().y) {
        position.y = limit.Top() - Engine::GetWindow().GetSize().y;
    }
}

Math::TransformationMatrix CS230::DampingCamera::GetMatrix()
{
    return Math::TranslationMatrix(-position);
}

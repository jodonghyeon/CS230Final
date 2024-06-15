/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Ship.cpp
Project:    CS230 Engine
Author:     Donghyeon Jo
Created:    March 31, 2024
*/

#include "..\Engine\Sprite.h"
#include "ScreenWrap.h"
#include "..\Engine\Input.h"
#include "..\Engine\Vec2.h"
#include "..\Engine\Matrix.h"
#include "..\Engine\Engine.h"
#include "..\Engine\Collision.h"
#include "..\Engine\ShowCollision.h"
#include "..\Engine\GameObjectManager.h"
#include "Mode2.h"
#include "Ship.h"
#include "Laser.h"

Ship::Ship(Math::vec2 position, double rotation, Math::vec2 scale) :
    GameObject(position, rotation, scale),
    flame_left("Assets/Flame.spt", this),
    flame_right("Assets/Flame.spt", this)
{
    AddGOComponent(new CS230::Sprite("Assets/Ship.spt", this));
    AddGOComponent(new ScreenWrap(*this));
    flame_left.Load("Assets/Flame.spt");
    flame_right.Load("Assets/Flame.spt");
    flame_left.PlayAnimation(static_cast<int>(Flame_Animations::Off));
    flame_right.PlayAnimation(static_cast<int>(Flame_Animations::Off));
    SetVelocity({ 0,0 });
    ignition = false;
    exploded = false;
}

void Ship::Update(double dt) {
    flame_left.Update(dt);
    flame_right.Update(dt);
    if (!exploded) {
        if (Engine::GetInput().KeyDown(CS230::Input::Keys::W)) {
            UpdateVelocity(Math::RotationMatrix(GetRotation()) * Math::vec2{ 0, speed * dt });
            if (!ignition) {
                flame_left.PlayAnimation(static_cast<int>(Flame_Animations::On));
                flame_right.PlayAnimation(static_cast<int>(Flame_Animations::On));
                ignition = true;
            }
        }
        else {
            flame_left.PlayAnimation(static_cast<int>(Flame_Animations::Off));
            flame_right.PlayAnimation(static_cast<int>(Flame_Animations::Off));
            ignition = false;
        }
        if (Engine::GetInput().KeyDown(CS230::Input::Keys::A)) {
            UpdateRotation(rotation_speed * dt);
        }
        if (Engine::GetInput().KeyDown(CS230::Input::Keys::D)) {
            UpdateRotation(-rotation_speed * dt);
        }
        if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Enter)) {
            Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(
                new Laser(
                    GetMatrix() * Math::vec2(GetGOComponent<CS230::Sprite>()->GetHotSpot(3)),
                    GetRotation(),
                    GetScale(),
                    Math::RotationMatrix(GetRotation()) * Math::vec2{ 0, Laser::DefaultVelocity }));
            Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(
                new Laser(
                    GetMatrix() * Math::vec2(GetGOComponent<CS230::Sprite>()->GetHotSpot(4)),
                    GetRotation(),
                    GetScale(),
                    Math::RotationMatrix(GetRotation()) * Math::vec2{ 0, Laser::DefaultVelocity }));
        }
    }
    UpdateVelocity(-GetVelocity() * drag * dt);

    UpdatePosition(dt* GetVelocity());

    UpdateGOComponents(dt);
}


void Ship::Draw(Math::TransformationMatrix camera_matrix) {
    if (!exploded) {
        flame_left.Draw(GetMatrix() * Math::TranslationMatrix(GetGOComponent<CS230::Sprite>()->GetHotSpot(1)) * camera_matrix);
        flame_right.Draw(GetMatrix() * Math::TranslationMatrix(GetGOComponent<CS230::Sprite>()->GetHotSpot(2)) * camera_matrix);
    }
    GetGOComponent<CS230::Sprite>()->Draw(GetMatrix() * camera_matrix);

    CS230::Collision* collision = GetGOComponent<CS230::Collision>();
    if (collision != nullptr && Engine::GetGameStateManager().GetGSComponent<CS230::ShowCollision>() != nullptr
        && Engine::GetGameStateManager().GetGSComponent<CS230::ShowCollision>()->Enabled()) {
        collision->Draw(camera_matrix);
    }
}

bool Ship::CanCollideWith(GameObjectType)
{
    return true;
}

void Ship::ResolveCollision(GameObject*)
{
    GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Explosion));
    RemoveGOComponent<CS230::Collision>();
    exploded = true;
}

bool Ship::Exploded()
{
    return exploded;
}


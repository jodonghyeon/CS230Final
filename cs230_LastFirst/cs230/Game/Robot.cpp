/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Robot.cpp
Project:    CS230 Engine
Author:     Donghyeon Jo
Created:    May 1, 2024
*/

#include "Mode1.h"
#include "Robot.h"
#include "..\Engine\GameObject.h"
#include "..\Engine\Collision.h"

Robot::Robot(Math::vec2 position, Cat* cat, double left_boundary, double right_boundary) : CS230::GameObject(position), cat_ptr(cat), left_boundary(left_boundary), right_boundary(right_boundary) 
{
    AddGOComponent(new CS230::Sprite("Assets/Robot.spt", this));
    GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::None));
    current_state = &state_walking;
    current_state->Enter(this);
    SetVelocity({ walking_speed,0 });
}

void Robot::ResolveCollision(GameObject* other_object)
{
    if (other_object->Type() == GameObjectType::Cat) {
        change_state(&state_dead);
        RemoveGOComponent<CS230::Collision>();
    }
}

void Robot::State_Dead::Enter(GameObject* object)
{
    Robot* robot = static_cast<Robot*>(object);
    robot->SetVelocity({ 0,0 });
    robot->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Dead));
}
void Robot::State_Dead::Update(GameObject*, double)
{
}
void Robot::State_Dead::CheckExit(GameObject*)
{
}

void Robot::State_Walking::Enter(GameObject* object)
{
    Robot* robot = static_cast<Robot*>(object);
    if (robot->GetVelocity().x >= 0) {
        robot->SetVelocity({ walking_speed,0 });
    }
    else {
        robot->SetVelocity({ -walking_speed,0 });
    }
    robot->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Walking));
}
void Robot::State_Walking::Update(GameObject* object, double)
{
    Robot* robot = static_cast<Robot*>(object);
    if (robot->GetPosition().x >= robot->right_boundary) {
        robot->SetScale({ -1,1 });
        robot->SetVelocity({ -walking_speed,0 });
    }else if (robot->GetPosition().x <= robot->left_boundary) {
        robot->SetScale({ 1,1 });
        robot->SetVelocity({ walking_speed,0 });
    }
}
void Robot::State_Walking::CheckExit(GameObject* object)
{
    Robot* robot = static_cast<Robot*>(object);
    Math::vec2 cat_pos = robot->cat_ptr->GetPosition();
    if (cat_pos.x > robot->left_boundary && cat_pos.x < robot->right_boundary
        && ((cat_pos.x - robot->GetPosition().x >= 0 && robot->GetVelocity().x > 0) || (cat_pos.x - robot->GetPosition().x <= 0 && robot->GetVelocity().x < 0)))
    {
        robot->change_state(&robot->state_angry);
    }
}

void Robot::State_Angry::Enter(GameObject* object)
{
    Robot* robot = static_cast<Robot*>(object);
    if (robot->GetVelocity().x >= 0) {
        robot->SetVelocity({ angry_speed,0 });
    }
    else {
        robot->SetVelocity({ -angry_speed,0 });
    }
    robot->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Angry));
}
void Robot::State_Angry::Update(GameObject* object, double)
{
    Robot* robot = static_cast<Robot*>(object);
    if (robot->GetPosition().x >= robot->right_boundary) {
        robot->SetScale({ -1,1 });
        robot->SetVelocity({ -angry_speed,0 });
    }
    else if (robot->GetPosition().x <= robot->left_boundary) {
        robot->SetScale({ 1,1 });
        robot->SetVelocity({ angry_speed,0 });
    }
}
void Robot::State_Angry::CheckExit(GameObject*)
{
}

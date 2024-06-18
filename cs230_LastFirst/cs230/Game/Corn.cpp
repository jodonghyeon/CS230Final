/*
File Name:  Corn.cpp
Project:    CS230 Final
Author:     Donghyeon Jo
Created:    June 18, 2024
*/

#include "Corn.h"
#include "..\Engine\Collision.h"
#include "Level.h"

Corn::Corn(Math::vec2 position, Ball* ball)
	: CS230::GameObject(position), origin(position), ball_ptr(ball), is_dead(false), disappearance(false), dead_time(0.0)
{
	AddGOComponent(new CS230::Sprite("Assets/Corn.spt", this));
	AddGOComponent(new Level(*this, 1, level_default));
	current_state = &state_alive;
	current_state->Enter(this);
}

void Corn::ResolveCollision(GameObject* other_object)
{
	if (other_object->Type() == GameObjectType::Ball) {
		change_state(&state_dead);
	}
}

void Corn::Draw(Math::TransformationMatrix camera_matrix)
{
	if (!disappearance) {
		CS230::GameObject::Draw(camera_matrix);
	}
}

void Corn::State_Alive::Enter(GameObject* object)
{
	Corn* corn = static_cast<Corn*>(object);
	corn->is_dead = false;
	corn->disappearance = false;
	corn->SetVelocity({ 0,0 });
	corn->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::None));
}

void Corn::State_Alive::Update(GameObject* object, double dt)
{

}

void Corn::State_Alive::CheckExit(GameObject* object)
{

}


void Corn::State_Dying::Enter(GameObject* object)
{
	Corn* corn = static_cast<Corn*>(object);
	corn->SetVelocity({ Corn::fly_velocity,0 });
	corn->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Dying));
	corn->is_dead = true;
}

void Corn::State_Dying::Update(GameObject* object, double dt)
{

}

void Corn::State_Dying::CheckExit(GameObject* object)
{
	Corn* corn = static_cast<Corn*>(object);
	if (corn->GetGOComponent<CS230::Sprite>()->AnimationEnded()) {
		corn->change_state(&corn->state_dead);
		corn->disappearance = true;
	}
}


void Corn::State_Dead::Enter(GameObject* object)
{
	Corn* corn = static_cast<Corn*>(object);
	corn->SetPosition(corn->origin);
	corn->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::None));
}

void Corn::State_Dead::Update(GameObject* object, double dt)
{
	Corn* corn = static_cast<Corn*>(object);
	corn->dead_time += dt;
}

void Corn::State_Dead::CheckExit(GameObject* object)
{
	Corn* corn = static_cast<Corn*>(object);
	if (corn->dead_time >= resurrection_time) {
		corn->change_state(&corn->state_alive);
	}
}

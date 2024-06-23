/*
File Name:  Drone.cpp
Project:    CS230 Final
Author:     Donghyeon Jo
Created:    June 18, 2024
*/

#include "Drone.h"
#include "..\Engine\Collision.h"
#include "Level.h"

Drone::Drone(Math::vec2 position, Ball* ball)
	: CS230::GameObject(position), origin(position), ball_ptr(ball), is_dead(false), disappearance(false), dead_time(0.0)
{
	AddGOComponent(new CS230::Sprite("Assets/Drone.spt", this));
	AddGOComponent(new Level(*this, 1, level_default, level_default));
	current_state = &state_alive;
	current_state->Enter(this);
}

void Drone::ResolveCollision(GameObject* other_object)
{
	if (other_object->Type() == GameObjectType::Ball) {
		change_state(&state_dying);
	}
}

void Drone::Draw(Math::TransformationMatrix camera_matrix)
{
	if (!disappearance) {
		CS230::GameObject::Draw(camera_matrix);
	}
}

void Drone::State_Alive::Enter(GameObject* object)
{
	Drone* drone = static_cast<Drone*>(object);
	drone->is_dead = false;
	drone->disappearance = false;
	drone->SetPosition(drone->origin);
	drone->SetVelocity({ 0,0 });
	drone->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::None));
}

void Drone::State_Alive::Update(GameObject* object, double dt)
{

}

void Drone::State_Alive::CheckExit(GameObject* object)
{

}


void Drone::State_Dying::Enter(GameObject* object)
{
	Drone* drone = static_cast<Drone*>(object);
	drone->SetVelocity({ Drone::fly_velocity,0 });
	drone->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Dying));
	drone->is_dead = true;
}

void Drone::State_Dying::Update(GameObject* object, double dt)
{

}

void Drone::State_Dying::CheckExit(GameObject* object)
{
	Drone* drone = static_cast<Drone*>(object);
	if (drone->GetGOComponent<CS230::Sprite>()->AnimationEnded()) {
		drone->change_state(&drone->state_dead);
		drone->disappearance = true;
	}
}


void Drone::State_Dead::Enter(GameObject* object)
{
	Drone* drone = static_cast<Drone*>(object);
	drone->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::None));
}

void Drone::State_Dead::Update(GameObject* object, double dt)
{
	Drone* drone = static_cast<Drone*>(object);
	drone->dead_time += dt;
}

void Drone::State_Dead::CheckExit(GameObject* object)
{
	Drone* drone = static_cast<Drone*>(object);
	if (drone->dead_time >= resurrection_time) {
		drone->change_state(&drone->state_alive);
	}
}

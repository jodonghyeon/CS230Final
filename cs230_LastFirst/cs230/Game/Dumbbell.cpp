/*
File Name:  Dumbbell.cpp
Project:    CS230 Final
Author:     Donghyeon Jo
Created:    June 18, 2024
*/

#include "Dumbbell.h"
#include "..\Engine\Collision.h"
#include "Level.h"

Dumbbell::Dumbbell(Math::vec2 position, Ball* ball)
	: CS230::GameObject(position), origin(position), ball_ptr(ball), is_dead(false), disappearance(false), dead_time(0.0)
{
	AddGOComponent(new CS230::Sprite("Assets/Dumbbell.spt", this));
	AddGOComponent(new Level(*this, 1, level_default));
	current_state = &state_alive;
	current_state->Enter(this);
}

void Dumbbell::ResolveCollision(GameObject* other_object)
{
	if (other_object->Type() == GameObjectType::Ball) {
		change_state(&state_dead);
	}
}

void Dumbbell::Draw(Math::TransformationMatrix camera_matrix)
{
	if (!disappearance) {
		CS230::GameObject::Draw(camera_matrix);
	}
}

void Dumbbell::State_Alive::Enter(GameObject* object)
{
	Dumbbell* dumbbell = static_cast<Dumbbell*>(object);
	dumbbell->is_dead = false;
	dumbbell->disappearance = false;
	dumbbell->SetVelocity({ 0,0 });
	dumbbell->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::None));
}

void Dumbbell::State_Alive::Update(GameObject* object, double dt)
{

}

void Dumbbell::State_Alive::CheckExit(GameObject* object)
{

}


void Dumbbell::State_Dying::Enter(GameObject* object)
{
	Dumbbell* dumbbell = static_cast<Dumbbell*>(object);
	dumbbell->SetVelocity({ Dumbbell::fly_velocity,0 });
	dumbbell->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Dying));
	dumbbell->is_dead = true;
}

void Dumbbell::State_Dying::Update(GameObject* object, double dt)
{

}

void Dumbbell::State_Dying::CheckExit(GameObject* object)
{
	Dumbbell* dumbbell = static_cast<Dumbbell*>(object);
	if (dumbbell->GetGOComponent<CS230::Sprite>()->AnimationEnded()) {
		dumbbell->change_state(&dumbbell->state_dead);
		dumbbell->disappearance = true;
	}
}


void Dumbbell::State_Dead::Enter(GameObject* object)
{
	Dumbbell* dumbbell = static_cast<Dumbbell*>(object);
	dumbbell->SetPosition(dumbbell->origin);
	dumbbell->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::None));
}

void Dumbbell::State_Dead::Update(GameObject* object, double dt)
{
	Dumbbell* dumbbell = static_cast<Dumbbell*>(object);
	dumbbell->dead_time += dt;
}

void Dumbbell::State_Dead::CheckExit(GameObject* object)
{
	Dumbbell* dumbbell = static_cast<Dumbbell*>(object);
	if (dumbbell->dead_time >= resurrection_time) {
		dumbbell->change_state(&dumbbell->state_alive);
	}
}

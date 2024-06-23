/*
File Name:  Cone.cpp
Project:    CS230 Final
Author:     Donghyeon Jo
Created:    June 18, 2024
*/

#include "Cone.h"
#include "..\Engine\Collision.h"
#include "Level.h"

Cone::Cone(Math::vec2 position, Ball* ball)
	: CS230::GameObject(position), origin(position), ball_ptr(ball), is_dead(false), disappearance(false), dead_time(0.0)
{
	AddGOComponent(new CS230::Sprite("Assets/Cone.spt", this));
	AddGOComponent(new Level(*this, 1, level_default, level_default));
	current_state = &state_alive;
	current_state->Enter(this);
}

void Cone::ResolveCollision(GameObject* other_object)
{
	if (other_object->Type() == GameObjectType::Ball) {
		change_state(&state_dying);
	}
}

void Cone::Draw(Math::TransformationMatrix camera_matrix)
{
	if (!disappearance) {
		CS230::GameObject::Draw(camera_matrix);
	}
}

void Cone::State_Alive::Enter(GameObject* object)
{
	Cone* cone = static_cast<Cone*>(object);
	cone->is_dead = false;
	cone->disappearance = false;
	cone->SetPosition(cone->origin);
	cone->SetVelocity({ 0,0 });
	cone->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::None));
}

void Cone::State_Alive::Update(GameObject* object, double dt)
{

}

void Cone::State_Alive::CheckExit(GameObject* object)
{

}


void Cone::State_Dying::Enter(GameObject* object)
{
	Cone* cone = static_cast<Cone*>(object);
	cone->SetVelocity({ Cone::fly_velocity,0 });
	cone->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Dying));
	cone->is_dead = true;
}

void Cone::State_Dying::Update(GameObject* object, double dt)
{

}

void Cone::State_Dying::CheckExit(GameObject* object)
{
	Cone* cone = static_cast<Cone*>(object);
	if (cone->GetGOComponent<CS230::Sprite>()->AnimationEnded()) {
		cone->change_state(&cone->state_dead);
		cone->disappearance = true;
	}
}


void Cone::State_Dead::Enter(GameObject* object)
{
	Cone* cone = static_cast<Cone*>(object);
	cone->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::None));
}

void Cone::State_Dead::Update(GameObject* object, double dt)
{
	Cone* cone = static_cast<Cone*>(object);
	cone->dead_time += dt;
}

void Cone::State_Dead::CheckExit(GameObject* object)
{
	Cone* cone = static_cast<Cone*>(object);
	if (cone->dead_time >= resurrection_time) {
		cone->change_state(&cone->state_alive);
	}
}

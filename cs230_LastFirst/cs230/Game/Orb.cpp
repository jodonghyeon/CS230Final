/*
File Name:  Orb.cpp
Project:    CS230 Final
Author:     Donghyeon Jo
Created:    June 18, 2024
*/

#include "Orb.h"
#include "..\Engine\Collision.h"
#include "Level.h"

Orb::Orb(Math::vec2 position, Ball* ball)
	: CS230::GameObject(position), origin(position), ball_ptr(ball), is_dead(false), disappearance(false), dead_time(0.0)
{
	AddGOComponent(new CS230::Sprite("Assets/Orb.spt", this));
	AddGOComponent(new Level(*this, 1, level_default, level_default));
	current_state = &state_alive;
	current_state->Enter(this);
}

void Orb::ResolveCollision(GameObject* other_object)
{
	if (other_object->Type() == GameObjectType::Ball) {
		change_state(&state_dead);
	}
}

void Orb::Draw(Math::TransformationMatrix camera_matrix)
{
	if (!disappearance) {
		CS230::GameObject::Draw(camera_matrix);
	}
}

void Orb::State_Alive::Enter(GameObject* object)
{
	Orb* orb = static_cast<Orb*>(object);
	orb->is_dead = false;
	orb->disappearance = false;
	orb->SetVelocity({ 0,0 });
	orb->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::None));
}

void Orb::State_Alive::Update(GameObject* object, double dt)
{

}

void Orb::State_Alive::CheckExit(GameObject* object)
{

}


void Orb::State_Dying::Enter(GameObject* object)
{
	Orb* orb = static_cast<Orb*>(object);
	orb->SetVelocity({ Orb::fly_velocity,0 });
	orb->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Dying));
	orb->is_dead = true;
}

void Orb::State_Dying::Update(GameObject* object, double dt)
{

}

void Orb::State_Dying::CheckExit(GameObject* object)
{
	Orb* orb = static_cast<Orb*>(object);
	if (orb->GetGOComponent<CS230::Sprite>()->AnimationEnded()) {
		orb->change_state(&orb->state_dead);
		orb->disappearance = true;
	}
}


void Orb::State_Dead::Enter(GameObject* object)
{
	Orb* orb = static_cast<Orb*>(object);
	orb->SetPosition(orb->origin);
	orb->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::None));
}

void Orb::State_Dead::Update(GameObject* object, double dt)
{
	Orb* orb = static_cast<Orb*>(object);
	orb->dead_time += dt;
}

void Orb::State_Dead::CheckExit(GameObject* object)
{
	Orb* orb = static_cast<Orb*>(object);
	if (orb->dead_time >= resurrection_time) {
		orb->change_state(&orb->state_alive);
	}
}

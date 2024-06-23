/*
File Name:  Pin.cpp
Project:    CS230 Final
Author:     Donghyeon Jo
Created:    June 18, 2024
*/

#include "Pin.h"
#include "..\Engine\Collision.h"
#include "Level.h"

Pin::Pin(Math::vec2 position, Ball* ball)
	: CS230::GameObject(position), origin(position), ball_ptr(ball), is_dead(false), disappearance(false) ,dead_time(0.0)
{
	AddGOComponent(new CS230::Sprite("Assets/Pin.spt", this));
	AddGOComponent(new Level(*this, 1, level_default, level_default));
	current_state = &state_alive;
	current_state->Enter(this);
}

void Pin::ResolveCollision(GameObject* other_object)
{
	if (other_object->Type() == GameObjectType::Ball) {
		change_state(&state_dying);
	}
}

void Pin::Draw(Math::TransformationMatrix camera_matrix)
{
	if (!disappearance) {
		CS230::GameObject::Draw(camera_matrix);
	}
}

void Pin::State_Alive::Enter(GameObject* object)
{
	Pin* pin = static_cast<Pin*>(object);
	pin->is_dead = false;
	pin->disappearance = false;
	pin->SetPosition(pin->origin);
	pin->SetVelocity({ 0,0 });
	pin->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::None));
}

void Pin::State_Alive::Update(GameObject* object, double dt)
{
	
}

void Pin::State_Alive::CheckExit(GameObject* object)
{

}


void Pin::State_Dying::Enter(GameObject* object)
{
	Pin* pin = static_cast<Pin*>(object);
	pin->SetVelocity({ Pin::fly_velocity,0 });
	pin->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Dying));
	pin->is_dead = true;
}

void Pin::State_Dying::Update(GameObject* object, double dt)
{

}

void Pin::State_Dying::CheckExit(GameObject* object)
{
	Pin* pin = static_cast<Pin*>(object);
	if (pin->GetGOComponent<CS230::Sprite>()->AnimationEnded()) {
		pin->change_state(&pin->state_dead);
		pin->disappearance = true;
	}
}


void Pin::State_Dead::Enter(GameObject* object)
{
	Pin* pin = static_cast<Pin*>(object);
	pin->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::None));
}

void Pin::State_Dead::Update(GameObject* object, double dt)
{
	Pin* pin = static_cast<Pin*>(object);
	pin->dead_time += dt;
}

void Pin::State_Dead::CheckExit(GameObject* object)
{
	Pin* pin = static_cast<Pin*>(object);
	if (pin->dead_time >= resurrection_time) {
		pin->change_state(&pin->state_alive);
	}
}

/*
File Name:  BigPin.cpp
Project:    CS230 Final
Author:     Donghyeon Jo
Created:    June 18, 2024
*/

#include "BigPin.h"
#include "..\Engine\Collision.h"
#include "Level.h"
#include "..\Engine\Engine.h"

BigPin::BigPin(Math::vec2 position, Ball* ball)
	: CS230::GameObject(position), ball_ptr(ball), is_dead(false)
{
	AddGOComponent(new CS230::Sprite("Assets/BigPin.spt", this));
	AddGOComponent(new Level(*this, 1, level_default, level_default));
	current_state = &state_alive;
	current_state->Enter(this);
}

void BigPin::ResolveCollision(GameObject* other_object)
{
	if (other_object->Type() == GameObjectType::Ball) {
		change_state(&state_dying);
	}
}

void BigPin::Draw(Math::TransformationMatrix camera_matrix)
{
	CS230::GameObject::Draw(camera_matrix);
}

void BigPin::State_Alive::Enter(GameObject* object)
{
	BigPin* big_pin = static_cast<BigPin*>(object);
	big_pin->is_dead = false;
	big_pin->SetVelocity({ 0,0 });
	big_pin->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Sparkling));
}

void BigPin::State_Alive::Update(GameObject* object, double dt)
{

}

void BigPin::State_Alive::CheckExit(GameObject* object)
{
	
}


void BigPin::State_Dying::Enter(GameObject* object)
{
	BigPin* big_pin = static_cast<BigPin*>(object);
	big_pin->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Dying));
	big_pin->is_dead = true;
}

void BigPin::State_Dying::Update(GameObject* object, double dt)
{

}

void BigPin::State_Dying::CheckExit(GameObject* object)
{
}
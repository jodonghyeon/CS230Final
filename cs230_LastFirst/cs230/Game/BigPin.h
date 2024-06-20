/*
File Name:  BigPin.h
Project:    CS230 Final
Author:     Donghyeon Jo
Created:    June 19, 2024
*/

#pragma once
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"
#include "Ball.h"

class BigPin : public CS230::GameObject {
public:
	BigPin(Math::vec2 position, Ball* ball);

	GameObjectType Type() override { return GameObjectType::BigPin; }
	std::string TypeName() override { return "BigPin"; }

	void ResolveCollision(GameObject* other_object)override;
	void Draw(Math::TransformationMatrix camera_matrix)override;

	bool IsAlive() const { return !is_dead; }

	static constexpr int level_default = 5;
private:
	enum class Animations {
		Sparkling,
		Dying
	};

	class State_Alive : public State {
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void CheckExit(GameObject* object) override;
		std::string GetName() override { return "alive"; }
	};

	State_Alive state_alive;

	class State_Dying : public State {
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void CheckExit(GameObject* object) override;
		std::string GetName() override { return "dying"; }
	};

	State_Dying state_dying;

	Ball* ball_ptr;
	bool is_dead;
};
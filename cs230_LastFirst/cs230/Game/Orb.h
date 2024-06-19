/*
File Name:  Orb.h
Project:    CS230 Final
Author:     Donghyeon Jo
Created:    June 18, 2024
*/

#pragma once
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"
#include "Ball.h"

class Orb : public CS230::GameObject {
public:
	Orb(Math::vec2 position, Ball* ball);

	GameObjectType Type() override { return GameObjectType::Orb; }
	std::string TypeName() override { return "Orb"; }

	void ResolveCollision(GameObject* other_object)override;
	void Draw(Math::TransformationMatrix camera_matrix)override;

	bool IsAlive() const { return !is_dead; }

	static constexpr int level_default = 5;
	static constexpr double exp_give = 100.0;
private:
	enum class Animations {
		None,
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

	class State_Dead : public State {
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void CheckExit(GameObject* object) override;
		std::string GetName() override { return "dead"; }
	};

	State_Dead state_dead;

	Math::vec2 origin;
	Ball* ball_ptr;
	bool is_dead;
	bool disappearance;
	double dead_time;
	static constexpr double resurrection_time = 5.0;
	static constexpr double fly_velocity = 300.0;
	static constexpr double default_velocity = 100;
};
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameObjectManager.cpp
Project:    CS230 Engine
Author:     Donghyeon Jo
Created:    April 29, 2024
*/

#include "GameObjectManager.h"
#include "Engine.h"

CS230::GameObjectManager::GameObjectManager()
{
}

void CS230::GameObjectManager::Add(GameObject* object)
{
	objects.push_back(object);
}

void CS230::GameObjectManager::Unload()
{
	for (GameObject* object : objects)
	{
		delete object;
	}
	objects.clear();
}

void CS230::GameObjectManager::UpdateAll(double dt)
{
	std::vector<GameObject*> destroy_objects;
	for (GameObject* object : objects)
	{
		object->Update(dt);
		if (object->Destroyed()) {
			destroy_objects.push_back(object);
		}
	}
	for (GameObject* object : destroy_objects) {
		objects.remove(object);
		delete object;
	}
}

void CS230::GameObjectManager::DrawAll(Math::TransformationMatrix camera_matrix)
{
	for (GameObject* object : objects)
	{
		object->Draw(camera_matrix);
	}
}

void CS230::GameObjectManager::CollisionTest()
{
	for (GameObject* object_1 : objects) {
		for (GameObject* object_2 : objects) {
			if (object_1 != object_2 && object_1->CanCollideWith(object_2->Type())) {
				if (object_1->IsCollidingWith(object_2)) {
					Engine::GetLogger().LogEvent("Collision Detected: " + object_1->TypeName() + " and " + object_2->TypeName());
					object_1->ResolveCollision(object_2);
				}
			}
		}
	}
}



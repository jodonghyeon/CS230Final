/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameObjectManager.h
Project:    CS230 Engine
Author:     Donghyeon Jo
Created:    April 29, 2024
*/

#pragma once
#include <list>
#include "GameObject.h"
#include "Matrix.h"

namespace CS230 {
    class GameObjectManager :public Component {
    public:
        GameObjectManager();

        void Add(GameObject* object);
        void Unload();

        void UpdateAll(double dt);
        void DrawAll(Math::TransformationMatrix camera_matrix);

        void CollisionTest();
    private:
        std::list<GameObject*> objects;
    };
}

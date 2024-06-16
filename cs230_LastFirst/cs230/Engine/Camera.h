/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Camera.h
Project:    CS230 Engine
Author:     Donghyeon Jo
Created:    April 6, 2024
*/

#pragma once

#include "Component.h"
#include "Vec2.h"
#include "Rect.h"
#include "Matrix.h"
#include "GameObject.h"

namespace CS230 {
    class Camera : public Component {
    public:
        Camera(Math::rect player_zone);
        void SetPosition(Math::vec2 new_position);
        const Math::vec2& GetPosition() const;
        void SetLimit(Math::irect new_limit);
        const Math::irect& GetLimit() const;
        void Update(const Math::vec2& player_position);
        Math::TransformationMatrix GetMatrix();

    private:
        Math::irect limit;
        Math::vec2 position;
        Math::rect player_zone;
    };

    class DampingCamera : public Component {
    public:
        DampingCamera(Math::irect limit, double dampingFactor=0.5);
        void SetPosition(Math::vec2 new_position);
        const Math::vec2& GetPosition() const;
        void SetLimit(Math::irect new_limit);
        const Math::irect& GetLimit() const;
        void SetDampingFactor(double new_dampingFactor);
        void Update(CS230::GameObject* player, double dt);
        Math::TransformationMatrix GetMatrix();

    private:
        Math::irect limit;
        Math::vec2 position;
        double dampingFactor;
    };
}


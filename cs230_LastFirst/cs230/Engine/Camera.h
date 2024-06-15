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

namespace CS230 {
    class Camera : public Component {
    public:
        Camera(Math::rect player_zone);
        void SetPosition(Math::vec2 new_position);
        const Math::vec2& GetPosition() const;
        void SetLimit(Math::irect new_limit);
        void Update(const Math::vec2& player_position);
        Math::TransformationMatrix GetMatrix();

    private:
        Math::irect limit;
        Math::vec2 position;
        Math::rect player_zone;
    };
}


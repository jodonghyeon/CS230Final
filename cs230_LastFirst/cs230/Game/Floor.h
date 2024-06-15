/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Floor.h
Project:    CS230 Engine
Author:     Donghyeon Jo
Created:    June 2, 2024
*/

#pragma once
#include "..\Engine\GameObject.h"
#include "..\Engine\Rect.h"
#include "GameObjectTypes.h"

class Floor : public CS230::GameObject {
public:
    Floor(Math::irect boundary);
    std::string TypeName() override { return "Floor"; }
    virtual GameObjectType Type() override { return GameObjectType::Floor; }
};

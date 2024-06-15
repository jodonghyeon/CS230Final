/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Crates.h
Project:    CS230 Engine
Author:     Donghyeon Jo
Created:    May 1, 2024
*/

#pragma once
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

class Crates : public CS230::GameObject {
public:
    Crates(Math::vec2 position, int size);

    GameObjectType Type() override { return GameObjectType::Crates; }
    std::string TypeName() override { return "Crates"; }
};

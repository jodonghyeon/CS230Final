/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Splash.h
Project:    CS230 Engine
Author:     Donghyeon Jo
Created:    March 14, 2024
*/

#pragma once
#include "..\Engine\GameState.h"
#include "..\Engine\Texture.h"

class Splash : public CS230::GameState {
public:
    Splash();
    void Load() override;
    void Update([[maybe_unused]] double dt) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override {
        return "Splash";
    }

public:
    double counter = 0;
    CS230::Texture* texture;
};

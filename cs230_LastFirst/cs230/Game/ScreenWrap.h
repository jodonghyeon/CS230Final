/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  ScreenWrap.h
Project:    CS230 Engine
Author:     Donghyeon Jo
Created:    May 15, 2024
*/

#pragma once
#include "..\Engine\GameObject.h"

class ScreenWrap : public CS230::Component {
public:
    ScreenWrap(CS230::GameObject& object) : object(object) {}
    void Update(double dt) override;
private:
    CS230::GameObject& object;
};
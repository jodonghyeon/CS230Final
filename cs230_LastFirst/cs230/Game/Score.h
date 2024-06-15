/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Score.h
Project:    CS230 Engine
Author:     Donghyeon Jo
Created:    June 2, 2024
*/

#pragma once
#include "..\Engine\Component.h"

class Score : public CS230::Component {
public:
    Score(int start_score):score(start_score){}
    void Add(int value) { score += value; };
    int Value() const { return score; };
private:
    int score;
};
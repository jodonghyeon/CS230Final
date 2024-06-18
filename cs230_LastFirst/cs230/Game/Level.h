/*
File Name:  Level.h
Project:    CS230 Final
Author:     Donghyeon Jo
Created:    June 18, 2024
*/

#pragma once
#include "..\Engine\GameObject.h"

class Level : public CS230::Component {
public:
    Level(CS230::GameObject& object, double exp_max, int start_level = 1)
        : object(object), exp_max(exp_max), level(start_level)
    {
        exp = 0.0;
    }

    void SetEXPMax(double new_exp_max) { exp_max = new_exp_max; }
    double GetEXPMax()const { return exp_max; }

    void UpdateLevel(int delta) { level += delta; is_level_updated = true; }
    void LevelUp() { UpdateLevel(1); }
    void LevelDown() { UpdateLevel(-1); }
    int GetLevel()const { return level; }

    void SetEXP(double new_exp) { exp = new_exp; }
    void UpdateEXP(double delta) { exp += delta; }
    double GetEXP()const { return exp; }

    void ResetIsLevelUpdated(){ is_level_updated = false; }
    bool IsLevelUpdated()const { return is_level_updated; }
    void Update(double dt) override
    { 
        if(exp>=exp_max){
            LevelUp();
        }
    }
private:
    CS230::GameObject& object;
    double exp_max;
    int level;
    double exp;
    bool is_level_updated;
};
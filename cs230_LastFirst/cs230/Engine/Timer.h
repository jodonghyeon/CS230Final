/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Timer.h
Project:    CS230 Engine
Author:     Donghyeon Jo
Created:    May 15, 2024
*/

#pragma once
#include "Component.h"

namespace CS230 {
    class Timer : public Component {
    public:
        /*Timer(double timer_max);
        void Update(double dt) override;

        const int GetTimer() const { return last_timer; }*/
        Timer(double time_remaining);
        void Set(double time_remaining);
        void Update(double dt) override;
        void Reset();
        double Remaining();
        int RemainingInt();
        bool TickTock();

    private:
        double timer;
        double timer_max;
        bool pendulum;
        //int last_timer;
    };
}
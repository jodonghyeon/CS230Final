/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Input.h
Project:    CS230 Engine
Author:     Donghyeon Jo
Created:    March 21, 2024
*/

#pragma once
#include <vector>

namespace CS230 {
    class Input {
    public:
        enum class Keys {
            Zero, One, Two, Three, Four,
            Five, Six, Seven, Eight, Nine,
            A, B, C, D, E, F, G, H, I, J, K, L, M,
            N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
            Space, Escape, Enter, Tab, 
            Left, Up, Right, Down,
            Count
        };

        Input();
        void Update();
        bool KeyDown(Keys key);
        bool KeyJustPressed(Keys key);
        bool KeyJustReleased(Keys key);
        void SetKeyDown(Keys key, bool value);
    private:
        std::vector<bool> keys_down;
        std::vector<bool> previous_keys_down;
    };
}



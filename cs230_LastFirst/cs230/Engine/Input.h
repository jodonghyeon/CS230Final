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
#include "Vec2.h"

namespace CS230 {
    class Input {
    public:

        Input();
        void Update();

        enum class Keys {
            Zero, One, Two, Three, Four,
            Five, Six, Seven, Eight, Nine,
            A, B, C, D, E, F, G, H, I, J, K, L, M,
            N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
            Space, Escape, Enter, Tab, 
            Left, Up, Right, Down,
            Count
        };

        bool KeyDown(Keys key);
        bool KeyJustPressed(Keys key);
        bool KeyJustReleased(Keys key);
        void SetKeyDown(Keys key, bool value);

        enum class MouseButtons {
            Left, Right, Wheel, Side,
            Count
        };

        bool MouseButtonDown(MouseButtons mouse_button);
        bool MouseButtonJustPressed(MouseButtons mouse_button);
        bool MouseButtonJustReleased(MouseButtons mouse_button);
        void SetMouseButtonDown(MouseButtons mouse_button, bool value);

        bool IsMouseMoved()const;
        Math::vec2 GetMousePosition()const;
        Math::vec2 GetMouseDelta()const;

    private:
        std::vector<bool> keys_down;
        std::vector<bool> previous_keys_down;
        std::vector<bool> mouse_buttons_down;
        std::vector<bool> previous_mouse_buttons_down;
        Math::vec2 mouse_position;
        Math::vec2 previous_mouse_position;
    };
}



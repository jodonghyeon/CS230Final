/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Input.h
Project:    CS230 Engine
Author:     Donghyeon Jo
Created:    March 21, 2024
*/

#include "Input.h"
#include "Engine.h"
#include <raylib.h>

constexpr int cs230_to_rl(CS230::Input::Keys cs230_key) noexcept {
    switch (cs230_key) {
    case CS230::Input::Keys::Zero:
        return KEY_ZERO;
    case CS230::Input::Keys::One:
        return KEY_ONE;
    case CS230::Input::Keys::Two:
        return KEY_TWO;
    case CS230::Input::Keys::Three:
        return KEY_THREE;
    case CS230::Input::Keys::Four:
        return KEY_FOUR;
    case CS230::Input::Keys::Five:
        return KEY_FIVE;
    case CS230::Input::Keys::Six:
        return KEY_SIX;
    case CS230::Input::Keys::Seven:
        return KEY_SEVEN;
    case CS230::Input::Keys::Eight:
        return KEY_EIGHT;
    case CS230::Input::Keys::Nine:
        return KEY_NINE;
    case CS230::Input::Keys::A:
        return KEY_A;
    case CS230::Input::Keys::B:
        return KEY_B;
    case CS230::Input::Keys::C:
        return KEY_C;
    case CS230::Input::Keys::D:
        return KEY_D;
    case CS230::Input::Keys::E:
        return KEY_E;
    case CS230::Input::Keys::F:
        return KEY_F;
    case CS230::Input::Keys::G:
        return KEY_G;
    case CS230::Input::Keys::H:
        return KEY_H;
    case CS230::Input::Keys::I:
        return KEY_I;
    case CS230::Input::Keys::J:
        return KEY_J;
    case CS230::Input::Keys::K:
        return KEY_K;
    case CS230::Input::Keys::L:
        return KEY_L;
    case CS230::Input::Keys::M:
        return KEY_M;
    case CS230::Input::Keys::N:
        return KEY_N;
    case CS230::Input::Keys::O:
        return KEY_O;
    case CS230::Input::Keys::P:
        return KEY_P;
    case CS230::Input::Keys::Q:
        return KEY_Q;
    case CS230::Input::Keys::R:
        return KEY_R;
    case CS230::Input::Keys::S:
        return KEY_S;
    case CS230::Input::Keys::T:
        return KEY_T;
    case CS230::Input::Keys::U:
        return KEY_U;
    case CS230::Input::Keys::V:
        return KEY_V;
    case CS230::Input::Keys::W:
        return KEY_W;
    case CS230::Input::Keys::X:
        return KEY_X;
    case CS230::Input::Keys::Y:
        return KEY_Y;
    case CS230::Input::Keys::Z:
        return KEY_Z;
    case CS230::Input::Keys::Space:
        return KEY_SPACE;
    case CS230::Input::Keys::Escape:
        return KEY_ESCAPE;
    case CS230::Input::Keys::Enter:
        return KEY_ENTER;
    case CS230::Input::Keys::Tab:
        return KEY_TAB;
    case CS230::Input::Keys::Left:
        return KEY_LEFT;
    case CS230::Input::Keys::Up:
        return KEY_UP;
    case CS230::Input::Keys::Right:
        return KEY_RIGHT;
    case CS230::Input::Keys::Down:
        return KEY_DOWN;
    default:
        return -1;
    }
}

constexpr int cs230_to_rl_mouse(CS230::Input::MouseButtons cs230_mouse_button) noexcept {
    switch (cs230_mouse_button)
    {
    case CS230::Input::MouseButtons::Left:
        return MOUSE_BUTTON_LEFT;
    case CS230::Input::MouseButtons::Right:
        return MOUSE_BUTTON_RIGHT;
    case CS230::Input::MouseButtons::Wheel:
        return MOUSE_BUTTON_MIDDLE;
    case CS230::Input::MouseButtons::Side:
        return MOUSE_BUTTON_SIDE;
    default:
        return -1;
    }
}

constexpr CS230::Input::Keys& operator++(CS230::Input::Keys& key) noexcept {
    key = static_cast<CS230::Input::Keys>(static_cast<unsigned>(key) + 1);
    return key;
}

constexpr CS230::Input::MouseButtons& operator++(CS230::Input::MouseButtons& mouse_button) noexcept {
    mouse_button = static_cast<CS230::Input::MouseButtons>(static_cast<unsigned>(mouse_button) + 1);
    return mouse_button;
}

bool CS230::Input::KeyDown(Keys key) {
    return keys_down[static_cast<int>(key)];
}

bool CS230::Input::KeyJustPressed(Keys key) {
    return keys_down[static_cast<int>(key)] == true && previous_keys_down[static_cast<int>(key)] == false;
}

bool CS230::Input::KeyJustReleased(Keys key) {
    return keys_down[static_cast<int>(key)] == false && previous_keys_down[static_cast<int>(key)] == true;
}

void CS230::Input::SetKeyDown(Keys key, bool value) {
    keys_down[static_cast<int>(key)] = value;
}


bool CS230::Input::MouseButtonDown(MouseButtons mouse_button){
    return mouse_buttons_down[static_cast<int>(mouse_button)];
}

bool CS230::Input::MouseButtonJustPressed(MouseButtons mouse_button){
    return mouse_buttons_down[static_cast<int>(mouse_button)] == true && previous_mouse_buttons_down[static_cast<int>(mouse_button)] == false;
}

bool CS230::Input::MouseButtonJustReleased(MouseButtons mouse_button){
    return mouse_buttons_down[static_cast<int>(mouse_button)] == false && previous_mouse_buttons_down[static_cast<int>(mouse_button)] == true;
}

void CS230::Input::SetMouseButtonDown(MouseButtons mouse_button, bool value){
    mouse_buttons_down[static_cast<int>(mouse_button)] = value;
}

bool CS230::Input::IsMouseMoved() const
{
    return mouse_position.x != previous_mouse_position.x && mouse_position.y != previous_mouse_position.y;
}

Math::vec2 CS230::Input::GetMousePosition() const
{
    return mouse_position;
}

Math::vec2 CS230::Input::GetMouseDelta() const
{
    return { mouse_position.x - previous_mouse_position.x, mouse_position.y - previous_mouse_position.y };
}

CS230::Input::Input() {
    keys_down.resize(static_cast<int>(Keys::Count));
    previous_keys_down.resize(static_cast<int>(Keys::Count));
    mouse_buttons_down.resize(static_cast<int>(MouseButtons::Count));
    previous_mouse_buttons_down.resize(static_cast<int>(MouseButtons::Count));
}

void CS230::Input::Update() {
    previous_keys_down = keys_down;
    for (Keys key = Keys::Zero; key < Keys::Count; ++key) {
        const auto rl_key = cs230_to_rl(static_cast<Keys>(key));
        SetKeyDown(key, IsKeyDown(rl_key));
        if (KeyJustPressed(key)) {
            Engine::GetLogger().LogDebug("Key Pressed");
        }
        else if (KeyJustReleased(key)) {
            Engine::GetLogger().LogDebug("Key Released");
        }
    }

    previous_mouse_buttons_down = mouse_buttons_down;
    for (MouseButtons mouse_button = MouseButtons::Left; mouse_button < MouseButtons::Count; ++mouse_button) {
        const auto rl_mouse_button = cs230_to_rl_mouse(static_cast<MouseButtons>(mouse_button));
        SetMouseButtonDown(mouse_button, IsMouseButtonDown(rl_mouse_button));
        if (MouseButtonJustPressed(mouse_button)) {
            Engine::GetLogger().LogDebug("MouseButton Pressed");
        }
        else if (MouseButtonJustReleased(mouse_button)) {
            Engine::GetLogger().LogDebug("MouseButton Released");
        }
    }

    previous_mouse_position = mouse_position;
    mouse_position = { (double)GetMouseX(),(double)(Engine::GetWindow().GetSize().y-GetMouseY()) };
}

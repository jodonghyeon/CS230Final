/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Window.cpp
Project:    CS230 Engine
Author:     Donghyeon Jo
Created:    March 14, 2024
*/

#include "Window.h"
#include "Engine.h"

void CS230::Window::Start(std::string title) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
    InitWindow(default_width, default_height, title.c_str());
    SetExitKey(KEY_NULL);
    rlDisableBackfaceCulling();
    BeginDrawing();
    Clear(default_background);
    size = { default_width, default_height };
    resized_current_frame = true;
}

void CS230::Window::Update() {
    EndDrawing();
    resized_current_frame = false;

    int current_width = GetScreenWidth();
    int current_height = GetScreenHeight();
    if (current_width != size.x || current_height != size.y) {
        resized_current_frame = true;
        Engine::GetLogger().LogEvent("Window Resized");
        size = { current_width, current_height };
    }
    BeginDrawing();
}

void CS230::Window::SetSize(int width, int height)
{
    SetWindowSize(width, height);
}

bool CS230::Window::IsClosed() const {
    return WindowShouldClose();
}

Math::ivec2 CS230::Window::GetSize() const {
    return size;
}

void CS230::Window::Clear(unsigned int rgba) {
    const Color rl_color = Color{
        static_cast<unsigned char>((rgba & 0xff000000) >> 24),
        static_cast<unsigned char>((rgba & 0x00ff0000) >> 16),
        static_cast<unsigned char>((rgba & 0x0000ff00) >> 8),
        static_cast<unsigned char>((rgba & 0x000000ff) >> 0)
    };

    ClearBackground(rl_color);
}

bool CS230::Window::IsResized() const
{
    return resized_current_frame;
}

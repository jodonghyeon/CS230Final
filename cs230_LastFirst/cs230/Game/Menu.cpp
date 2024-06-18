/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Menu.cpp
Project:    CS230 Engine
Author:     Donghyeon Jo
Created:    March 14, 2024
*/

#include "..\Engine\Engine.h"
#include "States.h"
#include "Menu.h"
#include "Fonts.h"

Menu::Menu(){ }

void Menu::Load()
{
    select = 1;
    title_texture = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("CS230 Engine Test", 0xA287FDFF);
    mode1_texture = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Side Scroller", 0xFFFFFFFF);
    mode2_texture = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Space Shooter", 0x81AC00FF);
    mode3_texture = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Unstoppable BB", 0x81AC00FF);
    exit_texture = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Exit", 0x81AC00FF);
}

void Menu::Update(double dt)
{
    //Engine::GetLogger().LogDebug("mouseX: " + std::to_string(Engine::GetInput().GetMousePosition().x) + " mouseY: " + std::to_string(Engine::GetInput().GetMousePosition().y));
    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Down)&&select<max_select) {
        update_select_text(select, 0x81AC00FF);
        ++select;
        update_select_text(select, 0xFFFFFFFF);
    }
    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Up) && select > 1) {
        update_select_text(select, 0x81AC00FF);
        --select;
        update_select_text(select, 0xFFFFFFFF);
    }

    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Enter)) {
        if (select == 1) {
            Engine::GetWindow().SetSize(800, 600);
        }
        else if (select == 2) {
            Engine::GetWindow().SetSize(800, 600);
        }
        else if (select == 3) {
            Engine::GetWindow().SetSize(1280, 720);
        }
    }

    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Enter)) {
        if (select == 1) {
            update_select_text(select, 0xFFFFFFFF);
            Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Mode1));
        }
        else if (select == 2) {
            update_select_text(select, 0xFFFFFFFF);
            Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Mode2));
        }
        else if (select == 3) {
            update_select_text(select, 0xFF0000FF);
            Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Mode3));
        }
        else if (select == 4) {
            Engine::GetGameStateManager().ClearNextGameState();
        }
    }
}

void Menu::Unload()
{ }

void Menu::Draw()
{
    Engine::GetWindow().Clear(0x1B1B1EFF);
    const double title_scaler = 1.5;
    title_texture->Draw(Math::TranslationMatrix(Math::vec2{ (double)(Engine::GetWindow().GetSize().x - title_scaler *title_texture->GetSize().x)/2, (double)(0.75*Engine::GetWindow().GetSize().y) }) * Math::ScaleMatrix(Math::vec2{ title_scaler,title_scaler }));
    mode1_texture->Draw(Math::TranslationMatrix(Math::vec2{ (double)(Engine::GetWindow().GetSize().x - mode1_texture->GetSize().x) / 2, (double)(0.65 * Engine::GetWindow().GetSize().y - mode1_texture->GetSize().y) }));
    mode2_texture->Draw(Math::TranslationMatrix(Math::vec2{ (double)(Engine::GetWindow().GetSize().x - mode2_texture->GetSize().x) / 2, (double)(0.5 * Engine::GetWindow().GetSize().y - mode2_texture->GetSize().y) }));
    mode3_texture->Draw(Math::TranslationMatrix(Math::vec2{ (double)(Engine::GetWindow().GetSize().x - mode3_texture->GetSize().x) / 2, (double)(0.35 * Engine::GetWindow().GetSize().y - mode3_texture->GetSize().y) }));
    exit_texture->Draw(Math::TranslationMatrix(Math::vec2{ (double)(Engine::GetWindow().GetSize().x - exit_texture->GetSize().x) / 2, (double)(0.2*Engine::GetWindow().GetSize().y - exit_texture->GetSize().y) }));
}

void Menu::update_select_text(int select,unsigned int color)
{
    if (select == 1) {
        mode1_texture = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Side Scroller", color);
    }
    else if (select == 2) {
        mode2_texture = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Space Shooter", color);
    }
    else if (select == 3) {
        mode3_texture = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Unstoppable BB", color);
    }
    else if (select == 4) {
        exit_texture = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Exit", color);
    }
}
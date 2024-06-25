/*
File Name:  Ending.cpp
Project:    CS230 Final
Author:     Donghyeon Jo
Created:    June 16, 2024
*/

#include "..\Engine\Engine.h"
#include "States.h"
#include "Ending.h"
#include "Fonts.h"

Ending::Ending() 
{ 
    cleared = false;
}

void Ending::Load()
{
    thanks_text = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Thanks for playing", 0xA287FDFF);
    donghyeon_text = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Tech Producer : Donghyeon Jo", 0xFFFFFFFF);
    jiyun_text = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Art Producer : Jiyun Seok", 0xFFFFFFFF);
    exit_to_menu_text = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Press enter to exit the menu", 0x81AC00FF);
    ending_sound = Engine::GetGameAudioManager().LoadSound("Assets/GameEndingSound.mp3");
    cleared = true;
    ending_sound->Play();
}

void Ending::Update(double dt)
{

    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Enter)) {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Menu));
    }

}

void Ending::Unload()
{ }

void Ending::Draw()
{
    Engine::GetWindow().Clear(0xFFFF00FF);
    const double title_scaler = 1.5;
    thanks_text->Draw(Math::TranslationMatrix(Math::vec2{ (double)(Engine::GetWindow().GetSize().x - title_scaler * thanks_text->GetSize().x) / 2, (double)(0.75 * Engine::GetWindow().GetSize().y) }) * Math::ScaleMatrix(Math::vec2{ title_scaler,title_scaler }));
    donghyeon_text->Draw(Math::TranslationMatrix(Math::vec2{ (double)(Engine::GetWindow().GetSize().x - donghyeon_text->GetSize().x) / 2, (double)(0.65 * Engine::GetWindow().GetSize().y - donghyeon_text->GetSize().y) }));
    jiyun_text->Draw(Math::TranslationMatrix(Math::vec2{ (double)(Engine::GetWindow().GetSize().x - jiyun_text->GetSize().x) / 2, (double)(0.5 * Engine::GetWindow().GetSize().y - jiyun_text->GetSize().y) }));
    exit_to_menu_text->Draw(Math::TranslationMatrix(Math::vec2{ (double)(Engine::GetWindow().GetSize().x - exit_to_menu_text->GetSize().x) / 2, (double)(0.35 * Engine::GetWindow().GetSize().y - exit_to_menu_text->GetSize().y) }));
}
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode1.cpp
Project:    CS230 Engine
Author:     Donghyeon Jo
Created:    March 14, 2024
*/

#include "Mode1.h"
#include "States.h"
#include "..\Engine\Engine.h"
#include "..\Engine\ShowCollision.h"
#include "..\Engine\Camera.h"
#include "Gravity.h"
#include "..\Engine\Timer.h"
#include "..\Engine\GameObjectManager.h"
#include "Background.h"
#include "..\Engine\Vec2.h"
#include "Fonts.h"
#include "Cat.h"
#include "Asteroid.h"
#include "Crates.h"
#include "Robot.h"
#include "Floor.h"
#include "Portal.h"
#include "Score.h"
#include "..\Engine\Particle.h"
#include "Particles.h"
#include "Platform.h"
#include "Platforms.h"

Mode1::Mode1():cat_ptr(nullptr),timer_texture(nullptr),last_time((int)timer_max),score_texture(nullptr),last_score(0)
{ }

void Mode1::Load() {
#ifdef _DEBUG
    AddGSComponent(new CS230::ShowCollision());
#endif
    AddGSComponent(new CS230::Camera({ { 0.15 * Engine::GetWindow().GetSize().x, 0.7 * Engine::GetWindow().GetSize().y }, { 0.35 * Engine::GetWindow().GetSize().x, 0.8 * Engine::GetWindow().GetSize().y } }));
    AddGSComponent(new Gravity(gravity));
    AddGSComponent(new CS230::Timer(timer_max));
    last_time = timer_max;
    AddGSComponent(new Score(0));
    last_score = 0;
    score_texture = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Score: " + std::to_string(last_score), 0xFFFFFFFF);
    AddGSComponent(new CS230::GameObjectManager());
    AddGSComponent(new Background());
    AddGSComponent(new CS230::ParticleManager<Particles::Smoke>());


    Background* background = GetGSComponent<Background>();
    background->Add("Assets/Planets.png", 0.25);
    background->Add("Assets/Ships.png", 0.5);
    background->Add("Assets/Foreground.png", 1);

    CS230::GameObjectManager* gameobjectmanager = GetGSComponent<CS230::GameObjectManager>();
    Floor* starting_floor_ptr = new Floor(Math::irect{ { 0, 0 }, { 930, static_cast<int>(floor) } });
    gameobjectmanager->Add(starting_floor_ptr);
    cat_ptr = new Cat({ 300, floor });
    gameobjectmanager->Add(cat_ptr);
    gameobjectmanager->Add(new Asteroid({ 600, floor }));
    gameobjectmanager->Add(new Asteroid({ 1800, floor }));
    gameobjectmanager->Add(new Asteroid({ 2400, floor }));
    gameobjectmanager->Add(new Crates({ 900, floor }, 2));
    gameobjectmanager->Add(new Crates({ 1400, floor }, 1));
    gameobjectmanager->Add(new Crates({ 2000, floor }, 5));
    gameobjectmanager->Add(new Crates({ 4000, floor }, 3));
    gameobjectmanager->Add(new Crates({ 5400, floor }, 1));
    gameobjectmanager->Add(new Crates({ 5500, floor }, 3));
    gameobjectmanager->Add(new Crates({ 5600, floor }, 5));
    gameobjectmanager->Add(new Robot({ 1025, floor }, cat_ptr, 1025, 1350));
    gameobjectmanager->Add(new Robot({ 2050, floor }, cat_ptr, 2050, 2325));
    gameobjectmanager->Add(new Robot({ 3400, floor }, cat_ptr, 3400, 3800));
    gameobjectmanager->Add(new Robot({ 4225, floor }, cat_ptr, 4225, 4800));
    gameobjectmanager->Add(new Floor(Math::irect{ { 1014, 0 }, { 2700, static_cast<int>(floor) } }));
    gameobjectmanager->Add(new Floor(Math::irect{ { 2884, 0 }, { 4126, static_cast<int>(floor) } }));
    gameobjectmanager->Add(new Floor(Math::irect{ { 4208, 0 }, { 5760, static_cast<int>(floor) } }));
    gameobjectmanager->Add(new Platform({ 800, 200 }, 420, Platforms::Underground));
    gameobjectmanager->Add(new Platform({ 1500, 200 }, 420, Platforms::Underground));
    gameobjectmanager->Add(new Portal(static_cast<int>(States::Menu), Math::irect{ { background->GetSize().x - 10,0}, {background->GetSize()} }));

    CS230::Camera* camera = GetGSComponent<CS230::Camera>();
    camera->SetPosition({ 0,0 });
    camera->SetLimit({ {0,0},background->GetSize() - Engine::GetWindow().GetSize() });
}

void Mode1::Update([[maybe_unused]] double dt) {
    UpdateGSComponents(dt);
    GetGSComponent<CS230::GameObjectManager>()->UpdateAll(dt);

    GetGSComponent<CS230::Camera>()->Update(cat_ptr->GetPosition());

    if (GetGSComponent<CS230::Timer>()->RemainingInt() < last_time) {
        last_time = GetGSComponent<CS230::Timer>()->RemainingInt();
        update_timer_text(last_time);
    }

    if (GetGSComponent<CS230::Timer>()->RemainingInt() == 0) {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Menu));
    }


    if (GetGSComponent<Score>()->Value() != last_score) {
        last_score = GetGSComponent<Score>()->Value();
        score_texture = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Score: " + std::to_string(last_score), 0xFFFFFFFF);
    }

    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Escape)) {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Menu));
    }
}

void Mode1::Draw() {
    Engine::GetWindow().Clear(0x000000FF);

    Math::TransformationMatrix camera_matrix = GetGSComponent<CS230::Camera>()->GetMatrix();

    GetGSComponent<Background>()->Draw(*GetGSComponent<CS230::Camera>());
    GetGSComponent<CS230::GameObjectManager>()->DrawAll(camera_matrix);

    timer_texture->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x - 10 - timer_texture->GetSize().x, Engine::GetWindow().GetSize().y - timer_texture->GetSize().y - 5 }));

    score_texture->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x - 10 - score_texture->GetSize().x, Engine::GetWindow().GetSize().y - timer_texture->GetSize().y - score_texture->GetSize().y - 5 }));
}


void Mode1::Unload() {
    GetGSComponent<Background>()->Unload();
    GetGSComponent<CS230::GameObjectManager>()->Unload();
    ClearGSComponents();
    cat_ptr = nullptr;
}

void Mode1::update_timer_text(int value) {
    timer_texture = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Timer: " + std::to_string(value), 0xFFFFFFFF);
}


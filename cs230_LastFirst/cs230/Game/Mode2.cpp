/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode2.cpp
Project:    CS230 Engine
Author:     Donghyeon Jo
Created:    March 14, 2024
*/

#include "Mode2.h"
#include "..\Engine\Timer.h"
#include "..\Engine\GameObjectManager.h"
#include "..\Engine\Engine.h"
#include "..\Engine\ShowCollision.h"
#include "States.h"
#include "Meteor.h"
#include "Fonts.h"
#include "Score.h"
#include "..\Engine\Particle.h"
#include "Particles.h"

Mode2::Mode2():ship(nullptr), score_texture(nullptr), last_score(0), gameover_texture(nullptr),restart_texture(nullptr)
{ }

void Mode2::Load() { 
#ifdef _DEBUG
    AddGSComponent(new CS230::ShowCollision());
#endif
    AddGSComponent(new CS230::Timer(meteor_timer));
    AddGSComponent(new Score(0));
    last_score = 0;
    score_texture = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Score: " + std::to_string(last_score), 0xFFFFFFFF);

    AddGSComponent(new CS230::GameObjectManager());
    ship = new Ship({ (double)Engine::GetWindow().GetSize().x / 2, (double)Engine::GetWindow().GetSize().y / 2 }, 0, { 0.75,0.75 });

    CS230::GameObjectManager* gameobjectmanager = GetGSComponent<CS230::GameObjectManager>();
    gameobjectmanager->Add(ship);

    AddGSComponent(new CS230::ParticleManager<Particles::Hit>());
    AddGSComponent(new CS230::ParticleManager<Particles::MeteorBit>());

    restart_texture = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Press R To Restart", 0xFFFFFFFF);
    gameover_texture = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Game Over!", 0xFFFFFFFF);
}

void Mode2::Draw() {
    Engine::GetWindow().Clear(0x000000FF);
    GetGSComponent<CS230::GameObjectManager>()->DrawAll(Math::TransformationMatrix());

    score_texture->Draw(Math::TranslationMatrix(Math::ivec2{ 10, Engine::GetWindow().GetSize().y - score_texture->GetSize().y - 5 }));

    if (ship->Exploded()) {
        restart_texture->Draw(Math::TranslationMatrix(Math::ivec2{ (Engine::GetWindow().GetSize().x - restart_texture->GetSize().x) / 2, Engine::GetWindow().GetSize().y - restart_texture->GetSize().y - 90 }));
        gameover_texture->Draw(Math::TranslationMatrix(Math::ivec2{ (Engine::GetWindow().GetSize().x - gameover_texture->GetSize().x) / 2, Engine::GetWindow().GetSize().y - gameover_texture->GetSize().y - 400 }));
    }
}

void Mode2::Update([[maybe_unused]] double dt) {
    UpdateGSComponents(dt);
    GetGSComponent<CS230::GameObjectManager>()->UpdateAll(dt);
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Escape)) {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Menu));
    }
    if (!ship->Exploded()&& GetGSComponent<CS230::Timer>()->Remaining() <= 0) {
        GetGSComponent<CS230::GameObjectManager>()->Add(new Meteor());
        GetGSComponent<CS230::Timer>()->Reset();
    }

    if (GetGSComponent<Score>()->Value() != last_score) {
        last_score = GetGSComponent<Score>()->Value();
        score_texture = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Score: " + std::to_string(last_score), 0xFFFFFFFF);
    }

    if (ship->Exploded() && Engine::GetInput().KeyJustReleased(CS230::Input::Keys::R)) {
        Engine::GetGameStateManager().ReloadState();
    }
}

void Mode2::Unload() {
    GetGSComponent<CS230::GameObjectManager>()->Unload();
    ClearGSComponents();
    ship = nullptr;
}
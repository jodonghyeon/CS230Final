/*
File Name:  Mode3.cpp
Project:    CS230 Final
Author:     Donghyeon Jo
Created:    June 16, 2024
*/

#include "Mode3.h"
#include "States.h"
#include "..\Engine\Engine.h"
#include "..\Engine\ShowCollision.h"
#include "..\Engine\Camera.h"
#include "Gravity.h"
#include "..\Engine\GameObjectManager.h"
#include "Background.h"
#include "..\Engine\Vec2.h"
#include "Ball.h"
#include "..\Engine\Particle.h"
#include "Particles.h"
#include "Platform.h"
#include "Platforms.h"
#include "Pin.h"
#include "Dumbbell.h"
#include "Corn.h"
#include "Drone.h"
#include "Orb.h"
#include "Particles.h"
#include "Level.h"

Mode3::Mode3():ball_ptr(nullptr)
{ }

void Mode3::Load()
{
#ifdef _DEBUG
    AddGSComponent(new CS230::ShowCollision());
#endif
    //Engine::GetLogger().LogDebug("x: " + std::to_string(Engine::GetWindow().GetSize().x) + " y: " + std::to_string(Engine::GetWindow().GetSize().y));
    AddGSComponent(new CS230::DampingCamera({ {0,0}, { map_width,map_height } }, { {0.0, 0.2},{0.9,0.7} }, { camera_offset1X,camera_offset1Y }, dampingFactor));
    AddGSComponent(new Gravity(gravity));
    AddGSComponent(new CS230::GameObjectManager());
    AddGSComponent(new Background());
    
    AddGSComponent(new CS230::ParticleManager<Particles::Smoke>());

    Background* background = GetGSComponent<Background>();
    background->Add("Assets/Background1.png", 0.25);
    background->Add("Assets/Background2.png", 0.5);
    background->Add("Assets/Background3.png", 0.75);

    CS230::GameObjectManager* gameobjectmanager = GetGSComponent<CS230::GameObjectManager>();
    ball_ptr = new Ball({ 100, 200 });
    gameobjectmanager->Add(ball_ptr);
    gameobjectmanager->Add(new Platform({ 0, 0 }, 1400, Platforms::Platform1));
    gameobjectmanager->Add(new Platform({ 1200, 0 }, 1000, Platforms::Platform1));
    gameobjectmanager->Add(new Platform({ 2700, 0 }, 20000, Platforms::Platform1));
    gameobjectmanager->Add(new Platform({ 1500, 200 }, 10000, Platforms::Platform1));
    gameobjectmanager->Add(new Platform({ 1500, 200 }, 440, Platforms::Platform1));
    gameobjectmanager->Add(new Platform({ 1500, 200 }, 500, Platforms::Platform1));
    gameobjectmanager->Add(new Platform({ 1500, 400 }, 500, Platforms::Platform1));
    gameobjectmanager->Add(new Platform({ 1500, 600 }, 500, Platforms::Platform2));
    gameobjectmanager->Add(new Platform({ 1500, 600 }, 1000, Platforms::Platform2));
    gameobjectmanager->Add(new Platform({ 2700, 600 }, 800, Platforms::Platform2));
    gameobjectmanager->Add(new Platform({ 3900, 600 }, 600, Platforms::Platform2));
    gameobjectmanager->Add(new Platform({ 1500, 1000 }, 4000, Platforms::Platform2));
    gameobjectmanager->Add(new Pin({ 1000,60 }, ball_ptr));

    CS230::DampingCamera* camera = GetGSComponent<CS230::DampingCamera>();
    camera->SetPosition({ 0,0 });
}

void Mode3::Update(double dt)
{
    //Engine::GetLogger().LogDebug("mouseX: " + std::to_string(Engine::GetInput().GetMousePosition().x) + " mouseY: " + std::to_string(Engine::GetInput().GetMousePosition().y));
    UpdateGSComponents(dt);
    GetGSComponent<CS230::GameObjectManager>()->UpdateAll(dt);
    GetGSComponent<CS230::DampingCamera>()->Update(ball_ptr,dt);
    
    if (ball_ptr->GetGOComponent<Level>()->IsLevelUpdated()) {
        GetGSComponent<CS230::DampingCamera>()->SetTargetOffset(Math::vec2{ camera_offset1X-(camera_offsetX_level_diff * (ball_ptr->GetGOComponent<Level>()->GetLevel() - 1)) * (camera_offsetX_level_diff * (ball_ptr->GetGOComponent<Level>()->GetLevel() - 1)), camera_offset1Y});
    }

    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Escape)) {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Menu));
    }
}

void Mode3::Unload()
{
    GetGSComponent<Background>()->Unload();
    GetGSComponent<CS230::GameObjectManager>()->Unload();
    ClearGSComponents();
    ball_ptr = nullptr;
}

void Mode3::Draw()
{
    Engine::GetWindow().Clear(0x007F7FFF);

    Math::TransformationMatrix camera_matrix = GetGSComponent<CS230::DampingCamera>()->GetMatrix();

    GetGSComponent<Background>()->Draw(*GetGSComponent<CS230::DampingCamera>());
    GetGSComponent<CS230::GameObjectManager>()->DrawAll(camera_matrix);
}

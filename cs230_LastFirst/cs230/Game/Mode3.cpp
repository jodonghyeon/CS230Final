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

Mode3::Mode3():ball_ptr(nullptr)
{ }

void Mode3::Load()
{
#ifdef _DEBUG
    AddGSComponent(new CS230::ShowCollision());
#endif
    Engine::GetWindow().SetSize(window_width, window_height);
    AddGSComponent(new CS230::DampingCamera({ {0,0},{ map_width,map_height } }, dampingFactor));
    AddGSComponent(new Gravity(gravity));
    AddGSComponent(new CS230::GameObjectManager());
    /*AddGSComponent(new Background());
    AddGSComponent(new CS230::ParticleManager<Particles::Smoke>());


    Background* background = GetGSComponent<Background>();
    background->Add("Assets/Planets.png", 0.25);
    background->Add("Assets/Ships.png", 0.5);
    background->Add("Assets/Foreground.png", 1);*/

    CS230::GameObjectManager* gameobjectmanager = GetGSComponent<CS230::GameObjectManager>();
    ball_ptr = new Ball({ 100,stage1_floor });
    gameobjectmanager->Add(ball_ptr);
    gameobjectmanager->Add(new Platform({ 800, 200 }, 440, Platforms::Underground));
    gameobjectmanager->Add(new Platform({ 1500, 200 }, 20000, Platforms::Underground));

    CS230::DampingCamera* camera = GetGSComponent<CS230::DampingCamera>();
    camera->SetPosition({ 0,0 });
}

void Mode3::Update(double dt)
{
    UpdateGSComponents(dt);
    GetGSComponent<CS230::GameObjectManager>()->UpdateAll(dt);
    GetGSComponent<CS230::DampingCamera>()->Update(ball_ptr,dt);
}

void Mode3::Unload()
{
}

void Mode3::Draw()
{
    Engine::GetWindow().Clear(0x000000FF);

    Math::TransformationMatrix camera_matrix = GetGSComponent<CS230::DampingCamera>()->GetMatrix();

    //GetGSComponent<Background>()->Draw(*GetGSComponent<CS230::DampingCamera>());
    GetGSComponent<CS230::GameObjectManager>()->DrawAll(camera_matrix);
}

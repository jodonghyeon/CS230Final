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
#include "Cone.h"
#include "Drone.h"
#include "Orb.h"
#include "BigPin.h"
#include "Level.h"
#include "Cursor.h"
#include "StatusBar.h"
#include "Portal.h"
#include "Fonts.h"

Mode3::Mode3():ball_ptr(nullptr)
{ }

void Mode3::Load()
{
#ifdef _DEBUG
    AddGSComponent(new CS230::ShowCollision());
#endif
    //Engine::GetLogger().LogDebug("x: " + std::to_string(Engine::GetWindow().GetSize().x) + " y: " + std::to_string(Engine::GetWindow().GetSize().y));
    //Engine::GetAudio().game_music.Load("Assets/Mode3Music.mp3");
    timer = 0.0;

    tutorial_text = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Press Space to Dash!", 0xFFFFFFFF);

    bgm=Engine::GetGameAudioManager().LoadMusic("Assets/Mode3Music.mp3");
    bgm->Start();

    AddGSComponent(new CS230::DampingCamera({ {0,0}, { map_width-1000,map_height } }, { {0.0, 0.1},{0.9,0.7} }, { camera_offset1X,camera_offset1Y }, dampingFactor));

    CS230::DampingCamera* camera = GetGSComponent<CS230::DampingCamera>();
    camera->SetPosition({ 0,0 });

    AddGSComponent(new Gravity(gravity));
    AddGSComponent(new CS230::GameObjectManager());
    AddGSComponent(new Background());
    AddGSComponent(new CS230::ParticleManager<Particles::SmogeRed>());
    AddGSComponent(new CS230::ParticleManager<Particles::SmogeYellow>());
    AddGSComponent(new CS230::ParticleManager<Particles::SmogeGreen>());
    AddGSComponent(new CS230::ParticleManager<Particles::SmogeBlue>());
    AddGSComponent(new CS230::ParticleManager<Particles::SmogeGrey>());

    AddGSComponent(new CS230::ParticleManager<Particles::ParticleRed>());
    AddGSComponent(new CS230::ParticleManager<Particles::ParticleYellow>());
    AddGSComponent(new CS230::ParticleManager<Particles::ParticleGreen>());
    AddGSComponent(new CS230::ParticleManager<Particles::ParticleBlue>());
    AddGSComponent(new CS230::ParticleManager<Particles::ParticleGrey>());
    
    AddGSComponent(new CS230::ParticleManager<Particles::Smoke>());

    AddGSComponent(new Cursor());

    Cursor* cursor = GetGSComponent<Cursor>();
    cursor->Add("Assets/Cursor1.png");
    cursor->Add("Assets/Cursor2.png");

    Background* background = GetGSComponent<Background>();
    background->Add("Assets/Background1.png", 0.45);
    background->Add("Assets/Background2.png", 0.5);
    background->Add("Assets/Background3.png", 0.75);

    CS230::GameObjectManager* gameobjectmanager = GetGSComponent<CS230::GameObjectManager>();
    
    // stage 1
    gameobjectmanager->Add(new Platform({ -4 * Mode3::unit_block_side, 0 }, 40 * Mode3::unit_block_side, Platforms::Platform1));
    gameobjectmanager->Add(new Pin({ 16 * Mode3::unit_block_side, Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Dumbbell({ 27 * Mode3::unit_block_side, Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Platform({ 42 * Mode3::unit_block_side, 0 }, 20 * Mode3::unit_block_side, Platforms::Platform1));
    gameobjectmanager->Add(new Pin({ 53 * Mode3::unit_block_side, Mode3::unit_block_side }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 53 * Mode3::unit_block_side, 3 * Mode3::unit_block_side }, 28 * Mode3::unit_block_side, Platforms::Platform1));
    gameobjectmanager->Add(new Dumbbell({ 60 * Mode3::unit_block_side, 4 * Mode3::unit_block_side }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 70 * Mode3::unit_block_side, 0 }, 25 * Mode3::unit_block_side, Platforms::Platform1));

    gameobjectmanager->Add(new Platform({ 75 * Mode3::unit_block_side, 6 * Mode3::unit_block_side }, 10 * Mode3::unit_block_side, Platforms::Platform1));
    gameobjectmanager->Add(new Dumbbell({ 80 * Mode3::unit_block_side, Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Platform({ 87 * Mode3::unit_block_side, 6 * Mode3::unit_block_side }, 8 * Mode3::unit_block_side, Platforms::Platform1));

    gameobjectmanager->Add(new Platform({ 106 * Mode3::unit_block_side, 0 }, 41 * Mode3::unit_block_side, Platforms::Platform1));
    gameobjectmanager->Add(new Pin({ 112 * Mode3::unit_block_side, Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Platform({ 126 * Mode3::unit_block_side, 4 * Mode3::unit_block_side }, 20 * Mode3::unit_block_side, Platforms::Platform1));
    gameobjectmanager->Add(new Dumbbell({ 136 * Mode3::unit_block_side, 5 * Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Pin({ 136 * Mode3::unit_block_side, 7 * Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Platform({ 150 * Mode3::unit_block_side, 0 }, 15 * Mode3::unit_block_side, Platforms::Platform1));
    gameobjectmanager->Add(new Platform({ 151 * Mode3::unit_block_side, 4 * Mode3::unit_block_side }, 13 * Mode3::unit_block_side, Platforms::Platform1));
    gameobjectmanager->Add(new Pin({ 154 * Mode3::unit_block_side, Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Dumbbell({ 154 * Mode3::unit_block_side, 5 * Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Platform({ 168 * Mode3::unit_block_side, 0 }, 50 * Mode3::unit_block_side, Platforms::Platform1));
    gameobjectmanager->Add(new Platform({ 169 * Mode3::unit_block_side, 4 * Mode3::unit_block_side }, 13 * Mode3::unit_block_side, Platforms::Platform1));
    gameobjectmanager->Add(new Dumbbell({ 174 * Mode3::unit_block_side, Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Pin({ 174 * Mode3::unit_block_side, 5 * Mode3::unit_block_side }, ball_ptr));

    // stage 2

    gameobjectmanager->Add(new Platform({ 0,  Mode3::stage_height }, 15 * Mode3::unit_block_side, Platforms::Platform2));

    gameobjectmanager->Add(new Platform({ 15 * Mode3::unit_block_side, 3 * Mode3::unit_block_side + Mode3::stage_height }, 7 * Mode3::unit_block_side, Platforms::Platform2));
    gameobjectmanager->Add(new Pin({ 20 * Mode3::unit_block_side, 4 * Mode3::unit_block_side + Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 22 * Mode3::unit_block_side, Mode3::stage_height }, 16 * Mode3::unit_block_side, Platforms::Platform2));
    gameobjectmanager->Add(new Dumbbell({ 23 * Mode3::unit_block_side, 1 * Mode3::unit_block_side + Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 38 * Mode3::unit_block_side, 3 * Mode3::unit_block_side + Mode3::stage_height }, 9 * Mode3::unit_block_side, Platforms::Platform2));
    gameobjectmanager->Add(new Pin({ 45 * Mode3::unit_block_side, 4 * Mode3::unit_block_side + Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 45 * Mode3::unit_block_side, 6 * Mode3::unit_block_side + Mode3::stage_height }, 14 * Mode3::unit_block_side, Platforms::Platform2));
    gameobjectmanager->Add(new Dumbbell({ 57 * Mode3::unit_block_side, 7 * Mode3::unit_block_side + Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 42 * Mode3::unit_block_side, Mode3::stage_height }, 22 * Mode3::unit_block_side, Platforms::Platform2));
    gameobjectmanager->Add(new Cone({ 49 * Mode3::unit_block_side, 1 * Mode3::unit_block_side + Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 66 * Mode3::unit_block_side, 3 * Mode3::unit_block_side + Mode3::stage_height }, 15 * Mode3::unit_block_side, Platforms::Platform2));
    gameobjectmanager->Add(new Dumbbell({ 73 * Mode3::unit_block_side, 4 * Mode3::unit_block_side + Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 84 * Mode3::unit_block_side, 1 * Mode3::unit_block_side + Mode3::stage_height }, 6 * Mode3::unit_block_side, Platforms::Platform2));

    gameobjectmanager->Add(new Pin({ 101 * Mode3::unit_block_side, 1 * Mode3::unit_block_side + Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 96 * Mode3::unit_block_side, 4 * Mode3::unit_block_side + Mode3::stage_height }, 12 * Mode3::unit_block_side, Platforms::Platform2));
    gameobjectmanager->Add(new Cone({ 105 * Mode3::unit_block_side, 5 * Mode3::unit_block_side + Mode3::stage_height }, ball_ptr));
    gameobjectmanager->Add(new Dumbbell({ 105 * Mode3::unit_block_side, 7 * Mode3::unit_block_side + Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 110 * Mode3::unit_block_side, Mode3::stage_height }, 15 * Mode3::unit_block_side, Platforms::Platform2));

    gameobjectmanager->Add(new Platform({ 124 * Mode3::unit_block_side, 4 * Mode3::unit_block_side + Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform2));
    gameobjectmanager->Add(new Dumbbell({ 130 * Mode3::unit_block_side, 5 * Mode3::unit_block_side + Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 135 * Mode3::unit_block_side, 2 * Mode3::unit_block_side + Mode3::stage_height }, 12 * Mode3::unit_block_side, Platforms::Platform2));

    gameobjectmanager->Add(new Platform({ 147 * Mode3::unit_block_side, 4 * Mode3::unit_block_side + Mode3::stage_height }, 8 * Mode3::unit_block_side, Platforms::Platform2));
    
    gameobjectmanager->Add(new Platform({ 151 * Mode3::unit_block_side, + Mode3::stage_height }, 8 * Mode3::unit_block_side, Platforms::Platform2));
    
    gameobjectmanager->Add(new Platform({ 159 * Mode3::unit_block_side, 6 * Mode3::unit_block_side + Mode3::stage_height }, 7 * Mode3::unit_block_side, Platforms::Platform2));

    gameobjectmanager->Add(new Platform({ 163 * Mode3::unit_block_side, 2 * Mode3::unit_block_side + Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform2));
    gameobjectmanager->Add(new Dumbbell({ 166 * Mode3::unit_block_side, 3 * Mode3::unit_block_side + Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 170 * Mode3::unit_block_side, 6 * Mode3::unit_block_side + Mode3::stage_height }, 11 * Mode3::unit_block_side, Platforms::Platform2));
    gameobjectmanager->Add(new Dumbbell({ 180 * Mode3::unit_block_side, 7 * Mode3::unit_block_side + Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 180 * Mode3::unit_block_side, 2* Mode3::unit_block_side + Mode3::stage_height }, 38 * Mode3::unit_block_side, Platforms::Platform2));
    gameobjectmanager->Add(new Dumbbell({ 186 * Mode3::unit_block_side, 3 * Mode3::unit_block_side + Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 92 * Mode3::unit_block_side,  Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform2)); // 이 플랫폼은 stage 1 과 이어지는 플랫폼이므로, 염두해두고 레벨 디자인 하기.


    // stage 3

    gameobjectmanager->Add(new Platform({ 0, 2 * Mode3::stage_height }, 25 * Mode3::unit_block_side, Platforms::Platform3));
    gameobjectmanager->Add(new Cone({ 20 * Mode3::unit_block_side, 1 * Mode3::unit_block_side + 2 * Mode3::stage_height }, ball_ptr));


    gameobjectmanager->Add(new Platform({ 25 * Mode3::unit_block_side, 5 * Mode3::unit_block_side + 2 * Mode3::stage_height }, 20 * Mode3::unit_block_side, Platforms::Platform3));
    gameobjectmanager->Add(new Cone({ 34 * Mode3::unit_block_side, 6 * Mode3::unit_block_side + 2 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 29 * Mode3::unit_block_side, 2 * Mode3::stage_height }, 18 * Mode3::unit_block_side, Platforms::Platform3));

    gameobjectmanager->Add(new Platform({ 56 * Mode3::unit_block_side, 4 * Mode3::unit_block_side + 2 * Mode3::stage_height }, 16 * Mode3::unit_block_side, Platforms::Platform3));
    gameobjectmanager->Add(new Cone({ 63 * Mode3::unit_block_side, 5 * Mode3::unit_block_side + 2 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 67 * Mode3::unit_block_side, 7 * Mode3::unit_block_side + 2 * Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform3));
    gameobjectmanager->Add(new Dumbbell({ 73 * Mode3::unit_block_side, 8 * Mode3::unit_block_side + 2 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 75 * Mode3::unit_block_side,  3 * Mode3::unit_block_side + 2 * Mode3::stage_height }, 9 * Mode3::unit_block_side, Platforms::Platform3));

    gameobjectmanager->Add(new Platform({ 89 * Mode3::unit_block_side,  5 * Mode3::unit_block_side + 2 * Mode3::stage_height }, 7 * Mode3::unit_block_side, Platforms::Platform3));

    gameobjectmanager->Add(new Platform({ 86 * Mode3::unit_block_side,  2 * Mode3::stage_height }, 7 * Mode3::unit_block_side, Platforms::Platform3));

    gameobjectmanager->Add(new Platform({ 98 * Mode3::unit_block_side, 6 * Mode3::unit_block_side + 2 * Mode3::stage_height }, 7 * Mode3::unit_block_side, Platforms::Platform3));

    gameobjectmanager->Add(new Platform({ 100 * Mode3::unit_block_side,  2 * Mode3::stage_height }, 16 * Mode3::unit_block_side, Platforms::Platform3));
    gameobjectmanager->Add(new Cone({ 105 * Mode3::unit_block_side,  Mode3::unit_block_side + 2 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 110 * Mode3::unit_block_side, 6 * Mode3::unit_block_side + 2 * Mode3::stage_height }, 12 * Mode3::unit_block_side, Platforms::Platform3));
    gameobjectmanager->Add(new Drone({ 115 * Mode3::unit_block_side, 7 * Mode3::unit_block_side + 2 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 127 * Mode3::unit_block_side, 8 * Mode3::unit_block_side + 2 * Mode3::stage_height }, 7 * Mode3::unit_block_side, Platforms::Platform3));

    gameobjectmanager->Add(new Platform({ 127 * Mode3::unit_block_side,  2 * Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform3));
    gameobjectmanager->Add(new Cone({ 130 * Mode3::unit_block_side,  Mode3::unit_block_side + 2 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 140 * Mode3::unit_block_side, 4 * Mode3::unit_block_side + 2 * Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform3));
    gameobjectmanager->Add(new Pin({ 145 * Mode3::unit_block_side, 5 * Mode3::unit_block_side + 2 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 155 * Mode3::unit_block_side, 6 * Mode3::unit_block_side + 2 * Mode3::stage_height }, 7 * Mode3::unit_block_side, Platforms::Platform3));

    gameobjectmanager->Add(new Platform({ 153 * Mode3::unit_block_side,  2 * Mode3::stage_height }, 7 * Mode3::unit_block_side, Platforms::Platform3));

    gameobjectmanager->Add(new Platform({ 163 * Mode3::unit_block_side,  3 * Mode3::unit_block_side + 2 * Mode3::stage_height }, 5 * Mode3::unit_block_side, Platforms::Platform3));
    gameobjectmanager->Add(new Cone({ 166 * Mode3::unit_block_side, 4 * Mode3::unit_block_side + 2 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 170 * Mode3::unit_block_side,   Mode3::unit_block_side + 2 * Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform3));

    gameobjectmanager->Add(new Platform({ 180 * Mode3::unit_block_side, 4 * Mode3::unit_block_side + 2 * Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform3));
    gameobjectmanager->Add(new Dumbbell({ 185 * Mode3::unit_block_side, 5 * Mode3::unit_block_side + 2 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 190 * Mode3::unit_block_side,  2 * Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform3));

    gameobjectmanager->Add(new Platform({ 53 * Mode3::unit_block_side,  2 * Mode3::stage_height }, 22 * Mode3::unit_block_side, Platforms::Platform3));



    // stage 4

    gameobjectmanager->Add(new Platform({ 0, 3 * Mode3::stage_height }, 20 * Mode3::unit_block_side, Platforms::Platform4));
    gameobjectmanager->Add(new Cone({ 19 * Mode3::unit_block_side, 1 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 20 * Mode3::unit_block_side, 4 * Mode3::unit_block_side + 3 * Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform4));
    gameobjectmanager->Add(new Drone({ 26 * Mode3::unit_block_side, 5 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));


    gameobjectmanager->Add(new Platform({ 36 * Mode3::unit_block_side, 6 * Mode3::unit_block_side + 3 * Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform4));


    gameobjectmanager->Add(new Platform({ 46 * Mode3::unit_block_side, 5 * Mode3::unit_block_side + 3 * Mode3::stage_height }, 8 * Mode3::unit_block_side, Platforms::Platform4));
    gameobjectmanager->Add(new Drone({ 50 * Mode3::unit_block_side, 7 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));


    gameobjectmanager->Add(new Platform({ 25 * Mode3::unit_block_side,  Mode3::unit_block_side + 3 * Mode3::stage_height }, 15 * Mode3::unit_block_side, Platforms::Platform4));
    gameobjectmanager->Add(new Pin({ 32 * Mode3::unit_block_side, 2 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 42 * Mode3::unit_block_side, 3 * Mode3::stage_height }, 12 * Mode3::unit_block_side, Platforms::Platform4));
    gameobjectmanager->Add(new Cone({ 50 * Mode3::unit_block_side,  Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));


    gameobjectmanager->Add(new Platform({ 58 * Mode3::unit_block_side, 2 * Mode3::unit_block_side + 3 * Mode3::stage_height }, 14 * Mode3::unit_block_side, Platforms::Platform4));
    gameobjectmanager->Add(new Drone({ 70 * Mode3::unit_block_side, 4 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 76 * Mode3::unit_block_side, 3 * Mode3::stage_height }, 15 * Mode3::unit_block_side, Platforms::Platform4));

    gameobjectmanager->Add(new Platform({ 94 * Mode3::unit_block_side, 6 * Mode3::unit_block_side + 3 * Mode3::stage_height }, 12 * Mode3::unit_block_side, Platforms::Platform4));
    gameobjectmanager->Add(new Drone({ 100 * Mode3::unit_block_side, 7 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 97 * Mode3::unit_block_side, 3 * Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform4));
    gameobjectmanager->Add(new Cone({ 100 * Mode3::unit_block_side,  Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 115 * Mode3::unit_block_side, 5 * Mode3::unit_block_side + 3 * Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform4));

    gameobjectmanager->Add(new Platform({ 112 * Mode3::unit_block_side, 3 * Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform4));
    gameobjectmanager->Add(new Orb({ 117 * Mode3::unit_block_side, 3 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 130 * Mode3::unit_block_side,  4 * Mode3::unit_block_side + 3 * Mode3::stage_height }, 6 * Mode3::unit_block_side, Platforms::Platform4));

    gameobjectmanager->Add(new Platform({ 138 * Mode3::unit_block_side, 3 * Mode3::stage_height }, 9 * Mode3::unit_block_side, Platforms::Platform4));


    gameobjectmanager->Add(new Platform({ 147 * Mode3::unit_block_side, 3 * Mode3::unit_block_side + 3 * Mode3::stage_height }, 15 * Mode3::unit_block_side, Platforms::Platform4));
    gameobjectmanager->Add(new Drone({ 160 * Mode3::unit_block_side, 5 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 168 * Mode3::unit_block_side, 2 * Mode3::unit_block_side + 3 * Mode3::stage_height }, 18 * Mode3::unit_block_side, Platforms::Platform4));
    gameobjectmanager->Add(new Drone({ 175 * Mode3::unit_block_side, 3 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));
    gameobjectmanager->Add(new Orb({ 185 * Mode3::unit_block_side, 4 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 180 * Mode3::unit_block_side, 7 * Mode3::unit_block_side + 3 * Mode3::stage_height }, 18 * Mode3::unit_block_side, Platforms::Platform4));
    gameobjectmanager->Add(new Dumbbell({ 185 * Mode3::unit_block_side, 8 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 190 * Mode3::unit_block_side, 3 * Mode3::stage_height }, 18 * Mode3::unit_block_side, Platforms::Platform4));

    // stage 5
    gameobjectmanager->Add(new Platform({ 0, 4 * Mode3::stage_height }, 20 * Mode3::unit_block_side, Platforms::Platform5));

    gameobjectmanager->Add(new Platform({ 23 * Mode3::unit_block_side, 6 * Mode3::unit_block_side + 4 * Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform5));
    gameobjectmanager->Add(new Drone({ 31 * Mode3::unit_block_side, 7 * Mode3::unit_block_side + 4 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 22 * Mode3::unit_block_side, 2 * Mode3::unit_block_side + 4 * Mode3::stage_height }, 9 * Mode3::unit_block_side, Platforms::Platform5));
    gameobjectmanager->Add(new Orb({ 30 * Mode3::unit_block_side, 3 * Mode3::unit_block_side + 4 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 33 * Mode3::unit_block_side, 4 * Mode3::stage_height }, 8 * Mode3::unit_block_side, Platforms::Platform5));

    gameobjectmanager->Add(new Platform({ 39 * Mode3::unit_block_side, 6 * Mode3::unit_block_side + 4 * Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform5));
    gameobjectmanager->Add(new Drone({ 45 * Mode3::unit_block_side, 7 * Mode3::unit_block_side + 4 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 51 * Mode3::unit_block_side, 5 * Mode3::unit_block_side + 4 * Mode3::stage_height }, 8 * Mode3::unit_block_side, Platforms::Platform5));

    gameobjectmanager->Add(new Platform({ 47 * Mode3::unit_block_side, Mode3::unit_block_side + 4 * Mode3::stage_height }, 12 * Mode3::unit_block_side, Platforms::Platform5));

    gameobjectmanager->Add(new Platform({ 65 * Mode3::unit_block_side, 2 * Mode3::unit_block_side + 4 * Mode3::stage_height }, 14 * Mode3::unit_block_side, Platforms::Platform5));
    gameobjectmanager->Add(new Drone({ 75 * Mode3::unit_block_side, 4 * Mode3::unit_block_side + 4 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 83 * Mode3::unit_block_side, 6 * Mode3::unit_block_side + 4 * Mode3::stage_height }, 12 * Mode3::unit_block_side, Platforms::Platform5));

    gameobjectmanager->Add(new Platform({ 87 * Mode3::unit_block_side, 1 * Mode3::unit_block_side + 4 * Mode3::stage_height }, 12 * Mode3::unit_block_side, Platforms::Platform5));
    gameobjectmanager->Add(new Orb({ 90 * Mode3::unit_block_side, 2 * Mode3::unit_block_side + 4 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 100 * Mode3::unit_block_side, 4 * Mode3::unit_block_side + 4 * Mode3::stage_height }, 12 * Mode3::unit_block_side, Platforms::Platform5));

    gameobjectmanager->Add(new Platform({ 115 * Mode3::unit_block_side, 2 * Mode3::unit_block_side + 4 * Mode3::stage_height }, 14 * Mode3::unit_block_side, Platforms::Platform5));
    gameobjectmanager->Add(new Orb({ 123 * Mode3::unit_block_side, 3 * Mode3::unit_block_side + 4 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 133 * Mode3::unit_block_side, 6 * Mode3::unit_block_side + 4 * Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform5));

    gameobjectmanager->Add(new Platform({ 132 * Mode3::unit_block_side, 1 * Mode3::unit_block_side + 4 * Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform5));
    gameobjectmanager->Add(new Orb({ 137 * Mode3::unit_block_side, 2 * Mode3::unit_block_side + 4 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 145 * Mode3::unit_block_side, 3 * Mode3::unit_block_side + 4 * Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform5));

    gameobjectmanager->Add(new Platform({ 160 * Mode3::unit_block_side, 5 * Mode3::unit_block_side + 4 * Mode3::stage_height }, 12 * Mode3::unit_block_side, Platforms::Platform5));
    gameobjectmanager->Add(new Drone({ 170 * Mode3::unit_block_side, 6 * Mode3::unit_block_side + 4 * Mode3::stage_height }, ball_ptr));


    gameobjectmanager->Add(new Platform({ 162 * Mode3::unit_block_side, 1 * Mode3::unit_block_side + 4 * Mode3::stage_height }, 12 * Mode3::unit_block_side, Platforms::Platform5));
    gameobjectmanager->Add(new Orb({ 165 * Mode3::unit_block_side, 2 * Mode3::unit_block_side + 4 * Mode3::stage_height }, ball_ptr));


    gameobjectmanager->Add(new Platform({ 175 * Mode3::unit_block_side,  4 * Mode3::stage_height }, 30 * Mode3::unit_block_side, Platforms::Platform5));
    gameobjectmanager->Add(new Orb({ 178 * Mode3::unit_block_side, 1 * Mode3::unit_block_side + 4 * Mode3::stage_height }, ball_ptr));

    Math::irect portal1 = { {Mode3::map_width - 1000, Mode3::unit_block_side}, {Mode3::map_width + 120, Mode3::stage_height} };
    Math::irect portal2 = { {Mode3::map_width - 1000, Mode3::stage_height + Mode3::unit_block_side}, {Mode3::map_width + 120, 2 * Mode3::stage_height} };
    Math::irect portal3 = { {Mode3::map_width - 1000, 2 * Mode3::stage_height + Mode3::unit_block_side}, {Mode3::map_width + 120, 3 * Mode3::stage_height} };
    Math::irect portal4 = { {Mode3::map_width - 1000, 3 * Mode3::stage_height + Mode3::unit_block_side}, {Mode3::map_width + 120, 4 * Mode3::stage_height} };
    gameobjectmanager->Add(new Portal(4, portal1));
    gameobjectmanager->Add(new Portal(4, portal2));
    gameobjectmanager->Add(new Portal(4, portal3));
    gameobjectmanager->Add(new Portal(4, portal4));

    big_pin_ptr = new BigPin({ Mode3::map_width-1500,4 * Mode3::stage_height + Mode3::unit_block_side }, ball_ptr);
    
    gameobjectmanager->Add(big_pin_ptr);

    // player ball start position and level
    ball_ptr = new Ball({0, 6 * Mode3::unit_block_side}, 1);

    gameobjectmanager->Add(ball_ptr);
}

void Mode3::Update(double dt)
{
    //Engine::GetLogger().LogDebug("mouseX: " + std::to_string(Engine::GetInput().GetMousePosition().x) + " mouseY: " + std::to_string(Engine::GetInput().GetMousePosition().y));
    //Engine::GetLogger().LogDebug(std::to_string(ball_ptr->GetPosition().x) + " " + std::to_string(ball_ptr->GetPosition().y));
    //Engine::GetLogger().LogDebug(ball_ptr->current_state->GetName());
    //Engine::GetLogger().LogDebug(std::to_string(ball_ptr->GetGOComponent<Level>()->GetLevel())+" "+std::to_string(ball_ptr->GetGOComponent<Level>()->GetEXP()) + " " + std::to_string(ball_ptr->GetGOComponent<Level>()->GetEXPMax()));
    
    timer += dt;
    
    UpdateGSComponents(dt);
    GetGSComponent<CS230::GameObjectManager>()->UpdateAll(dt);

    GetGSComponent<CS230::DampingCamera>()->Update(ball_ptr,dt);
    
    GetGSComponent<CS230::DampingCamera>()->SetTargetOffset(Math::vec2{ camera_offset1X-(camera_offsetX_level_diff * (ball_ptr->GetGOComponent<Level>()->GetLevel() - 1)) * (camera_offsetX_level_diff * (ball_ptr->GetGOComponent<Level>()->GetLevel() - 1)), camera_offset1Y});

    if (ball_ptr->GetPosition().x - GetGSComponent<CS230::DampingCamera>()->GetPosition().x > Engine::GetInput().GetMousePosition().x) {
        GetGSComponent<Cursor>()->SetType(1);
    }
    else {
        GetGSComponent<Cursor>()->SetType(0);
    }


    if (!big_pin_ptr->IsAlive()) {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Ending));
    }

    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Escape)) {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Menu));
    }
}

void Mode3::Unload()
{
    bgm->Stop();
    GetGSComponent<Background>()->Unload();
    GetGSComponent<CS230::GameObjectManager>()->Unload();
    ClearGSComponents();
    ball_ptr = nullptr;
}

void Mode3::Draw()
{
    Engine::GetWindow().Clear(0x00000000);

    Math::TransformationMatrix camera_matrix = GetGSComponent<CS230::DampingCamera>()->GetMatrix();

    GetGSComponent<Background>()->Draw(*GetGSComponent<CS230::DampingCamera>());
    GetGSComponent<CS230::GameObjectManager>()->DrawAll(camera_matrix);
    GetGSComponent<Cursor>()->Draw();
    if (timer <= tutorial_time) {
        tutorial_text->Draw(Math::TranslationMatrix(Math::vec2{ (double)(Engine::GetWindow().GetSize().x) / 10, (double)(Engine::GetWindow().GetSize().y / 5) }));
    }
}

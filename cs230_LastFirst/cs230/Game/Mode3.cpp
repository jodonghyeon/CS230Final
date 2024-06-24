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
    game_ending_text = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Thanks for Playing!", 0xFFFFFFFF);

    bgm=Engine::GetGameAudioManager().LoadMusic("Assets/Mode3Music.mp3");
    bgm->Start();

    ending_sound = Engine::GetGameAudioManager().LoadSound("Assets/GameEndingSound.mp3");

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


    // 알아보기 쉽도록, 같은 층이라면 x좌표 작은 오브젝트부터 순서대로 Add하기!!(x좌표 같으면 아래있는 오브젝트부터)
    // position 좌표 입력 시, Mode3::unit_block_side(한 블록 길이)와 Mode3::stage_height(한 스테이지 높이) 단위 상수 꼭 사용하기!
    // 직접 플레이 해보면서 추가하기
    
    // stage 1
    gameobjectmanager->Add(new Platform({ -4 * Mode3::unit_block_side, 0 }, 40 * Mode3::unit_block_side, Platforms::Platform1));
    gameobjectmanager->Add(new Pin({ 16 * Mode3::unit_block_side, Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Dumbbell({ 27 * Mode3::unit_block_side, Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Platform({ 42 * Mode3::unit_block_side, 0 }, 20 * Mode3::unit_block_side, Platforms::Platform1));
    gameobjectmanager->Add(new Pin({ 53 * Mode3::unit_block_side, Mode3::unit_block_side }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 53 * Mode3::unit_block_side, 3 * Mode3::unit_block_side }, 28 * Mode3::unit_block_side, Platforms::Platform1));
    gameobjectmanager->Add(new Dumbbell({ 60 * Mode3::unit_block_side, 4 * Mode3::unit_block_side }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 70 * Mode3::unit_block_side, 0 }, 25 * Mode3::unit_block_side, Platforms::Platform1));

    gameobjectmanager->Add(new Platform({ 79 * Mode3::unit_block_side, 6 * Mode3::unit_block_side }, 10 * Mode3::unit_block_side, Platforms::Platform1));
    gameobjectmanager->Add(new Dumbbell({ 80 * Mode3::unit_block_side, Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Platform({ 95 * Mode3::unit_block_side, 6 * Mode3::unit_block_side }, 8 * Mode3::unit_block_side, Platforms::Platform1));

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
    // TODO

    gameobjectmanager->Add(new Platform({ 0,  Mode3::stage_height }, 15 * Mode3::unit_block_side, Platforms::Platform2));
    gameobjectmanager->Add(new Pin({ 10 * Mode3::unit_block_side, Mode3::unit_block_side + Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 15 * Mode3::unit_block_side, 4 * Mode3::unit_block_side + Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform2));
    gameobjectmanager->Add(new Dumbbell({ 20 * Mode3::unit_block_side, 5 * Mode3::unit_block_side + Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 15 * Mode3::unit_block_side, -2 * Mode3::unit_block_side + Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform1));
    gameobjectmanager->Add(new Dumbbell({ 20 * Mode3::unit_block_side, -1 * Mode3::unit_block_side + Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 25 * Mode3::unit_block_side, 1 * Mode3::unit_block_side + Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform2));
    gameobjectmanager->Add(new Dumbbell({ 30 * Mode3::unit_block_side, 2 * Mode3::unit_block_side + Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 35 * Mode3::unit_block_side, 4 * Mode3::unit_block_side + Mode3::stage_height }, 8 * Mode3::unit_block_side, Platforms::Platform2));

    gameobjectmanager->Add(new Platform({ 43 * Mode3::unit_block_side, 7 * Mode3::unit_block_side + Mode3::stage_height }, 8 * Mode3::unit_block_side, Platforms::Platform2));
    gameobjectmanager->Add(new Pin({ 46 * Mode3::unit_block_side, 8* Mode3::unit_block_side + Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 45 * Mode3::unit_block_side,  1 * Mode3::unit_block_side + Mode3::stage_height }, 8 * Mode3::unit_block_side, Platforms::Platform2));
    gameobjectmanager->Add(new Dumbbell({ 47 * Mode3::unit_block_side, 2 * Mode3::unit_block_side + Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 54 * Mode3::unit_block_side, 2 * Mode3::unit_block_side + Mode3::stage_height }, 7 * Mode3::unit_block_side, Platforms::Platform2));
    gameobjectmanager->Add(new Cone({ 57 * Mode3::unit_block_side, 3 * Mode3::unit_block_side + Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 63 * Mode3::unit_block_side, 4 * Mode3::unit_block_side + Mode3::stage_height }, 15 * Mode3::unit_block_side, Platforms::Platform2));
    gameobjectmanager->Add(new Dumbbell({ 70 * Mode3::unit_block_side, 5 * Mode3::unit_block_side + Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 78 * Mode3::unit_block_side, 2 * Mode3::unit_block_side + Mode3::stage_height }, 8 * Mode3::unit_block_side, Platforms::Platform2));

    gameobjectmanager->Add(new Platform({ 98 * Mode3::unit_block_side, 5 * Mode3::unit_block_side + Mode3::stage_height }, 12 * Mode3::unit_block_side, Platforms::Platform2));
    gameobjectmanager->Add(new Cone({ 105 * Mode3::unit_block_side, 6 * Mode3::unit_block_side + Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 110 * Mode3::unit_block_side, Mode3::unit_block_side + Mode3::stage_height }, 15 * Mode3::unit_block_side, Platforms::Platform2));
    gameobjectmanager->Add(new Pin({ 115 * Mode3::unit_block_side, 2 * Mode3::unit_block_side + Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 120 * Mode3::unit_block_side, 5 * Mode3::unit_block_side + Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform2));
    gameobjectmanager->Add(new Dumbbell({ 125 * Mode3::unit_block_side, 6 * Mode3::unit_block_side + Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 135 * Mode3::unit_block_side, 3 * Mode3::unit_block_side + Mode3::stage_height }, 8 * Mode3::unit_block_side, Platforms::Platform2));

    gameobjectmanager->Add(new Platform({ 147 * Mode3::unit_block_side, 5 * Mode3::unit_block_side + Mode3::stage_height }, 8 * Mode3::unit_block_side, Platforms::Platform2));
    gameobjectmanager->Add(new Dumbbell({ 149 * Mode3::unit_block_side, 6 * Mode3::unit_block_side + Mode3::stage_height }, ball_ptr));
    
    gameobjectmanager->Add(new Platform({ 151 * Mode3::unit_block_side, Mode3::unit_block_side + Mode3::stage_height }, 8 * Mode3::unit_block_side, Platforms::Platform2));
    gameobjectmanager->Add(new Cone({ 155 * Mode3::unit_block_side, 2 * Mode3::unit_block_side + Mode3::stage_height }, ball_ptr));
    
    gameobjectmanager->Add(new Platform({ 159 * Mode3::unit_block_side, 7 * Mode3::unit_block_side + Mode3::stage_height }, 7 * Mode3::unit_block_side, Platforms::Platform2));
    gameobjectmanager->Add(new Pin({ 164 * Mode3::unit_block_side, 8 * Mode3::unit_block_side + Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 163 * Mode3::unit_block_side, 3 * Mode3::unit_block_side + Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform2));
    gameobjectmanager->Add(new Dumbbell({ 166 * Mode3::unit_block_side, 4 * Mode3::unit_block_side + Mode3::stage_height }, ball_ptr));


    gameobjectmanager->Add(new Platform({ 175 * Mode3::unit_block_side, 7 * Mode3::unit_block_side + Mode3::stage_height }, 7 * Mode3::unit_block_side, Platforms::Platform2));
    gameobjectmanager->Add(new Dumbbell({ 178 * Mode3::unit_block_side, 8 * Mode3::unit_block_side + Mode3::stage_height }, ball_ptr));


    gameobjectmanager->Add(new Dumbbell({ 185 * Mode3::unit_block_side, 4 * Mode3::unit_block_side + Mode3::stage_height }, ball_ptr));
    gameobjectmanager->Add(new Platform({ 182 * Mode3::unit_block_side, 3* Mode3::unit_block_side + Mode3::stage_height }, 16 * Mode3::unit_block_side, Platforms::Platform2));

    gameobjectmanager->Add(new Platform({ 92 * Mode3::unit_block_side,  Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform2)); // 이 플랫폼은 stage 1 과 이어지는 플랫폼이므로, 염두해두고 레벨 디자인 하기.


    // stage 3
   // Redesigned Complex Stage 2 with Numerous Short Platforms

    gameobjectmanager->Add(new Platform({ 0, 2 * Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform3));
    gameobjectmanager->Add(new Cone({ 3 * Mode3::unit_block_side, 1 * Mode3::unit_block_side + 2 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 10 * Mode3::unit_block_side, 3* Mode3::unit_block_side + 2 * Mode3::stage_height }, 8 * Mode3::unit_block_side, Platforms::Platform3));
    gameobjectmanager->Add(new Pin({ 15 * Mode3::unit_block_side, 4 * Mode3::unit_block_side + 2 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 18 * Mode3::unit_block_side,  2 * Mode3::stage_height }, 7 * Mode3::unit_block_side, Platforms::Platform3));
    gameobjectmanager->Add(new Dumbbell({ 20 * Mode3::unit_block_side, 1 * Mode3::unit_block_side + 2 * Mode3::stage_height }, ball_ptr));


    gameobjectmanager->Add(new Platform({ 25 * Mode3::unit_block_side, 5 * Mode3::unit_block_side + 2 * Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform3));
    gameobjectmanager->Add(new Cone({ 28 * Mode3::unit_block_side, 6 * Mode3::unit_block_side + 2 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 29 * Mode3::unit_block_side, 2 * Mode3::stage_height }, 12 * Mode3::unit_block_side, Platforms::Platform3));


    gameobjectmanager->Add(new Drone({ 37 * Mode3::unit_block_side,  Mode3::unit_block_side + 2 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 40 * Mode3::unit_block_side, 6 * Mode3::unit_block_side + 2 * Mode3::stage_height }, 8 * Mode3::unit_block_side, Platforms::Platform3));
    gameobjectmanager->Add(new Pin({ 45 * Mode3::unit_block_side, 7 * Mode3::unit_block_side + 2 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 54 * Mode3::unit_block_side, 7 * Mode3::unit_block_side + 2 * Mode3::stage_height }, 4 * Mode3::unit_block_side, Platforms::Platform3));

    gameobjectmanager->Add(new Platform({ 50 * Mode3::unit_block_side,  2 * Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform3));
    gameobjectmanager->Add(new Cone({ 55 * Mode3::unit_block_side, Mode3::unit_block_side + 2 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 60 * Mode3::unit_block_side, 4 * Mode3::unit_block_side + 2 * Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform3));
    gameobjectmanager->Add(new Drone({ 65 * Mode3::unit_block_side, 5 * Mode3::unit_block_side + 2 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 70 * Mode3::unit_block_side, 7 * Mode3::unit_block_side + 2 * Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform3));
    gameobjectmanager->Add(new Dumbbell({ 75 * Mode3::unit_block_side, 8 * Mode3::unit_block_side + 2 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 80 * Mode3::unit_block_side,  2 * Mode3::unit_block_side + 2 * Mode3::stage_height }, 7 * Mode3::unit_block_side, Platforms::Platform3));
    gameobjectmanager->Add(new Pin({ 84 * Mode3::unit_block_side, 3 * Mode3::unit_block_side + 2 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 89 * Mode3::unit_block_side,  5 * Mode3::unit_block_side + 2 * Mode3::stage_height }, 7 * Mode3::unit_block_side, Platforms::Platform3));

    gameobjectmanager->Add(new Platform({ 89 * Mode3::unit_block_side,  2 * Mode3::stage_height }, 7 * Mode3::unit_block_side, Platforms::Platform3));
    gameobjectmanager->Add(new Dumbbell({ 93 * Mode3::unit_block_side, 3 * Mode3::unit_block_side + 2 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 98 * Mode3::unit_block_side, 6 *Mode3::unit_block_side + 2 * Mode3::stage_height }, 7 * Mode3::unit_block_side, Platforms::Platform3));
    gameobjectmanager->Add(new Pin({ 102 * Mode3::unit_block_side, 7 * Mode3::unit_block_side + 2 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 100 * Mode3::unit_block_side,  2 * Mode3::stage_height }, 12 * Mode3::unit_block_side, Platforms::Platform3));
    gameobjectmanager->Add(new Cone({ 105 * Mode3::unit_block_side, 2 * Mode3::unit_block_side + 2 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 110 * Mode3::unit_block_side, 6 * Mode3::unit_block_side + 2 * Mode3::stage_height }, 12 * Mode3::unit_block_side, Platforms::Platform3));
    gameobjectmanager->Add(new Drone({ 115 * Mode3::unit_block_side, 7 * Mode3::unit_block_side + 2 * Mode3::stage_height }, ball_ptr));
    
    gameobjectmanager->Add(new Platform({ 127 * Mode3::unit_block_side, 8 * Mode3::unit_block_side + 2* Mode3::stage_height }, 7 * Mode3::unit_block_side, Platforms::Platform3));

    gameobjectmanager->Add(new Platform({ 127 * Mode3::unit_block_side,  2 * Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform3));
    gameobjectmanager->Add(new Cone({ 130 * Mode3::unit_block_side,  Mode3::unit_block_side + 2 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 140 * Mode3::unit_block_side, 4 * Mode3::unit_block_side + 2 * Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform3));
    gameobjectmanager->Add(new Pin({ 145 * Mode3::unit_block_side, 5 * Mode3::unit_block_side  + 2 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 155 * Mode3::unit_block_side, 6 * Mode3::unit_block_side + 2 * Mode3::stage_height }, 7 * Mode3::unit_block_side, Platforms::Platform3));


    gameobjectmanager->Add(new Platform({ 163 * Mode3::unit_block_side,  3 * Mode3::unit_block_side + 2 * Mode3::stage_height }, 5 * Mode3::unit_block_side, Platforms::Platform3));
    gameobjectmanager->Add(new Cone({ 166 * Mode3::unit_block_side, 4 * Mode3::unit_block_side + 2 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 170 * Mode3::unit_block_side,   Mode3::unit_block_side + 2 * Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform3));
   

    gameobjectmanager->Add(new Platform({ 180 * Mode3::unit_block_side, 4 * Mode3::unit_block_side + 2 * Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform3));
    gameobjectmanager->Add(new Dumbbell({ 185 * Mode3::unit_block_side, 5 * Mode3::unit_block_side + 2 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 190 * Mode3::unit_block_side,  2 * Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform3));

 



    // stage 4

    //gameobjectmanager->Add(new Drone({ 174 * Mode3::unit_block_side, 5 * Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Platform({ 0,  3 * Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform4));


    gameobjectmanager->Add(new Platform({ 10 * Mode3::unit_block_side, 2 * Mode3::unit_block_side + 3 * Mode3::stage_height }, 6 * Mode3::unit_block_side, Platforms::Platform4));
    gameobjectmanager->Add(new Orb({ 12 * Mode3::unit_block_side, 3 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 18 * Mode3::unit_block_side, 0 + 3 * Mode3::stage_height }, 7 * Mode3::unit_block_side, Platforms::Platform4));
    gameobjectmanager->Add(new Dumbbell({ 20 * Mode3::unit_block_side, Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 25 * Mode3::unit_block_side, 2 * Mode3::unit_block_side + 3 * Mode3::stage_height }, 8 * Mode3::unit_block_side, Platforms::Platform4));
    gameobjectmanager->Add(new Cone({ 28 * Mode3::unit_block_side, 3 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 35 * Mode3::unit_block_side, 0 + 3 * Mode3::stage_height }, 6 * Mode3::unit_block_side, Platforms::Platform4));
    gameobjectmanager->Add(new Orb({ 38 * Mode3::unit_block_side, 1 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 43 * Mode3::unit_block_side, 3 * Mode3::unit_block_side + 3 * Mode3::stage_height }, 8 * Mode3::unit_block_side, Platforms::Platform4));
    gameobjectmanager->Add(new Pin({ 45 * Mode3::unit_block_side, 4 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 50 * Mode3::unit_block_side, 0 + 3 * Mode3::stage_height }, 6 * Mode3::unit_block_side, Platforms::Platform4));
    gameobjectmanager->Add(new Cone({ 53 * Mode3::unit_block_side, Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));
    gameobjectmanager->Add(new Orb({ 56 * Mode3::unit_block_side, 3 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 60 * Mode3::unit_block_side, 3 * Mode3::unit_block_side + 3 * Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform4));
    gameobjectmanager->Add(new Dumbbell({ 65 * Mode3::unit_block_side, 4 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 72 * Mode3::unit_block_side, 0 + 3 * Mode3::stage_height }, 7 * Mode3::unit_block_side, Platforms::Platform4));
    gameobjectmanager->Add(new Pin({ 75 * Mode3::unit_block_side, 1 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 80 * Mode3::unit_block_side, 2 * Mode3::unit_block_side + 3 * Mode3::stage_height }, 8 * Mode3::unit_block_side, Platforms::Platform4));
    gameobjectmanager->Add(new Cone({ 83 * Mode3::unit_block_side, 3 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));
    gameobjectmanager->Add(new Orb({ 86 * Mode3::unit_block_side, 4 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 90 * Mode3::unit_block_side, 0 + 3 * Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform4));
    gameobjectmanager->Add(new Dumbbell({ 93 * Mode3::unit_block_side, Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 100 * Mode3::unit_block_side, 3 * Mode3::unit_block_side + 3 * Mode3::stage_height }, 8 * Mode3::unit_block_side, Platforms::Platform4));
    gameobjectmanager->Add(new Pin({ 103 * Mode3::unit_block_side, 4 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 110 * Mode3::unit_block_side, 0 + 3 * Mode3::stage_height }, 7 * Mode3::unit_block_side, Platforms::Platform4));
    gameobjectmanager->Add(new Cone({ 113 * Mode3::unit_block_side, Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));
    gameobjectmanager->Add(new Orb({ 116 * Mode3::unit_block_side, 2 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 120 * Mode3::unit_block_side, 3 * Mode3::unit_block_side + 3 * Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform4));
    gameobjectmanager->Add(new Dumbbell({ 125 * Mode3::unit_block_side, 4 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));
    gameobjectmanager->Add(new Platform({ 132 * Mode3::unit_block_side, 0 + 3 * Mode3::stage_height }, 8 * Mode3::unit_block_side, Platforms::Platform4));
    gameobjectmanager->Add(new Pin({ 135 * Mode3::unit_block_side, 1 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 140 * Mode3::unit_block_side, 2 * Mode3::unit_block_side + 3 * Mode3::stage_height }, 8 * Mode3::unit_block_side, Platforms::Platform4));
    gameobjectmanager->Add(new Cone({ 143 * Mode3::unit_block_side, 3 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));
    gameobjectmanager->Add(new Orb({ 146 * Mode3::unit_block_side, 4 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 150 * Mode3::unit_block_side, 0 + 3 * Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform4));
    gameobjectmanager->Add(new Dumbbell({ 153 * Mode3::unit_block_side, Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));
    gameobjectmanager->Add(new Platform({ 160 * Mode3::unit_block_side, 3 * Mode3::unit_block_side + 3 * Mode3::stage_height }, 8 * Mode3::unit_block_side, Platforms::Platform4));
    gameobjectmanager->Add(new Pin({ 163 * Mode3::unit_block_side, 4 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 170 * Mode3::unit_block_side, 0 + 3 * Mode3::stage_height }, 7 * Mode3::unit_block_side, Platforms::Platform4));
    gameobjectmanager->Add(new Cone({ 173 * Mode3::unit_block_side, Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));
    gameobjectmanager->Add(new Orb({ 176 * Mode3::unit_block_side, 2 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Drone({ 30 * Mode3::unit_block_side, 5 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));
    gameobjectmanager->Add(new Drone({ 50 * Mode3::unit_block_side, 2 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));
    gameobjectmanager->Add(new Drone({ 70 * Mode3::unit_block_side, 4 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));
    gameobjectmanager->Add(new Drone({ 90 * Mode3::unit_block_side, 3 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));
    gameobjectmanager->Add(new Drone({ 110 * Mode3::unit_block_side, 5 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));
    gameobjectmanager->Add(new Drone({ 130 * Mode3::unit_block_side, 2 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));
    gameobjectmanager->Add(new Drone({ 150 * Mode3::unit_block_side, 4 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 180 * Mode3::unit_block_side, 3 * Mode3::unit_block_side + 3 * Mode3::stage_height }, 10 * Mode3::unit_block_side, Platforms::Platform4));
    gameobjectmanager->Add(new Dumbbell({ 185 * Mode3::unit_block_side, 4 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));
    gameobjectmanager->Add(new Platform({ 192 * Mode3::unit_block_side, 0 + 3 * Mode3::stage_height }, 8 * Mode3::unit_block_side, Platforms::Platform4));
    gameobjectmanager->Add(new Pin({ 195 * Mode3::unit_block_side, 1 * Mode3::unit_block_side + 3 * Mode3::stage_height }, ball_ptr));



    // stage 5

    //gameobjectmanager->Add(new Orb({ 174 * Mode3::unit_block_side, 5 * Mode3::unit_block_side }, ball_ptr));




    Math::irect portal1 = { {Mode3::map_width - 1000, Mode3::unit_block_side}, {Mode3::map_width + 120, Mode3::stage_height} };
    Math::irect portal2 = { {Mode3::map_width - 1000, Mode3::stage_height + Mode3::unit_block_side}, {Mode3::map_width + 120, 2 * Mode3::stage_height} };
    Math::irect portal3 = { {Mode3::map_width - 1000, 2 * Mode3::stage_height + Mode3::unit_block_side}, {Mode3::map_width + 120, 3 * Mode3::stage_height} };
    Math::irect portal4 = { {Mode3::map_width - 1000, 3 * Mode3::stage_height + Mode3::unit_block_side}, {Mode3::map_width + 120, 4 * Mode3::stage_height} };
    gameobjectmanager->Add(new Portal(4, portal1));
    gameobjectmanager->Add(new Portal(4, portal2));
    gameobjectmanager->Add(new Portal(4, portal3));
    gameobjectmanager->Add(new Portal(4, portal4));

    big_pin_ptr = new BigPin({ Mode3::map_width-1500,4 * Mode3::stage_height + Mode3::unit_block_side },ball_ptr);
    gameobjectmanager->Add(big_pin_ptr);

    // 플래이어 볼 시작 위치
    ball_ptr = new Ball({ 0, 400 });
    // 플레이어 볼 시작 레벨 변경은 Ball.h 파일에서 start_level 상수 변경하면 됨


    gameobjectmanager->Add(ball_ptr);
    ball_ptr->SetPosition({0,400});
}

void Mode3::Update(double dt)
{
    //Engine::GetLogger().LogDebug("mouseX: " + std::to_string(Engine::GetInput().GetMousePosition().x) + " mouseY: " + std::to_string(Engine::GetInput().GetMousePosition().y));
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

    //Engine::GetLogger().LogDebug(std::to_string(ball_ptr->GetPosition().x) + " " + std::to_string(ball_ptr->GetPosition().y));
    Engine::GetLogger().LogDebug(ball_ptr->current_state->GetName());
    //Engine::GetLogger().LogDebug(std::to_string(ball_ptr->GetGOComponent<Level>()->GetLevel())+" "+std::to_string(ball_ptr->GetGOComponent<Level>()->GetEXP()) + " " + std::to_string(ball_ptr->GetGOComponent<Level>()->GetEXPMax()));

    if (!big_pin_ptr->IsAlive()) {
        timer = 0.0;
        game_ending = true;
        ending_sound->Play();
    }

    if (timer >= ending_time && game_ending) {
        game_clear = true;
    }

    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Escape)||game_clear) {
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
    if (!big_pin_ptr->IsAlive()) {
        game_ending_text->Draw(Math::TranslationMatrix(Math::vec2{ (double)(Engine::GetWindow().GetSize().x - 2.0 * game_ending_text->GetSize().x) / 2, (double)(Engine::GetWindow().GetSize().y - 2.0 * game_ending_text->GetSize().y)/2 }) * Math::ScaleMatrix(Math::vec2{ 2.0,2.0 }));
    }
}

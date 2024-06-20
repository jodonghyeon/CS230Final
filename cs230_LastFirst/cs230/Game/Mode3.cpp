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
    gameobjectmanager->Add(new Platform({ 0, 0 }, 1400, Platforms::Platform1));
    gameobjectmanager->Add(new Platform({ 1200, 0 }, 1000, Platforms::Platform1));
    gameobjectmanager->Add(new Platform({ 2700, 0 }, 20000, Platforms::Platform1));
    gameobjectmanager->Add(new Platform({ 1500, 200 }, 1000, Platforms::Platform1));
    gameobjectmanager->Add(new Platform({ 1500, 200 }, 440, Platforms::Platform1));
    gameobjectmanager->Add(new Platform({ 1500, 200 }, 500, Platforms::Platform1));
    gameobjectmanager->Add(new Platform({ 1500, 400 }, 500, Platforms::Platform1));
    gameobjectmanager->Add(new Platform({ -500, Mode3::stage_height }, 5000, Platforms::Platform2));
    gameobjectmanager->Add(new Platform({ 5000, Mode3::stage_height }, 10000, Platforms::Platform2));
    gameobjectmanager->Add(new Platform({ 700, Mode3::stage_height+3* Mode3::unit_block_side }, 1000, Platforms::Platform2));
    gameobjectmanager->Add(new Platform({ 3900, 600 }, 600, Platforms::Platform2));
    gameobjectmanager->Add(new Platform({ 1500, 1000 }, 4000, Platforms::Platform2));
    gameobjectmanager->Add(new Pin({ 1000,60 }, ball_ptr));
    gameobjectmanager->Add(new Pin({ 3000,60 }, ball_ptr));
    gameobjectmanager->Add(new Pin({ 4000,60 }, ball_ptr));
    gameobjectmanager->Add(new Pin({ 5000,60 }, ball_ptr));
    gameobjectmanager->Add(new Pin({ 6000,60 }, ball_ptr));
    gameobjectmanager->Add(new Dumbbell({ 1700,60 }, ball_ptr));
    gameobjectmanager->Add(new Dumbbell({ 7000,60 }, ball_ptr));
    gameobjectmanager->Add(new Dumbbell({ 8000,60 }, ball_ptr));
    gameobjectmanager->Add(new Pin({ 9000,60 }, ball_ptr));

    gameobjectmanager->Add(new Platform({ 5000, Mode3::stage_height }, 7000, Platforms::Platform2));
    gameobjectmanager->Add(new Dumbbell({ 1000,Mode3::stage_height+ Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Dumbbell({ 2000,Mode3::stage_height + Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Dumbbell({ 3000,Mode3::stage_height + Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Pin({ 4000, Mode3::stage_height + Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Dumbbell({ 5000,Mode3::stage_height + Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Cone({ 8000,Mode3::stage_height + Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Cone({ 10000,Mode3::stage_height + Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Dumbbell({ 9000,Mode3::stage_height + Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Dumbbell({ 11000,Mode3::stage_height + Mode3::unit_block_side }, ball_ptr));

    gameobjectmanager->Add(new Cone({ 1000,2*Mode3::stage_height + Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Cone({ 2000,2 * Mode3::stage_height + Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Cone({ 3000,2 * Mode3::stage_height + Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Cone({ 4000,2 * Mode3::stage_height + Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Drone({ 5000,2 * Mode3::stage_height + Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Drone({ 6000,2 * Mode3::stage_height + Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Drone({ 8000,2 * Mode3::stage_height + Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Drone({ 10000,2 * Mode3::stage_height + Mode3::unit_block_side }, ball_ptr));

    gameobjectmanager->Add(new Drone({ 1000, 3 * Mode3::stage_height + Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Drone({ 3000, 3 * Mode3::stage_height + Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Drone({ 5000, 3 * Mode3::stage_height + Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Drone({ 6000, 3 * Mode3::stage_height + Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Drone({ 8000, 3 * Mode3::stage_height + Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Drone({ 9000, 3 * Mode3::stage_height + Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Drone({ 10000, 3 * Mode3::stage_height + Mode3::unit_block_side }, ball_ptr));

    gameobjectmanager->Add(new Drone({ 2000, 4 * Mode3::stage_height + Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Pin({ 6000, 4 * Mode3::stage_height + Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Orb({ 1000, 4 * Mode3::stage_height + Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Orb({ 3000, 4 * Mode3::stage_height + Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Orb({ 5000, 4 * Mode3::stage_height + Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Orb({ 7000, 4 * Mode3::stage_height + Mode3::unit_block_side }, ball_ptr));
    gameobjectmanager->Add(new Orb({ 9000, 4 * Mode3::stage_height + Mode3::unit_block_side }, ball_ptr));

    gameobjectmanager->Add(new Platform({ -500, 2 * Mode3::stage_height }, 14000, Platforms::Platform3));
    gameobjectmanager->Add(new Platform({ -500, 3 * Mode3::stage_height }, 14000, Platforms::Platform4));
    gameobjectmanager->Add(new Platform({ -500, 4 * Mode3::stage_height }, 14000, Platforms::Platform5));



    Math::irect portal1 = { {Mode3::map_width + 60, Mode3::unit_block_side}, {Mode3::map_width + 180, (int)Mode3::stage_height} };
    Math::irect portal2 = { {Mode3::map_width + 60, (int)Mode3::stage_height + Mode3::unit_block_side}, {Mode3::map_width + 180, 2 * (int)Mode3::stage_height} };
    Math::irect portal3 = { {Mode3::map_width + 60, 2 * (int)Mode3::stage_height + Mode3::unit_block_side}, {Mode3::map_width + 180, 3 * (int)Mode3::stage_height} };
    Math::irect portal4 = { {Mode3::map_width + 60, 3 * (int)Mode3::stage_height + Mode3::unit_block_side}, {Mode3::map_width + 180, 4 * (int)Mode3::stage_height} };
    gameobjectmanager->Add(new Portal(4, portal1));
    gameobjectmanager->Add(new Portal(4, portal2));
    gameobjectmanager->Add(new Portal(4, portal3));
    gameobjectmanager->Add(new Portal(4, portal4));

    big_pin_ptr = new BigPin({ Mode3::map_width-1500,4* Mode3::stage_height + Mode3::unit_block_side },ball_ptr);
    gameobjectmanager->Add(big_pin_ptr);

    ball_ptr = new Ball({ 100, 200 });
    gameobjectmanager->Add(ball_ptr);
    CS230::DampingCamera* camera = GetGSComponent<CS230::DampingCamera>();
    camera->SetPosition({ 0,0 });
}

void Mode3::Update(double dt)
{
    //Engine::GetLogger().LogDebug("mouseX: " + std::to_string(Engine::GetInput().GetMousePosition().x) + " mouseY: " + std::to_string(Engine::GetInput().GetMousePosition().y));
    timer += dt;
    
    UpdateGSComponents(dt);
    GetGSComponent<CS230::GameObjectManager>()->UpdateAll(dt);

    GetGSComponent<CS230::DampingCamera>()->Update(ball_ptr,dt);
    
    if (ball_ptr->GetGOComponent<Level>()->IsLevelUpdated()) {
        GetGSComponent<CS230::DampingCamera>()->SetTargetOffset(Math::vec2{ camera_offset1X-(camera_offsetX_level_diff * (ball_ptr->GetGOComponent<Level>()->GetLevel() - 1)) * (camera_offsetX_level_diff * (ball_ptr->GetGOComponent<Level>()->GetLevel() - 1)), camera_offset1Y});
    }

    if (ball_ptr->GetPosition().x - GetGSComponent<CS230::DampingCamera>()->GetPosition().x > Engine::GetInput().GetMousePosition().x) {
        GetGSComponent<Cursor>()->SetType(1);
    }
    else {
        GetGSComponent<Cursor>()->SetType(0);
    }

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

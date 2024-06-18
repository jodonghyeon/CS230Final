/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Engine.cpp
Project:    CS230 Engine
Author:     Donghyeon Jo
Created:    March 14, 2024
*/

#include "Engine.h"

Engine::Engine() :last_tick(std::chrono::system_clock::now()),
#ifdef _DEBUG
    logger(CS230::Logger::Severity::Debug, true,last_tick)
#else
    logger(CS230::Logger::Severity::Event, false, last_tick)
#endif
{ }

void Engine::Start(std::string window_title) {
    logger.LogEvent("Engine Started");
    window.Start(window_title);
    //Start other services
    last_test = last_tick;
    unsigned int seed = time(NULL);
    srand(seed);
    logger.LogEvent("Seed: "+std::to_string(seed));
}

void Engine::Stop() {
    //Stop all services
    logger.LogEvent("Engine Stopped");
}

void Engine::Update() {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    double dt = std::chrono::duration<double>(now - last_tick).count();
    if (dt >= 1 / TargetFPS)
    {
        logger.LogVerbose("Engine Update");
        window.Update();
        last_tick = now;
        
        ++frame_count;
        if (frame_count >= FPSTargetFrames)
        {
            char fps_log[15];
            double FPS = frame_count / std::chrono::duration<double>(now - last_test).count();
            sprintf_s(fps_log, "FPS: %.6f", FPS);
            logger.LogDebug(fps_log);
            frame_count = 0;
            last_test = now;
        }
        GameStateManager.Update(dt);
        input.Update();
    }
    
    //Update other services
}

bool Engine::HasGameEnded()
{
    return GameStateManager.HasGameEnded() || window.IsClosed();
}

void Engine::AddFont(const std::filesystem::path& file_name)
{
    fonts.push_back(CS230::Font(file_name));
}

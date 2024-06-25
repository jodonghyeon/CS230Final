/*
File Name:  Ending.h
Project:    CS230 Final
Author:     Donghyeon Jo
Created:    June 16, 2024
*/

#pragma once
#include "..\Engine\GameState.h"
#include "..\Engine\Texture.h"
#include "..\Engine\GameAudio.h"

class Ending : public CS230::GameState {
public:
    Ending();
    void Load() override;
    void Update([[maybe_unused]] double dt) override;
    void Unload() override;
    void Draw() override;

    bool IsCleared() { return cleared; }

    std::string GetName() override {
        return "Ending";
    }

private:
    CS230::Texture* thanks_text;
    CS230::Texture* donghyeon_text;
    CS230::Texture* jiyun_text;
    CS230::Texture* exit_to_menu_text;
    CS230::GameSound* ending_sound;

    bool cleared;
};
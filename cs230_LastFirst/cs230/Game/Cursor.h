/*
File Name:  Cursor.h
Project:    CS230 Final
Author:     Donghyeon Jo
Created:    June 19, 2024
*/

#pragma once
#include "..\Engine\Component.h"
#include "..\Engine\Texture.h"

class Cursor : public CS230::Component {
public:
    void Add(const std::filesystem::path& texture_path);
    void SetType(int new_type) { type = new_type; }
    void Draw();
private:
    int type=0;
    std::vector<CS230::Texture*> textures = {};
};

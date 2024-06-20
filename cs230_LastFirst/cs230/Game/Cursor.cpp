/*
File Name:  Cursor.cpp
Project:    CS230 Final
Author:     Donghyeon Jo
Created:    June 19, 2024
*/

#include "Cursor.h"
#include "..\Engine\Engine.h"

void Cursor::Add(const std::filesystem::path& texture_path)
{
	textures.push_back(Engine::GetTextureManager().Load(texture_path));
}

void Cursor::Draw()
{
	textures[type]->Draw(Math::TranslationMatrix(Math::vec2{Engine::GetInput().GetMousePosition().x - textures[type]->GetSize().x / 2, Engine::GetInput().GetMousePosition().y - textures[type]->GetSize().y / 2}));
}

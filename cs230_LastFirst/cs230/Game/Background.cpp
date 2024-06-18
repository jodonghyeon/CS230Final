/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Background.cpp
Project:    CS230 Engine
Author:     Donghyeon Jo
Created:    April 6, 2024
*/

#include "Background.h"
#include "..\Engine\Engine.h"

void Background::Add(const std::filesystem::path& texture_path, double speed)
{
	backgrounds.push_back(ParallaxLayer{ Engine::GetTextureManager().Load(texture_path),speed});
}

void Background::Unload()
{
	backgrounds.clear();
}

void Background::Draw(const CS230::Camera& camera)
{
	for (int i = 0; i < backgrounds.size(); ++i) {
		backgrounds[i].texture->Draw(Math::TranslationMatrix(Math::vec2{ { - backgrounds[i].speed * camera.GetPosition().x }, {- camera.GetPosition().y} }));
	}
}

void Background::Draw(const CS230::DampingCamera& camera)
{
    for (int i = 0; i < backgrounds.size(); ++i) {
        double backgroundX = (camera.GetPosition().x * backgrounds[i].speed);

        int num_tile = static_cast<int>(camera.GetLimit().Size().x / backgrounds[i].texture->GetSize().x) + 2;
        for (int j = 0; j < num_tile; ++j) {
            double tileX = -backgroundX + j * backgrounds[i].texture->GetSize().x;

            if (tileX >= -backgrounds[i].texture->GetSize().x) {
                backgrounds[i].texture->Draw(Math::TranslationMatrix(Math::vec2{ tileX, -camera.GetPosition().y }));
            }
        }
    }

}

Math::ivec2 Background::GetSize()
{
	return Math::ivec2(backgrounds[backgrounds.size()-1].texture->GetSize());
}

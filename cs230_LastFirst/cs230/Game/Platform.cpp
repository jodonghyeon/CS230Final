/*
File Name:  Platform.cpp
Project:    CS230 Final
Author:     Donghyeon Jo
Created:    June 15, 2024
*/

#include "Platform.h"
#include "..\Engine\Collision.h"
#include "..\Engine\Engine.h"
#include "..\Engine\ShowCollision.h"

Platform::Platform(Math::vec2 position, int length, Platforms type)
	: GameObject(static_cast<Math::vec2>(position)), length(length)
{
    AddGOComponent(new CS230::RectCollision({ Math::ivec2{ 0, 0 }, Math::ivec2{ length, platform_height } }, this));
	switch (type)
	{
	case Platforms::Platform1:
		texture = Engine::GetTextureManager().Load("Assets/Platform1.png");
		break;
	case Platforms::Platform2:
		texture = Engine::GetTextureManager().Load("Assets/Platform2.png");
		break;
	case Platforms::Platform3:
		texture = Engine::GetTextureManager().Load("Assets/Platform3.png");
		break;
	case Platforms::Platform4:
		texture = Engine::GetTextureManager().Load("Assets/Platform4.png");
		break;
	case Platforms::Platform5:
		texture = Engine::GetTextureManager().Load("Assets/Platform5.png");
		break;
	default:
		break;
	}
}

void Platform::Draw(Math::TransformationMatrix camera_matrix)
{
	int middle_num = length / platform_unit_width - 1;
	texture->Draw(camera_matrix * GetMatrix() * Math::TranslationMatrix(Math::ivec2{ 0,0 }), Math::ivec2{ 0,0 }, Math::ivec2{ platform_unit_width, platform_height });
	for (int i = 1; i <= middle_num; ++i) {
		texture->Draw(camera_matrix * GetMatrix() * Math::TranslationMatrix(Math::ivec2{ platform_unit_width * i,0 }), Math::ivec2{ platform_unit_width,0 }, Math::ivec2{ platform_unit_width, platform_height });
	}
	texture->Draw(camera_matrix * GetMatrix() * Math::TranslationMatrix(Math::ivec2{ length - platform_unit_width,0 }), Math::ivec2{ 2 * platform_unit_width,0 }, Math::ivec2{ platform_unit_width, platform_height });

	CS230::Collision* collision = GetGOComponent<CS230::Collision>();
	if (collision != nullptr && Engine::GetGameStateManager().GetGSComponent<CS230::ShowCollision>() != nullptr
		&& Engine::GetGameStateManager().GetGSComponent<CS230::ShowCollision>()->Enabled()) {
		collision->Draw(camera_matrix);
	}
}


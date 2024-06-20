/*
File Name:  StatusBar.cpp
Project:    CS230 Final
Author:     Donghyeon Jo
Created:    June 19, 2024
*/

#include "StatusBar.h"
#include "..\Engine\Engine.h"
#include "Fonts.h"

StatusBar::StatusBar(Math::vec2 level_position, Math::vec2 exp_position, Math::vec2 stamina_position, Level* given_level_ptr, Stamina* given_stamina_ptr)
	: level_position(level_position), exp_position(exp_position), stamina_position(stamina_position)
{

	level1_text = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("1", 0xFFFFFFFF);
	level2_text = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("2", 0xFFFFFFFF);
	level3_text = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("3", 0xFFFFFFFF);
	level4_text = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("4", 0xFFFFFFFF);
	level5_text = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("5", 0xFFFFFFFF);

	level1 = Engine::GetTextureManager().Load("Assets/Level1.png");
	level2 = Engine::GetTextureManager().Load("Assets/Level2.png");
	level3 = Engine::GetTextureManager().Load("Assets/Level3.png");
	level4 = Engine::GetTextureManager().Load("Assets/Level4.png");
	level5 = Engine::GetTextureManager().Load("Assets/Level5.png");
	exp_back_texture = Engine::GetTextureManager().Load("Assets/EXPBarWhite.png");
	exp_front_texture = Engine::GetTextureManager().Load("Assets/EXPBarYellow.png");
	stamina_back_texture = Engine::GetTextureManager().Load("Assets/StaminaBarWhite.png");
	stamina_front_texture = Engine::GetTextureManager().Load("Assets/StaminaBarGreen.png");
	level_ptr = given_level_ptr;
	stamina_ptr = given_stamina_ptr;
}

void StatusBar::Draw()
{
	exp_back_texture->Draw(Math::TranslationMatrix(exp_position), Math::ivec2(0, 0), Math::ivec2(exp_back_texture->GetSize()));
	exp_front_texture->Draw(Math::TranslationMatrix(exp_position), Math::ivec2(0, 0), Math::ivec2(exp_front_texture->GetSize().x*level_ptr->GetEXP()/level_ptr->GetEXPMax(), exp_front_texture->GetSize().y));
	stamina_back_texture->Draw(Math::TranslationMatrix(stamina_position), Math::ivec2(0, 0), Math::ivec2(stamina_back_texture->GetSize()));
	stamina_front_texture->Draw(Math::TranslationMatrix(stamina_position), Math::ivec2(0, 0), Math::ivec2(stamina_front_texture->GetSize().x * stamina_ptr->GetStamina()/stamina_ptr->GetStaminaMax(), stamina_front_texture->GetSize().y));
	switch (level_ptr->GetLevel())
	{
	case 1:
		level1->Draw(Math::TranslationMatrix(level_position));
		level1_text->Draw(Math::TranslationMatrix(Math::vec2{ level_position.x + level1->GetSize().x*2/5, level_position.y + level1->GetSize().y/4}));
		break;
	case 2:
		level2->Draw(Math::TranslationMatrix(level_position));
		level2_text->Draw(Math::TranslationMatrix(Math::vec2{ level_position.x + level2->GetSize().x * 2 / 5, level_position.y + level2->GetSize().y / 4 }));
		break;
	case 3:
		level3->Draw(Math::TranslationMatrix(level_position));
		level3_text->Draw(Math::TranslationMatrix(Math::vec2{ level_position.x + level3->GetSize().x * 2 / 5, level_position.y + level3->GetSize().y / 4 }));
		break;
	case 4:
		level4->Draw(Math::TranslationMatrix(level_position));
		level4_text->Draw(Math::TranslationMatrix(Math::vec2{ level_position.x + level4->GetSize().x * 2 / 5, level_position.y + level4->GetSize().y / 4 }));
		break;
	case 5:
		level5->Draw(Math::TranslationMatrix(level_position));
		level5_text->Draw(Math::TranslationMatrix(Math::vec2{ level_position.x + level5->GetSize().x * 2 / 5, level_position.y + level5->GetSize().y / 4 }));
		break;
	default:
		break;
	}
}

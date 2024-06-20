/*
File Name:  GameAudioManager.h
Project:    CS230 Final
Author:     Donghyeon Jo
Created:    June 19, 2024
*/

#pragma once
#include <filesystem>
#include <map>

namespace CS230 {
	class GameSound;
	class GameMusic;

	class GameAudioManager {
	public:
		GameAudioManager();

		GameSound* LoadSound(const std::filesystem::path& file_name);
		void UnloadAllSound();

		GameMusic* LoadMusic(const std::filesystem::path& file_name);
		void UnloadAllMusic();

		void Update();
		void UnloadAll();

	private:
		std::map<std::filesystem::path, GameSound*> sounds;
		std::map<std::filesystem::path, GameMusic*> musics;
	};
}
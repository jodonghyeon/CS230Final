/*
File Name:  GameAudioManager.cpp
Project:    CS230 Final
Author:     Donghyeon Jo
Created:    June 19, 2024
*/

#include "GameAudio.h"
#include "GameAudioManager.h"
#include "Engine.h"
#include <raylib.h>

CS230::GameAudioManager::GameAudioManager()
{
	InitAudioDevice();
}

CS230::GameSound* CS230::GameAudioManager::LoadSound(const std::filesystem::path& file_name)
{
	if (sounds.find(file_name) == sounds.end()) {
		sounds.insert({ file_name, new GameSound(file_name) });
		Engine::GetLogger().LogEvent("Loading Sound: " + file_name.string());
	}

	return sounds[file_name];
}

void CS230::GameAudioManager::UnloadAllSound()
{
	for (auto itr = sounds.begin(); itr != sounds.end(); ++itr) {
		delete itr->second;
	}
	sounds.clear();
	Engine::GetLogger().LogEvent("Clearing Sounds");
}

CS230::GameMusic* CS230::GameAudioManager::LoadMusic(const std::filesystem::path& file_name)
{
	if (musics.find(file_name) == musics.end()) {
		musics.insert({ file_name, new GameMusic(file_name) });
		Engine::GetLogger().LogEvent("Loading Music: " + file_name.string());
	}

	return musics[file_name];
}

void CS230::GameAudioManager::UnloadAllMusic()
{
	for (auto itr = musics.begin(); itr != musics.end(); ++itr) {
		delete itr->second;
	}
	musics.clear();
	Engine::GetLogger().LogEvent("Clearing Musics");
}



void CS230::GameAudioManager::Update()
{
	for (auto itr = sounds.begin(); itr != sounds.end();)
	{
		if (itr->second->Destroyed()) {
			delete itr->second;
			itr = sounds.erase(itr);
		}
		else {
			++itr;
		}
	}

	for (auto itr = musics.begin(); itr != musics.end();)
	{
		itr->second->Update();
		if (itr->second->Destroyed()) {
			delete itr->second;
			itr = musics.erase(itr);
		}
		else {
			++itr;
		}
	}
}

void CS230::GameAudioManager::UnloadAll()
{
	UnloadAllSound();
	UnloadAllMusic();
}

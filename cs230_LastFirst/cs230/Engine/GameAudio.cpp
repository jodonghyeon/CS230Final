/*
File Name:  GameAudio.cpp
Project:    CS230 Final
Author:     Donghyeon Jo
Created:    June 19, 2024
*/

#include "GameAudio.h"

namespace CS230 {

	GameSound::GameSound(const std::filesystem::path& sound_file)
	{
		sound = LoadSound(sound_file.string().c_str());
	}

	GameSound::GameSound(Sound given_sound) {
		sound = given_sound;
	}

	GameSound::~GameSound()
	{
		UnloadSound(sound);
	}

	void GameSound::Play()
	{
		PlaySound(sound);
	}

	void GameSound::Stop()
	{
		StopSound(sound);
	}

	void GameSound::Pause()
	{
		PauseSound(sound);
	}

	void GameSound::Resume()
	{
		ResumeSound(sound);
	}

	void GameSound::SetSoundVolume(float new_volume)
	{
		SetSoundVolume(new_volume);
		volume = new_volume;
	}




	GameMusic::GameMusic(const std::filesystem::path& music_file)
	{
		music = LoadMusicStream(music_file.string().c_str());
	}

	GameMusic::GameMusic(Music given_music) {
		music = given_music;
	}

	GameMusic::~GameMusic()
	{
		UnloadMusicStream(music);
	}

	void GameMusic::Start()
	{
		PlayMusicStream(music);
	}

	void GameMusic::Stop()
	{
		StopMusicStream(music);
	}

	void GameMusic::Update()
	{
		UpdateMusicStream(music);
	}

	void GameMusic::Pause()
	{
		PauseMusicStream(music);
	}

	void GameMusic::Resume()
	{
		ResumeMusicStream(music);
	}

	void GameMusic::SetMusicVolume(float new_volume)
	{
		SetMusicVolume(volume);
		volume = new_volume;
	}

	bool GameMusic::IsMusicPlaying() const
	{
		return IsMusicStreamPlaying(music);
	}

}
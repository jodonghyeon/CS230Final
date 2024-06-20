/*
File Name:  GameAudio.h
Project:    CS230 Final
Author:     Donghyeon Jo
Created:    June 19, 2024
*/

#pragma once
#include <filesystem>
#include <raylib.h>

namespace CS230 {

	class GameSound {
	public:
		friend class GameAudioManager;

		void Play();
		void Stop();
		void Pause();
		void Resume();
		void SetSoundVolume(float volume);

		float GetSoundVolume()const { return volume; }

		~GameSound();

		void Destroy() { destroy = true; }
		bool Destroyed() { return destroy; }

	private:
		GameSound(Sound given_sound);
		GameSound(const std::filesystem::path& music_file);

		Sound sound = {};
		float volume = 1.0f;
		bool destroy = false;
	};

	class GameMusic {
	public:
		friend class GameAudioManager;

		void Start();
		void Stop();
		void Update();
		void Pause();
		void Resume();
		void SetMusicVolume(float volume);

		float GetMusicVolume()const { return volume; }
		bool IsMusicPlaying()const;

		~GameMusic();

		void Destroy() { destroy = true; }
		bool Destroyed() { return destroy; }

	private:
		GameMusic(Music given_music);
		GameMusic(const std::filesystem::path& music_file);

		Music music = {};
		float volume = 1.0f;
		bool destroy = false;
	};
}
#include "pch.h"
#include "Sound.h"

#include "Game.h"

using namespace DirectX;

Sound::Sound(const wchar_t* waveFileName)
{
	auto& game = Game::GetInstance();

	m_soundEffect = std::make_unique<SoundEffect>(game.m_audEngine.get(), waveFileName);
	m_soundEffectInstance = m_soundEffect->CreateInstance();
}

Sound::~Sound()
{
	m_soundEffectInstance.reset();
}

void Sound::Play(bool loop)
{
	m_soundEffectInstance->Play(loop);
}

void Sound::SetVolume(float volume)
{
	m_soundEffectInstance->SetVolume(volume);
}

void Sound::SetPitch(float pitch)
{
	m_soundEffectInstance->SetPitch(pitch);
}

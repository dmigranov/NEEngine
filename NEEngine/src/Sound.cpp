#include "pch.h"
#include "Sound.h"

#include "Game.h"

using namespace DirectX;

Sound::Sound(const wchar_t* waveFileName)
{
	auto& game = Game::GetInstance();

	m_soundEffect = std::make_unique<SoundEffect>(game.m_audEngine.get(), waveFileName);
	m_soundEffectInstance = m_soundEffect->CreateInstance();
	m_soundEffectInstance->Play(true);
}

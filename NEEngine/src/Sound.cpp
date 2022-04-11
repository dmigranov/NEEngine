#include "pch.h"
#include "Sound.h"

#include "Game.h"
#include "Scene.h"

using namespace DirectX;

Sound::Sound()
{
	
}

Sound::Sound(const wchar_t* waveFileName)
{
	auto& game = Game::GetInstance();

	m_soundEffect = std::make_unique<SoundEffect>(game.m_audEngine.get(), waveFileName);
	m_soundEffectInstance = m_soundEffect->CreateInstance();
}

Sound::Sound(std::function<void(int16_t*, int, int)> generateFunction)
{
	auto& game = Game::GetInstance();

	m_generateFunction = generateFunction;
	m_soundEffectInstance = std::make_unique<DynamicSoundEffectInstance>(game.m_audEngine.get(),
		[](DynamicSoundEffectInstance*)
		{
			// 'Buffer needed' event handler
		},
		44100, 1);
}

Sound::~Sound()
{
	m_soundEffectInstance.reset();
}

void Sound::Play(bool loop)
{
	m_soundEffectInstance->Play(loop);
	if (loop)
	{
		auto& game = Game::GetInstance();
		auto pScene = game.GetScene();
		pScene->AddLoopedSound(this);
	}
}

void Sound::SetVolume(float volume)
{
	m_soundEffectInstance->SetVolume(volume);
}

void Sound::SetPitch(float pitch)
{
	m_soundEffectInstance->SetPitch(pitch);
}

void Sound::SetPan(float pan)
{
	m_soundEffectInstance->SetPan(pan);
}

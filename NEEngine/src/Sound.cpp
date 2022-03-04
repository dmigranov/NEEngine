#include "pch.h"
#include "Sound.h"

#include "Game.h"

using namespace DirectX;

Sound::Sound(const wchar_t* waveFileName)
{
	m_soundEffect = std::make_unique<SoundEffect>(m_audEngine.get(),
		L"explo1.wav");
}

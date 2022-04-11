#include "pch.h"
#include "DynamicSound.h"

#include "Game.h"
#include "Scene.h"

using namespace DirectX;

DynamicSound::DynamicSound(std::function<void(int16_t*, int, int)> generateFunction)
{
	auto& game = Game::GetInstance();

	m_generateFunction = generateFunction;

	// PCM (»мпульсно-кодова€ модул€ци€) 44100 Hz, 16-bit, 1 channel
	m_audioBytes.resize(44100 * 2);
	m_dynamicSoundEffectInstance = std::make_unique<DynamicSoundEffectInstance>(game.m_audEngine.get(),
		[this](DynamicSoundEffectInstance*)
		{
			// 'Buffer needed' event handler
			m_audioBytes;
		},
		44100, 1);
}

DynamicSound::~DynamicSound()
{
}

#include "pch.h"
#include "DynamicSound.h"

#include "Game.h"
#include "Scene.h"
DynamicSound::DynamicSound(std::function<void(int16_t*, int, int)> generateFunction)
{
	auto& game = Game::GetInstance();

	m_generateFunction = generateFunction;
	m_dynamicSoundEffectInstance = std::make_unique<DynamicSoundEffectInstance>(game.m_audEngine.get(),
		[](DynamicSoundEffectInstance*)
		{
			// 'Buffer needed' event handler
		},
		44100, 1);
}

DynamicSound::~DynamicSound()
{
}

#include "pch.h"
#include "DynamicSound.h"

#include "Game.h"
#include "Scene.h"

using namespace DirectX;

DynamicSound::DynamicSound(std::function<void(int16_t*, int, int)> generateFunction)
{
	auto& game = Game::GetInstance();

	m_generateFunction = generateFunction;

	// PCM (���������-������� ���������) 44100 Hz, 16-bit, 1 channel
	m_audioBytes.resize(44100 * 2);

	// ��� ������, ����������� ����� �������
	m_generateFunction(reinterpret_cast<int16_t*>(&m_audioBytes.front()),
		44100, 440);

	m_dynamicSoundEffectInstance = std::make_unique<DynamicSoundEffectInstance>(game.m_audEngine.get(),
		[this](DynamicSoundEffectInstance* effect)
		{
			// 'Buffer needed' event handler
			// This callback function is invoked whenever there are <= 2 buffers pending 
			// or whenever a buffer completes playback. 
			// You should submit sufficient data to avoid starving the voice.

			int count = effect->GetPendingBufferCount();
			while (count < 3)
			{
				effect->SubmitBuffer(&m_audioBytes.front(), m_audioBytes.size());
				++count;
			}
		},
		44100, 1);
}

DynamicSound::~DynamicSound()
{
	m_dynamicSoundEffectInstance.reset();
}

void DynamicSound::Play(bool loop)
{
	m_dynamicSoundEffectInstance->Play();
}

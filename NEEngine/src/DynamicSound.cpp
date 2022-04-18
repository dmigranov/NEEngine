#include "pch.h"
#include "DynamicSound.h"

#include "Game.h"
#include "Scene.h"

using namespace DirectX;

DynamicSound::DynamicSound(std::function<void(int16_t*, int, int)> generateFunction, double length)
{
	auto& game = Game::GetInstance();

	m_generateFunction = generateFunction;

	// PCM (»мпульсно-кодова€ модул€ци€) 44100 Hz, 16-bit, 1 channel
	// умножаем на два - так как вектор однобайтовых чисел, а работаем с двухбайтовыми
	m_sampleCount = 44100 * length;
	for (size_t i = 0; i < m_audioBytesBufferCount; i++)
	{
		m_audioBytesBuffers[i].resize(m_sampleCount * 2);
	}

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
				//m_generateFunction(reinterpret_cast<int16_t*>(&m_audioBytes.front()), m_sampleCount, 440); //тут или за while?
				m_generateFunction(reinterpret_cast<int16_t*>(&m_audioBytesBuffers[m_currentBuffer++].front()), m_sampleCount, 440);
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

void DynamicSound::SetVolume(float volume)
{
	m_dynamicSoundEffectInstance->SetVolume(volume);
}

void DynamicSound::SetPitch(float pitch)
{
	m_dynamicSoundEffectInstance->SetPitch(pitch);
}

void DynamicSound::SetPan(float pan)
{
	m_dynamicSoundEffectInstance->SetPan(pan);
}

void DynamicSound::Stop(bool immediate)
{
	m_dynamicSoundEffectInstance->Stop(immediate);
}

void DynamicSound::Pause()
{
	m_dynamicSoundEffectInstance->Pause();
}

void DynamicSound::Resume()
{
	m_dynamicSoundEffectInstance->Resume();
}

size_t DynamicSound::GetSampleCount()
{
	return m_sampleCount;
}

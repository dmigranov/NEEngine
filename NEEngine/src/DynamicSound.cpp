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
	m_audioBytes.resize(m_sampleCount * 2);

	// ƒл€ начала, сгенерируем буфер заранее
	//m_generateFunction(reinterpret_cast<int16_t*>(&m_audioBytes.front()), 44100, 440);

	m_dynamicSoundEffectInstance = std::make_unique<DynamicSoundEffectInstance>(game.m_audEngine.get(),
		[this](DynamicSoundEffectInstance* effect)
		{
			// 'Buffer needed' event handler
			// This callback function is invoked whenever there are <= 2 buffers pending 
			// or whenever a buffer completes playback. 
			// You should submit sufficient data to avoid starving the voice.

			int count = effect->GetPendingBufferCount();
			while (count < 4)
			{
				m_generateFunction(reinterpret_cast<int16_t*>(&m_audioBytes.front()), m_sampleCount, 440); //тут или за while?
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

size_t DynamicSound::GetSampleCount()
{
	return m_sampleCount;
}

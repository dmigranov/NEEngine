#pragma once
#include "Sound.h"
class DynamicSound :
    public Sound
{
public:
    DynamicSound(std::function<void(int16_t*, int, int)> generateFunction, double length);
    ~DynamicSound();

    virtual void Play(bool loop = false) override;

    virtual void SetVolume(float volume) override;
    virtual void SetPitch(float pitch) override;
    virtual void SetPan(float pan) override;

    virtual void Stop(bool immediate = true) override;
    virtual void Pause() override;
    virtual void Resume() override;

    size_t GetSampleCount();
private:
    std::unique_ptr<DirectX::DynamicSoundEffectInstance> m_dynamicSoundEffectInstance;
    std::function<void(int16_t*, int, int)> m_generateFunction;

    size_t m_sampleCount;

    constexpr static size_t m_audioBytesBufferCount = 3;
    size_t m_audioBytesCurrent = 0;
    std::vector<uint8_t> m_audioBytesBuffers[m_audioBytesBufferCount];
};
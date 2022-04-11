#pragma once
#include "Sound.h"
class DynamicSound :
    public Sound
{
public:
    DynamicSound(std::function<void(int16_t*, int, int)> generateFunction);
    ~DynamicSound();

    virtual void Play(bool loop = false) override;

    virtual void SetVolume(float volume) override;
    virtual void SetPitch(float pitch) override;
    virtual void SetPan(float pan) override;

private:
    std::unique_ptr<DirectX::DynamicSoundEffectInstance> m_dynamicSoundEffectInstance;
    std::function<void(int16_t*, int, int)> m_generateFunction;

    std::vector<uint8_t> m_audioBytes;
};
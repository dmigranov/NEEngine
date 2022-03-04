#pragma once
class Sound
{
public:
	Sound(const wchar_t* waveFileName);
private:
	std::unique_ptr<DirectX::SoundEffect> m_soundEffect;
	std::unique_ptr<DirectX::SoundEffectInstance> m_soundEffectInstance;
};


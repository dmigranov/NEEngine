#pragma once
class Sound
{
public:
	Sound(const wchar_t* waveFileName);
	Sound(std::function<void(int16_t*, int, int)> generateFunction);
	~Sound();

	void Play(bool loop = false);

	void SetVolume(float volume);
	void SetPitch(float pitch);
	void SetPan(float pan);

private:
	DirectX::SoundEffect* m_soundEffect = nullptr;
	DirectX::SoundEffectInstance* m_soundEffectInstance = nullptr;

	std::function<void(int16_t*, int, int)> m_generateFunction;
};
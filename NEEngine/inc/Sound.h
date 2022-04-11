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
	std::unique_ptr<DirectX::SoundEffect> m_soundEffect;
	std::unique_ptr<DirectX::SoundEffectInstance> m_soundEffectInstance;

	private std::function<void(int16_t*, int, int)> m_generateFunction;
};
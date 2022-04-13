#pragma once
class Sound
{
public:
	Sound(const wchar_t* waveFileName);
	~Sound();

	virtual void Play(bool loop = false);

	virtual void SetVolume(float volume);
	virtual void SetPitch(float pitch);
	virtual void SetPan(float pan);

	virtual void Stop();
	virtual void Pause();
	virtual void Resume();

protected:
	Sound();

private:
	std::unique_ptr<DirectX::SoundEffect> m_soundEffect;
	std::unique_ptr<DirectX::SoundEffectInstance> m_soundEffectInstance;
};
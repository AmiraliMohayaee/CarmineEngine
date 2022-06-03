#pragma once

#include <fmod.hpp>
#include <string>
#include <map>



const float LEFT_PAN = -1.0;
const float RIGHT_PAN = 1.0f;

const float MIN_VOLUME = 0.0f;
const float MAX_VOLUME = 1.0f;


typedef unsigned int Fuint;

class Audio
{
public: 
	
	enum class Loop
	{
		None = 0,
		Single = 1,
		Endless = -1,
		Custom = -2
	};

	enum class Position
	{
		Start = 1,
		End = 2,
		Custom = 0
	};

	enum class Interval
	{
		Semitone = 0,
		Octave = 1
	};

	enum class Type
	{
		Music,
		Sound
	};

	static bool Initialize();
	static void Shutdown();
	static void Update();

	static bool Load(Type type, const std::string& tag,
		const std::string& filename);
	static void Unload(const std::string& tag = "");

	static void SetRootFolder(const std::string& rootFolder);

	Audio(Type type = Type::Music, const std::string& tag = "",
		const std::string& filename = "");
	Audio(const Audio& copy);
	~Audio() {}

	float GetPan() const;
	float GetVolume() const;
	float GetFrequency() const;

	Fuint GetLength() const;
	Fuint GetPosition() const;

	void SetPan(float pan);
	void SetVolume(float volume);
	void SetFrequency(float frequency);

	void IsMuted(bool flag);
	void SetAudio(const std::string& tag, Type type);
	void SetLoopCount(Loop loopType, Loop loopCount = Loop::None);
	void SetFrequencyRange(float minFrequency, float maxFrequency);
	void SetFrequencyInterval(Interval intervalType, float interval = 1.0f);

	bool Play();
	void Pause();
	void Resume();
	void Stop();
	void Move(Position position, Fuint positionValue = 0);



private:

	Type m_type;
	bool m_isMuted;
	Loop m_loopCount;
	std::string m_tag;

	float m_pan = 0.0f;
	float m_volume = 0.5f;
	float m_frequency = 44100.0f;
	float m_minFrequency = 11025.0f;
	float m_maxFrequency = 176400.0f;

	FMOD::Sound* m_audioData = nullptr;
	FMOD::Channel* m_channel = nullptr;
	FMOD::ChannelGroup* m_channelGroup = nullptr;

	static std::string s_rootFolder;
	static FMOD::System* s_audioSystem;
	static std::map<std::string, FMOD::Sound*> s_music;
	static std::map<std::string, FMOD::Sound*> s_sounds;

};


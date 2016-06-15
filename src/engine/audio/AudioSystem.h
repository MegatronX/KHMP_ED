#pragma once
#ifndef _AUDIO_SYSTEM_H_
#define _AUDIO_SYSTEM_H_

#include <string>

#include <boost/unordered_set.hpp>
#include <boost/unordered_map.hpp>
#include <boost/noncopyable.hpp>
#include <fmod/fmod.hpp>
#include <fmod/fmod_dsp.h>
#include <fmod/fmod_errors.h>

#include <sfml/Config.hpp>
#include <events/IEvent.h>


class Engine;

class AudioSystem : public boost::noncopyable
{
public:
	AudioSystem(Engine* engine);
	~AudioSystem();

	void initSystem(const sf::Uint8 channels = 32, const std::string& musicRoorDIr = std::string(), const std::string& soundEffectDir = std::string());
	void destroySystem();
	void update();

	bool addSound(const std::string& soundName, const std::string& indexName, const bool overwriteExisting = true, const bool useStoredPath = true, const bool isSoundEffect = false, const std::string& extension = ".mp3");
	bool addSound(const std::string& soundName, const std::string& indexName, const std::string& world, const bool overwriteExisting = true, const bool useStoredPath = true, const bool isSoundEffect = false, const std::string& extension = ".mp3");
	bool removeSound(const std::string& indexName);
	void clearSounds();

	void playSound(const std::string& name, const unsigned int channel = 0, const bool loop = true, const float vol = 1.f);
	void playSection(const std::string& soundName, const unsigned int channel = 0, const bool loop = true, const int intialMilliseconds = 0, const int LoopStartMilliseconds = -1, const int LoopEndMilliseconds = -1, const float Volume = 1.f);
	void pauseChannel(const unsigned int channel);
	void unpauseChannel(const unsigned int channel);
	bool isChannelPaused(const unsigned int channel);
	void setPlaybackSpeed(const unsigned int channel, const float playbackSpeed = 1.f);
	FMOD::Sound* getSound(const std::string& soundName);
protected:
	bool handleAudioEvent(ev_ptr audioEvent);
private:
	std::string m_primaryAudioDirectory;
	std::string m_primarySoundEffectDirectory;
	bool m_ready;
	sf::Uint8 m_maxChannels;
	FMOD::System* m_baseSystem;
	FMOD::ChannelGroup* m_musicChannels;
	FMOD::ChannelGroup* m_soundEffectChannels;
	FMOD::ChannelGroup* m_miscChannels;
	FMOD::Channel** m_channels;

	Engine* m_engine;

	boost::unordered_map<std::string, FMOD::Sound*> m_soundSet;
	boost::unordered_map<std::string, float> m_playbackSpeeds;
	boost::unordered_map<unsigned int, bool> m_channelStatus;
};

#endif
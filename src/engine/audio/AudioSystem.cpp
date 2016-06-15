#include "AudioSystem.h"
#include <delegates/FastDelegateBind.h>
#include <Engine.h>
#include <Events/EventManager.h>
#include <events/eventtypes/AudioEvents.h>

void ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	}
}

AudioSystem::AudioSystem(Engine* engine) : m_engine(engine), m_ready(false)
{
	
}
AudioSystem::~AudioSystem()
{
	if (m_ready)
	{
		destroySystem();
	}
}

void AudioSystem::initSystem(const sf::Uint8 channels, const std::string& musicRoorDir, const std::string& soundEffectDir)
{
	if (m_ready)
	{
		destroySystem();
		m_ready = false;
	}
	m_primaryAudioDirectory = musicRoorDir;
	m_primarySoundEffectDirectory = soundEffectDir;
	m_maxChannels = channels;

	m_channels = new FMOD::Channel*[m_maxChannels];
	FMOD::System_Create(&m_baseSystem);

	m_baseSystem->createChannelGroup("Music Channels", &m_musicChannels);
	m_baseSystem->createChannelGroup("Sound Effect Channels", &m_soundEffectChannels);
	m_baseSystem->createChannelGroup("Misc Channels", &m_musicChannels);

	m_baseSystem->init(m_maxChannels, FMOD_INIT_NORMAL, nullptr);
	m_baseSystem->setStreamBufferSize(128 * 1024, FMOD_TIMEUNIT_RAWBYTES);
	m_engine->getEventManager().addListener(fastdelegate::MakeDelegate(this, &AudioSystem::handleAudioEvent), AddAudioRequestEvent::m_eventSignature);
	m_engine->getEventManager().addListener(fastdelegate::MakeDelegate(this, &AudioSystem::handleAudioEvent), PlayAudioRequestEvent::m_eventSignature);
	//m_engine->getEventManager().addListener(EventListener(handleAudioEvent), AddAudioRequestEvent::m_eventSignature);
	m_ready = true;
}

void AudioSystem::destroySystem()
{
	for (auto it = m_soundSet.begin(); it != m_soundSet.end(); ++it)
	{
		if (it->second != nullptr)
		{
			it->second->release();
		}
	}
	m_soundSet.clear();
	m_playbackSpeeds.clear();
	m_channelStatus.clear();
	m_musicChannels->release();
	m_soundEffectChannels->release();
	m_miscChannels->release();

	m_baseSystem->close();
	m_baseSystem->release();
	delete[] m_channels;
	m_baseSystem = nullptr;
	m_engine->getEventManager().removeListener(fastdelegate::MakeDelegate(this, &AudioSystem::handleAudioEvent), AddAudioRequestEvent::m_eventSignature);
	m_engine->getEventManager().removeListener(fastdelegate::MakeDelegate(this, &AudioSystem::handleAudioEvent), PlayAudioRequestEvent::m_eventSignature);
	m_ready = false;
}

void AudioSystem::update()
{
	m_baseSystem->update();
}

bool AudioSystem::addSound(const std::string& soundName, const std::string& indexName, const bool overwriteExisting, const bool useStoredPath, const bool isSoundEffect, const std::string& extension)
{
	if (!overwriteExisting && m_soundSet.find(indexName) != m_soundSet.end())
		return false;

	std::string assembedPath;
	if (!useStoredPath)
	{
		assembedPath = soundName;
	}
	else
	{
		assembedPath = isSoundEffect ? m_primarySoundEffectDirectory : m_primaryAudioDirectory;
		assembedPath += soundName + extension;
	}
	if (overwriteExisting)
		removeSound(indexName);
	FMOD::Sound* sound;
	FMOD_RESULT res = m_baseSystem->createSound(assembedPath.c_str(), FMOD_HARDWARE | FMOD_LOOP_NORMAL, 0, &sound);
	return true;
}

bool AudioSystem::addSound(const std::string& soundName, const std::string& indexName, const std::string& world, const bool overwriteExisting, const bool useStoredPath, const bool isSoundEffect, const std::string& extension)
{
	if (!overwriteExisting && m_soundSet.find(indexName) != m_soundSet.end())
		return false;

	std::string assembedPath;
	if (!useStoredPath)
	{
		assembedPath = soundName;
	}
	else
	{
		assembedPath = isSoundEffect ? m_primarySoundEffectDirectory : m_primaryAudioDirectory;
		if (!world.empty() || world != "Default")
		{
			std::string setting(world + "Dir");
			assembedPath += m_engine->getConfiguration().getApplicationSetting(setting);
		}
		assembedPath += soundName + extension;
	}
	if (overwriteExisting)
		removeSound(indexName);
	FMOD::Sound* sound;
	FMOD_RESULT res = m_baseSystem->createSound(assembedPath.c_str(), FMOD_HARDWARE | FMOD_LOOP_NORMAL, 0, &sound);
	m_soundSet[indexName] = sound;
	return true;
}

bool AudioSystem::removeSound(const std::string& indexName)
{
	bool removed = false;
	auto it = m_soundSet.find(indexName);
	if (it != m_soundSet.end())
	{
		it->second->release();
		m_soundSet.erase(it);
		removed = true;
	}
	auto it2 = m_playbackSpeeds.find(indexName);
	if (it2 != m_playbackSpeeds.end())
	{
		m_playbackSpeeds.erase(it2);
		removed = true;
	}
	return removed;

}
void AudioSystem::clearSounds()
{
	for (auto it = m_soundSet.begin(); it != m_soundSet.end(); ++it)
	{
		if (it->second != NULL)
			it->second->release();
	}
	m_soundSet.clear();
	m_playbackSpeeds.clear();
	m_channelStatus.clear();
}

void AudioSystem::playSound(const std::string& name, const unsigned int channel, const bool loop, const float vol)
{
	auto playableSound = m_soundSet.find(name);
	if (playableSound != m_soundSet.end())
	{
		if (!loop)
		{
			playableSound->second->setMode(FMOD_HARDWARE | FMOD_LOOP_OFF);
		}
		else
		{
			playableSound->second->setMode(FMOD_HARDWARE | FMOD_LOOP_NORMAL);
		}
		FMOD_RESULT res = m_baseSystem->playSound(FMOD_CHANNEL_FREE, playableSound->second, false, &m_channels[channel % m_maxChannels]);
		res = m_channels[channel % m_maxChannels]->setVolume(vol);
		m_baseSystem->update();
	}
}
void AudioSystem::playSection(const std::string& soundName, const unsigned int channel, const bool loop, const int intialMilliseconds, const int LoopStartMilliseconds, const int LoopEndMilliseconds, const float vol)
{
	auto playableSound = m_soundSet.find(soundName);
	if (playableSound != m_soundSet.end())
	{
		if (!loop)
		{
			playableSound->second->setMode(FMOD_HARDWARE | FMOD_LOOP_OFF);
		}
		else
		{
			playableSound->second->setMode(FMOD_HARDWARE | FMOD_LOOP_NORMAL);
		}
		FMOD_RESULT res = m_baseSystem->playSound(FMOD_CHANNEL_FREE, playableSound->second, false, &m_channels[channel % m_maxChannels]);
		res = m_channels[channel % m_maxChannels]->setVolume(vol);
		m_baseSystem->update();
	}
}
void AudioSystem::pauseChannel(const unsigned int channel)
{

}
void AudioSystem::unpauseChannel(const unsigned int channel)
{

}
bool AudioSystem::isChannelPaused(const unsigned int channel)
{
	bool paused = false;
	return paused;
}
void AudioSystem::setPlaybackSpeed(const unsigned int channel, const float playbackSpeed)
{
	bool paused = false;
	//return paused;
}
FMOD::Sound* AudioSystem::getSound(const std::string& soundName)
{
	return nullptr;
}

bool AudioSystem::handleAudioEvent(ev_ptr audioEvent)
{
	EventType audioEventType = audioEvent->getEventType();
	std::cout << "Hitting Audio event\n";
	if (audioEventType == AddAudioRequestEvent::m_eventSignature)
	{
		
		auto audioReq = boost::dynamic_pointer_cast<AddAudioRequestEvent>(audioEvent);
		std::string fileName(audioReq->getFileName());
		addSound(fileName, audioReq->getAudioIndex(), audioReq->getWorld(), true, audioReq->getUseStoredPath(), audioReq->getIsSoundEffect(), audioReq->getExtension());
		return true;
	}
	else if (audioEventType == PlayAudioRequestEvent::m_eventSignature)
	{
		auto audioPlay = boost::dynamic_pointer_cast<PlayAudioRequestEvent>(audioEvent);
		unsigned int channel = audioPlay->getChannel();
		if (channel > m_maxChannels)
		{

		}
		playSound(audioPlay->getAudioName(), channel, audioPlay->getIsLooped(), audioPlay->getVolume());
		return true;
	}
	else if (audioEventType == PauseAudioRequestEvent::m_eventSignature)
	{
		return true;
	}
	return false;
}
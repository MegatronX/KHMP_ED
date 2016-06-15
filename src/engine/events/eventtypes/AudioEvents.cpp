#include "AudioEvents.h"

const EventType AddAudioRequestEvent::m_eventSignature = 0x8c88191f;// , 0xfc39, 0x4cc8, 0xad, 0x84, 0x38, 0x51, 0x1b, 0x4f, 0xe8, 0xbe);


AddAudioRequestEvent::AddAudioRequestEvent(const std::string& fileName, const std::string& index, const sf::Time timestamp) :
//AddAudioRequestEvent::AddAudioRequestEvent(const sf::Uint32 timestamp, const std::string& fileName, const std::string& index, const bool isSoundEffect) :
m_audioFileName(fileName), m_audioIndex(index), m_isSoundEffect(false), m_world(""), m_extension(".mp3"), m_useStoredPath(true), IEvent(m_eventSignature, timestamp)
{

}

AddAudioRequestEvent::AddAudioRequestEvent(const std::string& fileName, const std::string& index, const bool isSoundEffect, const sf::Time timestamp) :
//AddAudioRequestEvent::AddAudioRequestEvent(const sf::Uint32 timestamp, const std::string& fileName, const std::string& index, const bool isSoundEffect) :
m_audioFileName(fileName), m_audioIndex(index), m_isSoundEffect(isSoundEffect), m_world(""), m_extension(".mp3"), m_useStoredPath(true), IEvent(m_eventSignature, timestamp)
{

}
AddAudioRequestEvent::AddAudioRequestEvent(const std::string& filename, const std::string& index, const bool isSoundEffect, const std::string& world, const bool useStoredPaths, const std::string extension, const sf::Time timestamp) :
m_audioFileName(filename), m_audioIndex(index), m_isSoundEffect(isSoundEffect), m_world(world), m_extension(extension), m_useStoredPath(useStoredPaths), IEvent(m_eventSignature, timestamp)
{

}
const EventType& AddAudioRequestEvent::getEventType() const
{
	return m_eventSignature;
}

const std::string& AddAudioRequestEvent::getFileName() const
{
	return m_audioFileName;
}
const std::string& AddAudioRequestEvent::getAudioIndex() const
{
	return m_audioIndex;
}
const std::string& AddAudioRequestEvent::getExtension() const
{
	return m_extension;
}
const std::string& AddAudioRequestEvent::getWorld() const
{
	return m_world;
}
const bool AddAudioRequestEvent::getUseStoredPath() const
{
	return m_useStoredPath;
}
const bool AddAudioRequestEvent::getIsSoundEffect() const
{
	return m_isSoundEffect;
}

const EventType PlayAudioRequestEvent::m_eventSignature = 0xffbfc54f;// , 0x344c, 0x47bd, 0xb6, 0x28, 0x27, 0x86, 0x20, 0xeb, 0xf, 0x41);


PlayAudioRequestEvent::PlayAudioRequestEvent(const std::string& audioName, const bool loop, const sf::Time timestamp) :
	m_audioName(audioName), m_channel(0), m_volume(1.f), IEvent(m_eventSignature, timestamp), m_loop(loop)
{

}

PlayAudioRequestEvent::PlayAudioRequestEvent(const std::string& audioName, const unsigned int channel, const bool loop, const float volume, const sf::Time timestamp) :
m_audioName(audioName), m_channel(channel), m_volume(volume), IEvent(m_eventSignature, timestamp), m_loop(loop)
{

}
const EventType& PlayAudioRequestEvent::getEventType() const
{
	return m_eventSignature;
}

const std::string& PlayAudioRequestEvent::getAudioName() const
{
	return m_audioName;
}
unsigned int PlayAudioRequestEvent::getChannel() const
{
	return m_channel;
}
float PlayAudioRequestEvent::getVolume() const
{
	return m_volume;
}
bool PlayAudioRequestEvent::getIsSoundEffect() const
{
	return m_isSoundEffect;
}
bool PlayAudioRequestEvent::getIsLooped() const
{
	return m_loop;
}

const EventType PauseAudioRequestEvent::m_eventSignature = 0xa329f244;// , 0x206d, 0x44d5, 0xbe, 0xac, 0x68, 0xda, 0xa5, 0xc1, 0x8, 0x3c);

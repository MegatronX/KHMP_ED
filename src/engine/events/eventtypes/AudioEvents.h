#pragma once
#ifndef _AUDIOEVENTS_H_
#define _AUDIOEVENTS_H_

#include <events/IEvent.h>


class AddAudioRequestEvent : public IEvent
{
public:
	static const EventType m_eventSignature;
	explicit AddAudioRequestEvent(const std::string& fileName, const std::string& index, const sf::Time timestamp = sf::Time::Zero);
	explicit AddAudioRequestEvent(const std::string& fileName, const std::string& index, const bool isSoundEffect, const sf::Time timestamp = sf::Time::Zero);
	explicit AddAudioRequestEvent(const std::string& filename, const std::string& index, const bool isSoundEffect, const std::string& world, const bool useStoredPaths = true, const std::string extension = ".mp3", const sf::Time timestamp = sf::Time::Zero);

	const EventType& getEventType() const override;
	const std::string& getFileName() const;
	const std::string& getAudioIndex() const;
	const std::string& getExtension() const;
	const std::string& getWorld() const;
	const bool getUseStoredPath() const;
	const bool getIsSoundEffect() const;
protected:
private:
	std::string m_audioFileName;
	std::string m_audioIndex;
	std::string m_extension;
	std::string m_world;
	bool m_useStoredPath;
	bool m_isSoundEffect;
};

class PlayAudioRequestEvent : public IEvent
{
public:
	static const EventType m_eventSignature;
	explicit PlayAudioRequestEvent(const std::string& audioName, const bool loop = false, const sf::Time timestamp = sf::Time::Zero);
	explicit PlayAudioRequestEvent(const std::string& audioName, const unsigned int channel = 10000, const bool loop = false, const float volume = 1.f, const sf::Time timestamp = sf::Time::Zero);
	const EventType& getEventType() const override;
	const std::string& getAudioName() const;
	unsigned int getChannel() const;
	float getVolume() const;
	bool getIsSoundEffect() const;
	bool getIsLooped() const;
protected:
private:
	std::string m_audioName;
	unsigned int m_channel;
	bool m_isSoundEffect;
	float m_volume;
	bool m_loop;
};
class PauseAudioRequestEvent : public IEvent
{
public:
	static const EventType m_eventSignature;
};
class AudioStartEvent : public IEvent
{

private:
	std::string m_audioName;
	bool m_isSoundEffect;
};

class AudioEndEvent : public IEvent
{
private:
	bool m_isSoundEffect;
};

class AudioPauseEvent : public IEvent
{
private:
	bool m_isSoundEffect;
};

#endif
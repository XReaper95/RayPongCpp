//
// Created by Luis on 22/04/2021.
//

#include "SoundManager.h"

namespace
{

raylib::Sound loadSoundResource(const char* path)
{
    return {(TextFormat("resources/%s", path))};
}

} // namespace

SoundManager::SoundManager()
    : m_StartWhistle{loadSoundResource("whistle.wav")},
      m_PaddleHit{loadSoundResource("wood_hit.wav")},
      m_BorderHit{loadSoundResource("rubber_hit.wav")},
      m_Score{loadSoundResource("coin_in_machine.wav")},
      m_GameWon{loadSoundResource("clapping.wav")}
{
}

SoundManager* SoundManager::s_Instance = nullptr;

SoundManager* SoundManager::instance()
{
    if (s_Instance == nullptr)
    {
        s_Instance = new SoundManager();
    }
    return s_Instance;
}

void SoundManager::playWhistle()
{
    m_StartWhistle.Play();
}

void SoundManager::playPaddleHit()
{
    m_PaddleHit.Play();
}

void SoundManager::playBorderHit()
{
    m_BorderHit.Play();
}

void SoundManager::playGameWon()
{
    m_GameWon.Play();
}

void SoundManager::playScore()
{
    m_Score.Play();
}

void SoundManager::stopScore()
{
    m_Score.Stop();
}

void SoundManager::stopGameWon()
{
    m_GameWon.Stop();
}
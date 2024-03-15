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

SoundManager* SoundManager::Instance()
{
    if (s_Instance == nullptr)
    {
        s_Instance = new SoundManager();
    }
    return s_Instance;
}

void SoundManager::PlayWhistle()
{
    m_StartWhistle.Play();
}

void SoundManager::PlayPaddleHit()
{
    m_PaddleHit.Play();
}

void SoundManager::PlayBorderHit()
{
    m_BorderHit.Play();
}

void SoundManager::PlayGameWon()
{
    m_GameWon.Play();
}

void SoundManager::PlayScore()
{
    m_Score.Play();
}

void SoundManager::StopScore()
{
    m_Score.Stop();
}

void SoundManager::StopGameWon()
{
    m_GameWon.Stop();
}

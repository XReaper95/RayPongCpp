//
// Created by Luis on 22/04/2021.
//

#include "SoundManager.h"

namespace
{

raylib::Sound LoadSoundResource(const char* path)
{
    return {(TextFormat("resources/%s", path))};
}

} // namespace

SoundManager::SoundManager()
    : m_startWhistle{LoadSoundResource("whistle.wav")},
      m_paddleHit{LoadSoundResource("wood_hit.wav")},
      m_borderHit{LoadSoundResource("rubber_hit.wav")},
      m_score{LoadSoundResource("coin_in_machine.wav")},
      m_gameWon{LoadSoundResource("clapping.wav")}
{
}

SoundManager* SoundManager::s_instance = nullptr;

SoundManager* SoundManager::Instance()
{
    if (s_instance == nullptr)
    {
        s_instance = new SoundManager();
    }
    return s_instance;
}

void SoundManager::PlayWhistle()
{
    m_startWhistle.Play();
}

void SoundManager::PlayPaddleHit()
{
    m_paddleHit.Play();
}

void SoundManager::PlayBorderHit()
{
    m_borderHit.Play();
}

void SoundManager::PlayGameWon()
{
    m_gameWon.Play();
}

void SoundManager::PlayScore()
{
    m_score.Play();
}

void SoundManager::StopScore()
{
    m_score.Stop();
}

void SoundManager::StopGameWon()
{
    m_gameWon.Stop();
}

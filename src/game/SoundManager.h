//
// Created by Luis on 22/04/2021.
//
#ifndef RAY_PONG_C_SRC_SYSTEM_SOUNDS_H_
#define RAY_PONG_C_SRC_SYSTEM_SOUNDS_H_

#include "raylib-cpp.hpp"

class SoundManager
{
public:
    SoundManager(SoundManager& other) = delete;
    void operator=(const SoundManager& rhs) = delete;
    static SoundManager* Instance();

    void PlayWhistle();
    void PlayPaddleHit();
    void PlayBorderHit();
    void PlayGameWon();
    void PlayScore();
    void StopScore();
    void StopGameWon();

private:
    SoundManager();
    static SoundManager* s_instance;

    raylib::AudioDevice m_audioDevice;

    raylib::Sound m_startWhistle;
    raylib::Sound m_paddleHit;
    raylib::Sound m_borderHit;
    raylib::Sound m_score;
    raylib::Sound m_gameWon;
};

#endif // RAY_PONG_C_SRC_SYSTEM_SOUNDS_H_

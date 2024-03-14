//
// Created by Luis on 22/04/2021.
//

#ifndef RAY_PONG_C_SRC_SYSTEM_SOUNDS_H_
#define RAY_PONG_C_SRC_SYSTEM_SOUNDS_H_
#include <Sound.hpp>

class SoundManager
{
public:
    SoundManager(SoundManager& other) = delete;
    void operator=(const SoundManager& rhs) = delete;
    static SoundManager* instance();

    void playWhistle();
    void playPaddleHit();
    void playBorderHit();
    void playGameWon();
    void playScore();
    void stopScore();
    void stopGameWon();

private:
    SoundManager();
    static SoundManager* s_Instance;

    raylib::Sound m_StartWhistle;
    raylib::Sound m_PaddleHit;
    raylib::Sound m_BorderHit;
    raylib::Sound m_Score;
    raylib::Sound m_GameWon;
};

#endif // RAY_PONG_C_SRC_SYSTEM_SOUNDS_H_

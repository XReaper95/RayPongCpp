#include "game/Game.h"
#include "game/SoundManager.h"
#include "game/UI.h"

#include "raylib-cpp.hpp"

#include <format>

// CONFIGURATION
constexpr int kScreenWidth = 800;
constexpr int kScreenHeight = 600;
constexpr int kTargetFps = 60;
constexpr auto kWindowsTitle = "Pong with Raylib and C++";

int main()
{
    // INITIALIZATION
    SetTraceLogLevel(LOG_INFO);

    auto window = raylib::Window{kScreenWidth, kScreenHeight, kWindowsTitle, FLAG_MSAA_4X_HINT};
    window.SetTargetFPS(kTargetFps);

    // load all the sounds, Note: loading the sounds and instantiating the singleton
    // should be two separate operations but since there is no resource manager just let it be
    SoundManager::Instance();

    // SHADERS
    raylib::RenderTexture2D renderTarget{kScreenWidth, kScreenHeight};

    raylib::Shader loopHeroShader{nullptr, "resources/loop_hero_crt.frag"};
    const int screenSizeUniformLoc = loopHeroShader.GetLocation("screenSize");
    constexpr float screenSize[2] = { static_cast<float>(kScreenHeight) /2, static_cast<float>(kScreenHeight) /2 };
    loopHeroShader.SetValue(screenSizeUniformLoc, screenSize, SHADER_UNIFORM_VEC2);

    raylib::Shader crtShader{nullptr, "resources/crt.frag"};

    const auto backgroundColor{raylib::Color::FromHSV(207, 0.47f, 0.15f)};

    Game game;
    window.SetMonitor(0);

    raylib::Shader* shader = &loopHeroShader;

    // Main game loop TODO refactor this to make the logic easier to follow
    while (!window.ShouldClose()) // Detect window close button or ESC key
    {
        // UPDATE
        window.SetTitle(std::format("{} FPS - {}", kWindowsTitle, window.GetFPS()));

        // swap the shader
        if (IsKeyDown(KEY_ONE))
        {
            shader = &loopHeroShader;
        }
        else if (IsKeyDown(KEY_TWO))
        {
            shader = &crtShader;
        }

        if (!game.HasWinner())
        {
            game.ProcessEvents();
        }
        else
        {
            game.Reset();
        }

        window.BeginDrawing();
        // draw the game to a texture framebuffer
        renderTarget.BeginMode();
        window.ClearBackground(backgroundColor);
        game.Draw();
        renderTarget.EndMode();

        // draw the game with the overlay CTR shader
        shader->BeginMode();
        renderTarget.GetTexture().Draw(0, 0, WHITE);
        shader->EndMode();

        ui::DrawScoreBoard(game.GetLeftPaddle(), game.GetRightPaddle());

        // this needs to be here because it draws to the screen TODO refactor
        if (game.HasWinner())
        {
            game.ProcessWonState();
        }

        window.EndDrawing();
    }

    return 0;
}

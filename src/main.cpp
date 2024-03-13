#include "raylib-cpp.hpp"

#include "imgui.h"
#include "rlImGui.h"

int main() {
    int screenWidth = 1280;
    int screenHeight = 800;

    raylib::Window window(
        screenWidth,
        screenHeight,
        "MyGame - basic window",
        FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE
        );

    raylib::Texture logo("resources/raylib_logo.png");

    // init imgui
    rlImGuiSetup(true);

    SetTargetFPS(60);

    while (!window.ShouldClose())
    {
        BeginDrawing();

        window.ClearBackground(RAYWHITE);

        // start ImGui Conent
        rlImGuiBegin();

        // show ImGui Content
        bool open = true;
        ImGui::ShowDemoWindow(&open);

        // end ImGui Content
        rlImGuiEnd();

        DrawText("Congrats! You created your first window!", 190, 50, 20, LIGHTGRAY);

        // Object methods.
        logo.Draw(
            screenWidth / 2 - logo.GetWidth() / 2 - 200,
            screenHeight / 2 - logo.GetHeight() / 2);

        EndDrawing();
    }

    rlImGuiShutdown();

    // UnloadTexture() and CloseWindow() are called automatically.

    return 0;
}

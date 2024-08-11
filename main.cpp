// main.cpp
#include "raylib.h"
#include <iostream>


Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};


int main() {
    std::cout << "Start!" << std::endl;
    InitWindow(750, 750, "Snake Retro");
    SetTargetFPS(60);
    
    while (!WindowShouldClose()) { 
        // Update

        // Draw
        BeginDrawing();
        ClearBackground(green);
        DrawText("AAAAAAAWelcome to Raylib 5.0!`", 190, 200, 20, darkGreen);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

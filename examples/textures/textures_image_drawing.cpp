/*******************************************************************************************
*
*   raylib [textures] example - Image loading and drawing on it
*
*   NOTE: Images are loaded in CPU memory (RAM); textures are loaded in GPU memory (VRAM)
*
*   This example has been created using raylib 1.4 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib/raylib.hpp"

#include <iostream>

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    raylib::Window w(screenWidth, screenHeight, "raylib [textures] example - image drawing");
    raylib::Color background(RAYWHITE);
    raylib::Color darkGray(DARKGRAY);

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    raylib::Image cat("resources/cat.png");             // Load image in CPU memory (RAM)
    cat.Crop(raylib::Rectangle(100, 10, 280, 380));      // Crop an image piece
    cat.FlipHorizontal();                              // Flip cropped image horizontally
    cat.Resize(150, 200);                            // Resize flipped-cropped image

    raylib::Image parrots("resources/parrots.png");     // Load image in CPU memory (RAM)

    // Draw one image over the other with a scaling of 1.5f
    parrots.Draw(cat,
            raylib::Rectangle(0, 0, cat.width, cat.height),
            raylib::Rectangle(30, 40, cat.width*1.5f, cat.height*1.5f),
            WHITE);

    parrots.Crop(raylib::Rectangle(0, 50, parrots.width, parrots.height - 100)); // Crop resulting image

    // Load custom font for frawing on image
    raylib::Font font("resources/custom_jupiter_crash.png");

    // Draw over image using custom font
    parrots.DrawTextEx(raylib::Vector2(300, 230), font, "PARROTS & CAT", font.baseSize, -2, WHITE);

    raylib::Texture2D texture(parrots);      // Image converted to texture, uploaded to GPU memory (VRAM)

    SetTargetFPS(60);
    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!w.ShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            background.ClearBackground();

            texture.Draw(screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2 - 40, WHITE);
            darkGray.DrawRectangleLines(screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2 - 40, texture.width, texture.height);

            darkGray.DrawText("We are drawing only one texture from various images composed!", 240, 350, 10);
            darkGray.DrawText("Source images have been cropped, scaled, flipped and copied one over the other.", 190, 370, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    return 0;
}

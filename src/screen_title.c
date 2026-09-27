/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Title Screen Functions Definitions (Init, Update, Draw, Unload)
*
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#include "colors.h"
#include "raylib.h"
#include "screens.h"
#include "raymath.h"
#include <stdio.h>

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;
static Texture2D title_texture = {0};
static float alpha;
static bool fadein = true;

//----------------------------------------------------------------------------------
// Title Screen Functions Definition
//----------------------------------------------------------------------------------

// Title Screen Initialization logic
void InitTitleScreen(void)
{
    // TODO: Initialize TITLE screen variables here!
    framesCounter = 0;
    finishScreen = 0;
    title_texture = LoadTexture("./resources/Keys_title.png");
    fadein = true;
    alpha = 0.05f;
}

// Title Screen Update logic
void UpdateTitleScreen(void)
{
    framesCounter++;
    
    if (alpha > 0.95f) {
        fadein = false;
        framesCounter = 0;
    } else if (alpha < 0.05f) {
        fadein = true;
        framesCounter = 0;
    }

    if (fadein) {
        alpha = Remap(framesCounter%50, 0, 50, 0.05, 1.0);
        printf("FADEIN - Alpha: %f\n", alpha);
    } else {
        alpha = Remap(framesCounter%50, 0, 50, 0.95, 0.0);
        printf("FADEOUT - Alpha: %f\n", alpha);
    }

    // Press enter or tap to change to GAMEPLAY screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        //finishScreen = 1;   // OPTIONS
        finishScreen = 2;   // GAMEPLAY
        PlaySound(fxKeys);
    }
}

// Title Screen Draw logic
void DrawTitleScreen(void)
{
    DrawTexture(title_texture, 0, 0, RAYWHITE);
    

    // // Background
    // DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), XT_DK_GREY);
    // // Title 
    Vector2 bb_text_title = MeasureTextEx(font, "KEYS", big_font.baseSize, 4);
    Vector2 pos = { (int)(GetScreenWidth()/2)-(bb_text_title.x/2), 20 };
    DrawTextEx(big_font, "KEYS", pos, big_font.baseSize, 4, VN_ORANGE);
    // // Start text 
    Vector2 bb_text_start = MeasureTextEx(font, "PRESS ENTER to START GAME", font.baseSize, 2);
    Vector2 pos_start = {(int)(GetScreenWidth()/2)-(bb_text_start.x/2), (int)(GetScreenHeight()/2)-(bb_text_start.y/2)};
    DrawTextEx(font, "PRESS ENTER to START GAME", pos_start, font.baseSize, 4, Fade(VN_ORANGE, alpha));
}

// Title Screen Unload logic
void UnloadTitleScreen(void)
{
    UnloadTexture(title_texture);
    // TODO: Unload TITLE screen variables here!
}

// Title Screen should finish?
int FinishTitleScreen(void)
{
    return finishScreen;
}

/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Ending Screen Functions Definitions (Init, Update, Draw, Unload)
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

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

//----------------------------------------------------------------------------------
// Winning Screen Functions Definition
//----------------------------------------------------------------------------------

// Winning Screen Initialization logic
void InitWinningScreen(void)
{
    // TODO: Initialize ENDING screen variables here!
    framesCounter = 0;
    finishScreen = 0;
}

// Winning Screen Update logic
void UpdateWinningScreen(void)
{
    // TODO: Update ENDING screen variables here!

    // Press enter or tap to return to TITLE screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        finishScreen = 1;
        PlaySound(fxKeys);
    }
}

// Winning Screen Draw logic
void DrawWinningScreen(void)
{
    // TODO: Draw ENDING screen here!
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), XT_DK_GREY);

    Vector2 pos = { 120, 50 };
    DrawTextEx(big_font, "U WIN", pos, big_font.baseSize, 4, VN_ORANGE);
    DrawTextEx(font, "MENUDO CAMPEON,\nTE MERECES UNA DUCHITA", (Vector2){120, 220}, font.baseSize, 2, VN_ORANGE);
}

// Winning Screen Unload logic
void UnloadWinningScreen(void)
{
    // TODO: Unload ENDING screen variables here!
}

// Winning Screen should finish?
int FinishWinningScreen(void)
{
    return finishScreen;
}

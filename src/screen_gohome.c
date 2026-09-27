
/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Gameplay Screen Functions Definitions (Init, Update, Draw, Unload)
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

#include "raylib.h"
#include "screens.h"
#include "colors.h"
#include <string.h>

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;
static Texture2D bg_texture = {0};
static Texture2D clouds_texture = {0};
static Texture2D bus_texture = {0};
static Texture2D buildings_texture = {0};
static Vector2 clouds_pos = {0};
static Vector2 bus_pos = {0};
//----------------------------------------------------------------------------------
// GoHome Screen Functions Definition
//----------------------------------------------------------------------------------

// GoHome Screen Initialization logic
void InitGoHomeScreen(void)
{
    framesCounter = 0;
    finishScreen = 0;
    bg_texture = LoadTexture("./resources/gohome_road.png");
    clouds_texture = LoadTexture("./resources/gohome_nubes.png");
    bus_texture = LoadTexture("./resources/gohome_bus.png");
    buildings_texture = LoadTexture("./resources/gohome_edificios.png");
    clouds_pos = (Vector2){400, 60};
    bus_pos = (Vector2){5, 300};
}

// GoHome Screen Update logic
void UpdateGoHomeScreen(void)
{
    // Press enter or tap to change to ENDING screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        finishScreen = 1;
        PlaySound(fxKeys);
    }
    if (framesCounter%4 == 0) clouds_pos.x -= 1;
    bus_pos.x += (framesCounter%2);

    if (bus_pos.x > 500) {
        finishScreen = 1;
        PlaySound(fxKeys);
    }
}

// GoHome Screen Draw logic
void DrawGoHomeScreen(void)
{
    // Limpieza de pantalla
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), XT_DK_GREY);
    // Background
    DrawTexture(bg_texture, 0, 0, RAYWHITE);
    // clouds 
    DrawTexture(clouds_texture, clouds_pos.x, clouds_pos.y, RAYWHITE);
    // buildings
    DrawTexture(buildings_texture, 0, 0, RAYWHITE);
    // bus 
    DrawTexture(bus_texture, bus_pos.x, bus_pos.y, RAYWHITE);
    framesCounter++;

}

// Gameplay Screen Unload logic
void UnloadGoHomeScreen(void)
{
    UnloadTexture(bg_texture);
    UnloadTexture(clouds_texture);
    UnloadTexture(buildings_texture);
    UnloadTexture(bus_texture);
}

// Gameplay Screen should finish?
int FinishGoHomeScreen(void)
{
    return finishScreen;
}

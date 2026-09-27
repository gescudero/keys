
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
static int dialogue_state = 0;
static Vector2 panel_pos = {80, 350};
static int panel_width = 0;
static const char *dialogues[3]; 
static float alpha = 0.0f;
//----------------------------------------------------------------------------------
// AtHome Screen Functions Definition
//----------------------------------------------------------------------------------

// AtHome Screen Initialization logic
void InitAtHomeScreen(void)
{
    // TODO: Initialize INTRO screen variables here!
    framesCounter = 0;
    finishScreen = 0;
    bg_texture = LoadTexture("./resources/atHome.png");
    dialogue_state = 0;
    panel_pos = (Vector2){80,350};
    panel_width = 0;
    dialogues[0] = "Oh no! You realized that you left the keys\non the table of your office!";
    dialogues[1] = "Now you need to RETURN to the office\nin less than 30 minutes or the office will be close.";
    dialogues[2] = "RUN!!!";
    alpha = 0.0f;
}

// AtHome Screen Update logic
void UpdateAtHomeScreen(void)
{
    // TODO: Update INTRO screen variables here!

    // Press enter or tap to change to ENDING screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        if (dialogue_state >= 3) {
            finishScreen = 1;
            PlaySound(fxKeys);
        } else {
            alpha = 0.0f;
            framesCounter = 0;
            dialogue_state++;
        }
    }
}

// AtHome Screen Draw logic
void DrawAtHomeScreen(void)
{
    // Limpieza de pantalla
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), XT_DK_GREY);
    // Background
    DrawTexture(bg_texture, 0, 0, RAYWHITE);
    // DrawText(TextFormat("finishScreen = %i", finishScreen), 20, 100, 20, VN_BLUE);
    // Vector2 pos = { 20, 10 };
    // DrawTextEx(font, "INTRO SCREEN", pos, font.baseSize*3.0f, 4, VN_CHALK);
    // DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 130, 220, 20, VN_BK_WHITE);

    // recuadro de dialogos
    switch (dialogue_state) {
        case 0:
            // Animacion del bg panel
            panel_width += 18;
            if (panel_width >= 640) {
                panel_width = 640;
                dialogue_state = 1;
            }

            DrawRectangle(panel_pos.x, panel_pos.y, panel_width, 80, Fade(XT_DK_GREY, 0.7f));
            break;
        case 4:
            // Se acabo el dialogo;
            break;
        default:
            // Animacion de show del texto 1
            alpha += 0.02;
            if (alpha >= 1.0) alpha = 1.0;
            char printed_text[200];
            int actual_char = framesCounter;
            int nb_chars = strlen(dialogues[dialogue_state-1]);
            if (actual_char>nb_chars) {
                actual_char = nb_chars;
            }
            for ( int i=0; i<actual_char; i++) {
                printed_text[i] = dialogues[dialogue_state-1][i];
            }
            printed_text[actual_char] = '\0';
            
                        
            DrawRectangle(panel_pos.x, panel_pos.y, panel_width, 80, Fade(XT_DK_GREY, 0.7f));
            DrawTextEx(
                    small_font, 
                    printed_text, 
                    (Vector2){ panel_pos.x + 10, panel_pos.y + 10}, 
                    small_font.baseSize, 
                    1, 
                    Fade(VN_WHITE, alpha));
            break;
    }
   
    framesCounter++;

}

// Gameplay Screen Unload logic
void UnloadAtHomeScreen(void)
{
    UnloadTexture(bg_texture);
}

// Gameplay Screen should finish?
int FinishAtHomeScreen(void)
{
    return finishScreen;
}

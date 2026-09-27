#include "colors.h"
#include "raylib.h"
#include "screens.h"
#include <stdlib.h>

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------

typedef enum { FS_IDLE, FS_AVOID, FS_HIT, FS_IMPACT, FS_CRASH } fighter_state;
typedef enum { FA_IDLE, FA_AVOID, FA_HIT } fighter_action;

typedef struct {
    fighter_state state;
    float cooldown;
    int health;
    Texture2D textures[5];
} fighter_t;

static float *elapsed_time = NULL;
static int framesCounter = 0;
static int finishScreen = 0;
static Texture2D heart_textures[2] = {0};
static Vector2 heart_pos = {0};
static fighter_t player = {0};
static fighter_t enemy = {0};
static fighter_action pending_action = FA_IDLE;
static const int FULL_HEALTH = 5;
static float last_action_time = 0.0f;
static float action_time = 0.0f;
static const float update_time = 0.3f; // Actualizamos el juego cada x
static int game_condition = 0; // 0=En juego; 1=Lose; 2=Win
//----------------------------------------------------------------------------------
// Fighting Screen Functions Definition
//----------------------------------------------------------------------------------
static void FighterAttacks(fighter_t *fighter);
static void FighterAvoids(fighter_t *fighter);
static void UpdateCooldown(fighter_t *fighter);

// Fighting Screen Initialization logic
void InitFightingScreen(float *elapsed)
{
    elapsed_time = elapsed;
    heart_textures[0] = LoadTexture("./resources/heart.png");
    heart_textures[1] = LoadTexture("./resources/heart_grey.png");
    heart_pos = (Vector2){500, 50};
    framesCounter = 0;
    finishScreen = 0;
    game_condition = 0;
    action_time = 0.0f;
    pending_action = FA_IDLE;
    player.state = FS_IDLE;
    player.cooldown = 0.0f;
    player.health = FULL_HEALTH;
    player.textures[0] = LoadTexture("./resources/fighter_player_idle.png");
    player.textures[1] = LoadTexture("./resources/fighter_player_avoid.png");
    player.textures[2] = LoadTexture("./resources/fighter_player_hit.png");
    player.textures[3] = LoadTexture("./resources/fighter_player_impact.png");
    player.textures[4] = LoadTexture("./resources/fighter_player_hit.png");
    enemy.state = FS_IDLE;
    enemy.cooldown = 0.0f;
    enemy.health = FULL_HEALTH;
    enemy.textures[0] = LoadTexture("./resources/fighter_enemy_idle.png");
    enemy.textures[1] = LoadTexture("./resources/fighter_enemy_avoid.png");
    enemy.textures[2] = LoadTexture("./resources/fighter_enemy_hit.png");
    enemy.textures[3] = LoadTexture("./resources/fighter_enemy_impact.png");
    enemy.textures[4] = LoadTexture("./resources/fighter_enemy_hit.png");
    last_action_time = 0.0f;
}

// Fighting Screen Update logic
void UpdateFightingScreen(void)
{
    // Press enter or tap to return to TITLE screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        finishScreen = 1;
        PlaySound(fxKeys);
    }
    // Capture player input
    if (IsKeyPressed(KEY_UP)) {
        pending_action = FA_HIT;
    }
    if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT)) {
        pending_action = FA_AVOID;
    }
    // Updating timers
    UpdateCooldown(&player);
    UpdateCooldown(&enemy);

    last_action_time += GetFrameTime();
    action_time += GetFrameTime();
    // Actualizamos solo en ciertas condiciones
    if (action_time > update_time && game_condition == 0) {
        action_time = 0.0f;
        // Tiramos un dado de 0 a 5, si saca 4 o 5, el enemy
        // ejecutará una accion, si no, no hace nada.
        int dice = rand() % 6;
        int time_to_action = (rand() % 3)+1 ;

        // Player Actions
        if (pending_action == FA_HIT) {
            FighterAttacks(&player);
            pending_action = FA_IDLE;
            if (dice > 3) {
                FighterAvoids(&enemy);
                last_action_time = 0.0f;
            }
        }
        if (pending_action == FA_AVOID) {
            FighterAvoids(&player);
            pending_action = FA_IDLE;
        }
        // Enemy Actions
        if (last_action_time > time_to_action) {
            if (dice == 4) {
                FighterAvoids(&enemy);
                last_action_time = 0.0f;
            } else if (dice == 5) {
                FighterAttacks(&enemy);
                last_action_time = 0.0f;
            }
        }
        // Check fighting 
        if (player.state == FS_IMPACT && enemy.state != FS_AVOID) {
            enemy.health--;
            player.state = FS_CRASH;
        }
        if (enemy.state == FS_IMPACT && player.state != FS_AVOID) {
            player.health--;
            *elapsed_time += 15;
            enemy.state = FS_CRASH;
        }
    }
    // Comprobamos la salud
    if (player.health <= 0) game_condition = 1; // Lose
    if (enemy.health <= 0) game_condition = 2;
}

// Fighting Screen Draw logic
void DrawFightingScreen(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLUE);
    DrawTexture(enemy.textures[enemy.state], 0, 0, RAYWHITE);
    DrawTexture(player.textures[player.state], 0, 0, RAYWHITE);
    for (int i=0; i<FULL_HEALTH; i++) {
        DrawTexture(heart_textures[(i>=enemy.health)], heart_pos.x + (i*50) , heart_pos.y, RAYWHITE);
    }

    /**
     * Debug
    DrawTextEx(small_font, 
            TextFormat("player state: %i\nplayer cooldown: %f\nplayer health: %i", player.state, player.cooldown, player.health), 
            (Vector2){10, 10}, 
            small_font.baseSize, 
            2, 
            VN_ORANGE);
    DrawTextEx(small_font, 
            TextFormat("enemy state: %i\nenemy cooldown: %f\nenemy health: %i", enemy.state, enemy.cooldown, enemy.health), 
            (Vector2){10, 150}, 
            small_font.baseSize, 
            2, 
            VN_ORANGE);
    */
    if (game_condition == 1) {
        DrawTextEx(font, 
                "HAS PERDIDO", 
                (Vector2){200, 200},
                font.baseSize, 
                2, 
                RAYWHITE);
    }
    if (game_condition == 2) {
        DrawTextEx(font, 
                "HAS GANADO", 
                (Vector2){200, 200},
                font.baseSize, 
                2, 
                RAYWHITE);
    }
}

// Fighting Screen Unload logic
void UnloadFightingScreen(void)
{
   for (int i=0; i<4; i++) {
       UnloadTexture(player.textures[i]);
       UnloadTexture(enemy.textures[i]);
   }
}

// Fighting Screen should finish?
int FinishFightingScreen(void)
{
    return finishScreen;
}


static void FighterAttacks(fighter_t *fighter) {
    if (fighter->cooldown > 0) {
        return;
    }
    fighter->state = FS_HIT;
    fighter->cooldown = 1.0f;
}
static void FighterAvoids(fighter_t *fighter) {
    if (fighter->cooldown > 0) {
        return;
    }
    fighter->state = FS_AVOID;
    fighter->cooldown = 1.0f;
}
static void UpdateCooldown(fighter_t *fighter) {
    if (fighter->cooldown > 0) {
        fighter->cooldown -= GetFrameTime();
        if (fighter->state == FS_HIT && fighter->cooldown < 0.6) {
            fighter->state = FS_IMPACT;
        }
    } else {
        fighter->state = FS_IDLE;
    }
}

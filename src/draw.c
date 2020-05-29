#include "draw.h"

#include <raylib.h>

void draw_level(const level *lvl){
    // Draw cells, iterate, including borders outside the level
    for(int y=-1;y<=lvl->size_y;y++){
        for(int x=-1;x<=lvl->size_x;x++){
            char cell = level_get(lvl,x,y);
            // If the cell is a wall, paint it
            if(cell=='#'){
                DrawRectangle(TILE_SIZE*x,TILE_SIZE*y,TILE_SIZE,TILE_SIZE,BROWN);
            }
        }
    }
}

void draw_state(const level *lvl, const state *sta){

    // Initialize a camera to be used as drawing context
    Camera2D cam;
    // make the camera follow the player
    cam.target.x = sta->pla.ent.x;
    cam.target.y = sta->pla.ent.y;
    // make it so that the player is in the middle of the screen
    cam.offset.x = GetScreenWidth()/2.0;
    cam.offset.y = GetScreenHeight()/2.0;
    // set the camera rotation to 0
    cam.rotation = 0.0;
    // set the camera zoom to 1
    cam.zoom = 1.0;
    // represents the size of the HP info(health) of each entity
    Vector2 size1 = {30,3};
    Vector2 size2 = {23,3};
    Vector2 size3 = {15,3};
    Vector2 size4 = {7,3};
    // Draw everything relative to the camera from now on
    BeginMode2D(cam);

    // Draw level
    draw_level(lvl);

    // Draw enemies
    for(int i=0;i<sta->n_enemies;i++){
        // Get a copy of the enemy entity
        entity ent = sta->enemies[i].ent;
        // Initialize a Vector2 that represents the center of the entity position
        Vector2 vec = {ent.x,ent.y};
        // These Vector2 represents the position of GUI HP info of each entity
        Vector2 health_minion = {ent.x-15,ent.y-20};
        Vector2 health_brute = {ent.x-15,ent.y-25};
        // Draw a circle with the radius of the entity, color depends on the enemy type
        if(sta->enemies[i].kind == MINION){
            DrawCircleV(vec,ent.rad,YELLOW);
            //Draw a rectangle representing the HP of minions depending of the remaining HP
            if (sta->enemies[i].ent.hp >= 2){
                DrawRectangleV(health_minion,size1,GREEN);
            }
            else {
                DrawRectangleV(health_minion,size3,RED);
            }
        }
        else{
            DrawCircleV(vec,ent.rad,RED);
            //Draw a rectangle representing the HP of brutes depending of the remaining HP
            if (sta->enemies[i].ent.hp > 9){
                DrawRectangleV(health_brute,size1,GREEN);
            }
            else if ((sta->enemies[i].ent.hp <= 9)&&(sta->enemies[i].ent.hp >6)) {
                DrawRectangleV(health_brute,size2,(Color){ 255, 220, 0, 255 });
            }
            else if ((sta->enemies[i].ent.hp <= 6)&&(sta->enemies[i].ent.hp >3)) {
                           DrawRectangleV(health_brute,size3,ORANGE);
                       }
            else {
                DrawRectangleV(health_brute,size4,RED);
            }
        }
    }

    // Draw player
    {
        // Get a copy of the player's entity
        entity ent = sta->pla.ent;
        // Initialize a Vector2 that represents the center of the entity position
        Vector2 vec = {ent.x,ent.y};
        // Vector2 whit teh position of health and cooldown
        Vector2 health = {ent.x-12,ent.y-16};
        // Draw a circle with the radius of the entity
        DrawCircleV(vec,ent.rad,BLACK);
        // /Draw a rectangle representing the HP depending of the remaining HP
        if (sta->pla.ent.hp  > 8){
            DrawRectangleV(health,size1,GREEN);
        }
        else if ((sta->pla.ent.hp  <= 8)&&(sta->pla.ent.hp  > 5)) {
            DrawRectangleV(health,size2,(Color){ 255, 220, 0, 255 });
        }
        else if ((sta->pla.ent.hp  <= 5)&&(sta->pla.ent.hp  > 2)) {
            DrawRectangleV(health,size3,ORANGE);
        }
        else {
            DrawRectangleV(health,size4,RED);
        }
        // This represent the sight that follow the mouse and show where the player is aiming
        DrawRing(vec, 90, 100, 360*(sta->aim_angle)/(2*3.1416)+100, 360*(sta->aim_angle)/(2*3.1416)+80, 100,(Color){ 230, 41, 55, 100 }  );
        DrawRingLines(vec, 90, 100, 360*(sta->aim_angle)/(2*3.1416)+100, 360*(sta->aim_angle)/(2*3.1416)+80, 10,RED);
        // Draw a point that show the cooldown of the weapon, this only show when the weapon is shutting changing from green to red.
        Vector2 cool = {ent.x-17,ent.y-14};
        if (sta->pla.cooldown <= 0){
            DrawCircleV(cool,3,GREEN);
        }
        else{
            DrawCircleV(cool,3,RED);
        }
    }
    // Draw bullets
    for(int i=0;i<sta->n_bullets;i++){
        // Get a copy of the bullet entity
        entity ent = sta->bullets[i].ent;
        // Initialize a Vector2 that represents the center of the entity position
        Vector2 vec = {ent.x,ent.y};
        // Draw a circle with the radius of the entity
        DrawCircleV(vec,ent.rad,PINK);
    }

    // Stop drawing relative to the camera
    EndMode2D();
}

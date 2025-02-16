#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <raylib.h>

#include "scene.h"
#include "example_scene.h"

#define SCREEN_WIDTH        (uint16_t) 1280
#define SCREEN_HEIGHT       (uint16_t) 800

scene_st* current_scene = NULL;

int main(int argc, char** argv) {
    // Initialise the raylib window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Scene Example");
    // Set targetted FPS
    SetTargetFPS(60);

    // Set our current scene to the example scene
    scene_st* current_scene = get_example_scene();

    // Load our scene
    scene_load(current_scene);

    // Main Loop
    while (!WindowShouldClose()) {
        // Begin drawing
        BeginDrawing();
        // Run our current scene
        scene_run(current_scene);
        // End drawing
        EndDrawing();
    }

    // Cleanup
    CloseWindow();
    scene_destroy(current_scene);

    return 0;
}

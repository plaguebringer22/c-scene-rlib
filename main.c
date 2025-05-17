#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <raylib.h>

#include "scene_manager.h"
#include "scene.h"
#include "example_scene.h"

#define SCREEN_WIDTH        (uint16_t) 1280
#define SCREEN_HEIGHT       (uint16_t) 800

scene_manager_st* manager;

scene_st* initial_scene;

int main(int argc, char** argv) {
    // Initialise the raylib window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Scene Example");
    // Set targetted FPS
    SetTargetFPS(60);

    // Create out scene manager
    initial_scene = get_example_scene();
    manager = scene_manager_create(initial_scene);

    // Set our current scene to the example scene

    // Load our scene
    scene_load(scene_manager_get_active_scene(manager));

    // Main Loop
    while (!WindowShouldClose()) {
        // Update our current scene 
        scene_update(scene_manager_get_active_scene(manager));
        // Begin drawing
        BeginDrawing();
        // Draw our current scene
        scene_draw(scene_manager_get_active_scene(manager));
        // End drawing
        EndDrawing();
    }

    // Cleanup
    CloseWindow();
    scene_manager_destroy(manager);
    scene_destroy(initial_scene);

    return 0;
}
